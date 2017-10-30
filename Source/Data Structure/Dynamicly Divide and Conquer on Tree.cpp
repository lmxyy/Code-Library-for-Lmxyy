// N个点的树，每个点点权0/1，询问两个0点之间最远距离，每次可以flip一个点的点权
#include<set>
#include<vector>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 200010,inf = 1<<29,lhh = 4000037;
int N,cnt,nlight,tot,best,Root,side[maxn],toit[maxn],nxt[maxn],size[maxn],large[maxn],optimal[maxn];
int father[maxn],L[maxn],R[maxn],leaf[maxn],rechain[lhh],depth[lhh]; bool off[maxn],vis[maxn];
vector <int> son[maxn]; pair <int,int> Hash[lhh]; multiset <int> mx[maxn],S[maxn];

struct Value
{
	int a,b;
	inline Value() {}
	inline Value(int _a,int _b):a(_a),b(_b) {}
	friend inline Value operator +(const Value &x,const Value &y)
	{
		Value ret;
		if (x.a > y.a)
		{
			ret.a = x.a;
			if (x.b > y.a) ret.b = x.b;
			else ret.b = y.a;
		}
		else
		{
			ret.a = y.a;
			if (y.b > x.a) ret.b = y.b;
			else ret.b = x.a;
		}
		return ret;
	}
}tree[maxn*2];

inline void add(int a,int b) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; }
inline void ins(int a,int b) { add(a,b); add(b,a); }

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline int find(const pair <int,int> &key)
{
	int now = (2333*key.first+5003*key.second)%lhh;
	while (true)
	{
		if (Hash[now].first == 0||Hash[now] == key) return now;
		else ++now;
		if (now >= lhh) now -= lhh;
	}
}

inline void getroot(int now,int rest,int fa)
{
	size[now] = 1; large[now] = 0;
	for (int i = side[now];i;i = nxt[i])
	{
		if (vis[toit[i]]||toit[i] == fa) continue;
		getroot(toit[i],rest,now);
		size[now] += size[toit[i]];
		large[now] = max(large[now],size[toit[i]]);
	}
	large[now] = max(large[now],rest-size[now]);
	if (large[now] < large[best]) best = now;
}
inline int find_root(int rest,int now) { best = 0; getroot(now,rest,0); return best; }

inline void dfs(int id,int root,int now,int fa,int dep)
{
	S[id].insert(dep);
	pair <int,int> key = make_pair(root,now); int pos = find(key);
	rechain[pos] = id; depth[pos] = dep; Hash[pos] = key;
	size[now] = 1;
	for (int i = side[now];i;i = nxt[i])
	{
		if (vis[toit[i]]||toit[i] == fa) continue;
		dfs(id,root,toit[i],now,dep+1);	size[now] += size[toit[i]];
	}
}

inline void subdivide(int root)
{
	optimal[root] = -inf; mx[root].insert(-inf);
	L[root] = tot+1;
	for (int i = side[root];i;i = nxt[i])
	{
		if (vis[toit[i]]) continue;
		++tot; dfs(tot,root,toit[i],root,1);
		S[tot].insert(-inf);		
	}
	R[root] = tot; vis[root] = true;
	for (int i = side[root];i;i = nxt[i])
	{
		if (vis[toit[i]]) continue;
		int tmp = find_root(size[toit[i]],toit[i]);
		father[tmp] = root; son[root].push_back(tmp);
		subdivide(tmp);
	}
}

inline void build(int now,int l,int r)
{
	if (l == r)
	{
		tree[now] = Value(*S[l].rbegin(),-inf);
		leaf[l] = now; return;
	}
	int mid = (l+r)>>1;
	build(now<<1,l,mid); build(now<<1|1,mid+1,r);
	tree[now] = tree[now<<1]+tree[now<<1|1];
}

inline Value query(int now,int l,int r,int ql,int qr)
{
	if (l == ql&&r == qr) return tree[now];
	int mid = (l+r)>>1;
	if (qr <= mid) return query(now<<1,l,mid,ql,qr);
	else if (ql > mid) return query(now<<1|1,mid+1,r,ql,qr);
	else return query(now<<1,l,mid,ql,mid)+query(now<<1|1,mid+1,r,mid+1,qr);
}

inline void upd(int &a,int b) { if (a < b) a = b; }

inline void modify(int pos,int dep,bool sign)
{
	if (sign) S[pos].insert(dep); else S[pos].erase(S[pos].find(dep));
	tree[leaf[pos]] = Value(*S[pos].rbegin(),-inf);
	for (int now = leaf[pos]>>1;now;now >>= 1)
		tree[now] = tree[now<<1]+tree[now<<1|1];
}
inline void modify(int pos)
{
	int c = 0;
	if (father[pos]) mx[father[pos]].erase(mx[father[pos]].find(optimal[pos]));
	off[pos] ^= 1; if (off[pos]) nlight++; else nlight--;
	if (L[pos] <= R[pos])
	{
		Value res = query(1,1,tot,L[pos],R[pos]);
		optimal[pos] = max(res.a+res.b,*mx[pos].rbegin());
		if (off[pos]) upd(optimal[pos],res.a);
	}
	if (father[pos]) mx[father[pos]].insert(optimal[pos]);
	for (int now = father[pos];now;now = father[now])
	{
		int t = find(make_pair(now,pos));
		int id = rechain[t],dep = depth[t];
		modify(id,dep,off[pos]);
		if (father[now]) mx[father[now]].erase(mx[father[now]].find(optimal[now]));
		Value res = query(1,1,tot,L[now],R[now]);
		optimal[now] = max(res.a+res.b,*mx[now].rbegin());
		if (off[now]) upd(optimal[now],res.a);
		if (father[now]) mx[father[now]].insert(optimal[now]);
		++c;
	}
}

inline void redfs(int now)
{
	for (int i = 0;i < (int)son[now].size();++i)
		redfs(son[now][i]),mx[now].insert(optimal[son[now][i]]);
	if (L[now] <= R[now])
	{
		Value res = query(1,1,tot,L[now],R[now]);
		optimal[now] = max(res.a+res.b,*mx[now].rbegin());
		if (off[now]) upd(optimal[now],res.a);
	}
}

int main()
{
	// freopen("A.in","r",stdin);
	memset(off,true,sizeof off);
	nlight = N = gi();
	for (int i = 1;i < N;++i) ins(gi(),gi());
	large[0] = inf;
	subdivide(Root = find_root(N,1));
	build(1,1,tot); redfs(Root);
	for (int Q = gi();Q--;)
	{
		char opt; do opt = getchar(); while (opt != 'G'&&opt != 'C');
		if (opt == 'G')
		{
			if (!nlight) puts("-1");
			else if (nlight == 1) puts("0");
			else printf("%d\n",optimal[Root]);
		}
		else modify(gi());
	}
	return 0;
}
