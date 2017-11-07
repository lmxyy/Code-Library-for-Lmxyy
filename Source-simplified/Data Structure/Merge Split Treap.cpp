// jisuanke17123
// Warning: 给指针赋值时，不要赋this，因为this是临时变量的地址
inline int rand(int n) { int x = rand(); if (x < 0) x = -x; return x%n+1; }

struct Node
{
	int size,key,val; Node *mn,*ch[2];
	inline Node *update()
	{
		mn = this; size = 1;
		if (ch[0])
		{
			size += ch[0]->size;
			if (ch[0]->mn->val < mn->val) mn = ch[0]->mn;
		}
		if (ch[1])
		{
			size += ch[1]->size;
			if (ch[1]->mn->val < mn->val) mn = ch[1]->mn;
		}
		return this;
	}
	inline Node() = default;
	inline Node(int v,Node *_mn):size(1),key(rand()),val(v),mn(_mn) { ch[0] = ch[1] = NULL; }
}pool[maxn*100/4],*root[maxn],*cur;
struct Status
{
	int l,r; ll val;
	inline Status() = default;
	inline Status(int _l,int _r,ll _val):l(_l),r(_r),val(_val) {}
	friend inline bool operator <(const Status &a,const Status &b) { return a.val > b.val; }
};

inline int sz(const Node *x) { if (x == NULL) return 0; else return x->size; }

inline Node *newnode(int v = 0) { *cur = Node(v,cur); return cur++; }

Node *insert(Node *p,Node *q)
{
	if (p == NULL&&q == NULL) return NULL;
	if (p == NULL||q == NULL) return p?p:q;
	Node *u = NULL;
	if (rand(sz(p)+sz(q)) < sz(p))
		u = p,u->ch[1] = insert(u->ch[1],q);
	else u = q,u->ch[0] = insert(p,u->ch[0]);
	return u->update();
}

Node *merge(Node *p,Node *q)
{
	if (p == NULL&&q == NULL) return NULL;
	if (p == NULL||q == NULL) return p?p:q;
	Node *u = newnode();
	if (rand(sz(p)+sz(q)) < sz(p))
		*u = *p,u->ch[1] = merge(u->ch[1],q);
	else *u = *q,u->ch[0] = merge(p,u->ch[0]);
	return u->update();
}

Node *split(Node *u,int l,int r)
{
	if (l > r||u == NULL) return 0;
	Node *x = NULL;
	if (l == 1&&r == sz(u))
	{
		x = newnode(); *x = *u;
		return x->update();
	}
	int lsz = sz(u->ch[0]);
	if (r <= lsz) return split(u->ch[0],l,r);
	if (l > lsz+1) return split(u->ch[1],l-lsz-1,r-lsz-1);
	x = newnode(); *x = *u;
	x->ch[0] = split(u->ch[0],l,lsz);
	x->ch[1] = split(u->ch[1],1,r-lsz-1);
	return x->update();
}

int get_pos(Node *rt,Node *mn)
{
	if (rt == mn) return sz(rt->ch[0]);
	else if (rt->ch[0]&&rt->ch[0]->mn == mn)
		return get_pos(rt->ch[0],mn);
	else return sz(rt->ch[0])+1+get_pos(rt->ch[1],mn);
}
inline pair <int,int> Qmin(Node *rt,int l,int r)
{
	if (l > r) return make_pair(-1,-1);
	Node *v = split(rt,l,r);
	auto ret = make_pair(v->mn->val,get_pos(v,v->mn)+l);
	return ret;
}
inline int get(Node *u,int x) { return split(u,x,x)->val; }

inline void init() { cur = pool; }

int main()
{
	struct timeb ttt; ftime(&ttt);
	srand(ttt.millitm+ttt.time*1000);
}
