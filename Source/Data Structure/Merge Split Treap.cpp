// jisuanke17123
// Warning: 给指针赋值时，不要赋this，因为this是临时变量的地址
#include<sys/timeb.h>
#include<queue>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<set>
using namespace std;

typedef long long ll;
const int maxn = 1000010;
int N;

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

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
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

inline void work(Node *rt,int k)
{
	int n = sz(rt);
	set <int> S; S.insert(0); S.insert(n+1);
	priority_queue <Status> heap;
	auto tmp = Qmin(rt,1,n);
	heap.push(Status(tmp.second,tmp.second,tmp.first));
	while (k--)
	{
		auto now = heap.top(); heap.pop();
		printf("%lld\n",now.val);
		if (now.l == now.r)
		{
			S.insert(now.l);
			auto it = S.find(now.l);
			int pre = *(--it);
			int nxt = *++(++it);
			auto ls = Qmin(rt,pre+1,now.l-1);
			auto rs = Qmin(rt,now.l+1,nxt-1);
			if (ls.first != -1)
				heap.push(Status(ls.second,ls.second,ls.first));
			if (rs.first != -1)
				heap.push(Status(rs.second,rs.second,rs.first));
		}
		if (now.r < n)
		{
			int inc = get(rt,now.r+1);
			++now.r; now.val += (ll)inc;
			heap.push(now);
		}
	}
}

inline void init() { N = 0; cur = pool; }

int main()
{
	struct timeb ttt; ftime(&ttt);
	srand(ttt.millitm+ttt.time*1000);
	for (int T = gi();T--;)
	{
		init();
		for (int Q = gi();Q--;)
		{
			int opt = gi();
			if (opt == 1)
			{
				root[++N] = NULL;
				for (int n = gi();n--;)
					root[N] = insert(root[N],newnode(gi()));
			}
			else if (opt == 2)
			{
				root[++N] = NULL;
				int x = gi(),l1 = gi(),r1 = gi(),y = gi(),l2 = gi(),r2 = gi();
				Node *ls = split(root[x],l1,r1);
				Node *rs = split(root[y],l2,r2);
				root[N] = merge(ls,rs);
			}
			else
			{
				int x = gi(),k = gi();
				work(root[x],k);
			}
		}
		// cerr << cur - pool << endl;
	}
	return 0;
}

// By zky. To be rewritten.
const int mo=1e9+7;
int rnd(){
    static int x=1;
    return x=(x*23333+233);
}
int rnd(int n){
    int x=rnd();
    if(x<0)x=-x;
    return x%n+1;
}
struct node{
    int siz,key;
    int val;
    LL sum;
    node *c[2];
    node* rz(){
        sum=val;siz=1;
        if(c[0])sum+=c[0]->sum,siz+=c[0]->siz;
        if(c[1])sum+=c[1]->sum,siz+=c[1]->siz;
        return this;
    }
    node(){}
    node(int v){
        siz=1;key=rnd();
        val=v;sum=v;
        c[0]=c[1]=0;
    }
    
}pool[maxn*8],*root,*cur=pool,*old_root,*stop;
node *newnode(int v=0){
    *cur=node(v);
    return cur++;
}
node *old_merge(node *p,node *q){
    if(!p&&!q)return 0;
    node *u=0;
    if(!p||!q)return u=p?p->rz():(q?q->rz():0);
    if(rnd(sz(p)+sz(q))<sz(p)){
        u=p;
        u->c[1]=old_merge(u->c[1],q);
    }else{
        u=q;
        u->c[0]=old_merge(p,u->c[0]);
    }
    return u->rz();
}
node *merge(node *p,node *q){
    if(!p&&!q)return 0;
    node *u=newnode();
    if(!p||!q)return u=p?p->rz():(q?q->rz():0);
    if(rnd(sz(p)+sz(q))<sz(p)){
        *u=*p;
        u->c[1]=merge(u->c[1],q);
    }else{
        *u=*q;
        u->c[0]=merge(p,u->c[0]);
    }
    return u->rz();
}
node *split(node *u,int l,int r){
    if(l>r||!u)return 0;
    node *x=0;
    if(l==1&&r==sz(u)){
        x=newnode();
        *x=*u;
        return x->rz();
    }
    int lsz=sz(u->c[0]);
    if(r<=lsz)
        return split(u->c[0],l,r);
    if(l>lsz+1)
        return split(u->c[1],l-lsz-1,r-lsz-1);
    x=newnode();
    *x=*u;
    x->c[0]=split(u->c[0],l,lsz);
    x->c[1]=split(u->c[1],1,r-lsz-1);
    return x->rz();
}
