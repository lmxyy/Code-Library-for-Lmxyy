// UOJ - 3
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 200010,inf = 1<<29;
int N,M,A[maxn],B[maxn],fa[maxn],ch[maxn][2];
int stk[maxn],father[maxn],ans = inf; bool rev[maxn];

inline int find(int a) { if (father[a] != a) return father[a] = find(father[a]); return a; }

struct Value
{
	int ma,mb,id;
	inline Value(int _ma = 0,int _mb = 0,int _id = 0):ma(_ma),mb(_mb),id(_id) {}
	friend inline Value operator +(const Value &a,const Value &b)
	{
		Value ret = Value(max(a.ma,b.ma),max(a.mb,b.mb),a.id);
		if (B[a.id] < B[b.id]) ret.id = b.id;
		return ret;
	}
	inline Value merge(int i)
	{
		Value ret = Value(max(ma,A[i]),max(mb,B[i]),id);
		if (B[i] > B[id]) ret.id = i; 
		return ret;
	}
}val[maxn];

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

struct Edge
{
	int x,y,a,b;
	inline Edge(int _x = 0,int _y = 0,int _a = 0,int _b = 0):x(_x),y(_y),a(_a),b(_b) {}
	inline void read() { x = gi(),y = gi(),a = gi(),b = gi(); }
	friend inline bool operator <(const Edge &s,const Edge &t) { return s.a < t.a; }
}edge[maxn];

inline bool isroot(int a) { return ch[fa[a]][0] != a&&ch[fa[a]][1] != a; }

inline void update(int x) { val[x] = (val[ch[x][0]]+val[ch[x][1]]).merge(x); }
inline void pushdown(int x)
{
	if (rev[x])
	{
		int &lc = ch[x][0],&rc = ch[x][1];
		swap(lc,rc);
		if (lc) rev[lc] ^= 1;
		if (rc) rev[rc] ^= 1;
		rev[x] = false;
	}
}

inline void rotate(int x)
{
	int y = fa[x],z = fa[y],l = ch[y][1] == x,r = l^1;
	if (!isroot(y)) ch[z][ch[z][1] == y] = x; fa[x] = z;
	if (ch[x][r]) fa[ch[x][r]] = y; ch[y][l] = ch[x][r];
	fa[y] = x; ch[x][r] = y; update(y); update(x);
}
inline void splay(int x)
{
	int top = 0,i;
	for (i = x;!isroot(i);i = fa[i]) stk[++top] = i; stk[++top] = i;
	while (top) pushdown(stk[top--]);
	while (!isroot(x))
	{
		int y = fa[x],z = fa[y];
		if (!isroot(y))
		{
			if ((ch[y][0] == x)^(ch[z][0] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}

inline int access(int x)
{
	int t = 0;
	for (t = 0;x;t = x,x = fa[x])
		splay(x),ch[x][1] = t,update(x);
	return t;
}
inline int evert(int x) { int t; rev[t = access(x)] ^= 1; return t; }
inline int getroot(int x)
{
	x = access(x);
	while (pushdown(x),ch[x][0]) x = ch[x][0];
	return x;
}
inline void cut(int x,int y)
{
	evert(x); access(y); splay(y);
	if (ch[y][0] != x||ch[x][1] != 0) return;
	ch[y][0] = fa[x] = 0; update(x); update(y);
}
inline void link(int x,int y) { fa[evert(x)] = y; }

inline Value query(int x,int y) { evert(x); return val[access(y)]; }

int main()
{
	freopen("3.in","r",stdin);
	N = gi(),M = gi();
	for (int i = 1;i <= M;++i) edge[i].read();
	sort(edge+1,edge+M+1);
	for (int i = 0;i <= N;++i)
		A[i] = B[i] = -inf,val[i] = Value(A[i],B[i],i),father[i] = i;
	for (int i = 1;i <= M;++i)
		A[i+N] = edge[i].a,B[i+N] = edge[i].b,val[i+N] = Value(A[i+N],B[i+N],i+N);
	for (int i = 1;i <= M;++i)
	{
		if (edge[i].x == edge[i].y) continue;
		if (find(edge[i].x) == find(edge[i].y))
		{
			Value res = query(edge[i].x,edge[i].y); int id = res.id-N;
			if (edge[i].b < edge[id].b)
			{
				cut(edge[id].x,id+N),cut(edge[id].y,id+N);
				link(edge[i].x,i+N),link(edge[i].y,i+N);
			}
		}
		else link(edge[i].x,i+N),link(i+N,edge[i].y),father[find(edge[i].x)] = find(edge[i].y);
		if (find(1) == find(N))
		{
			Value res = query(1,N);
			ans = min(ans,res.ma+res.mb);
		}
	}
	if (ans == inf) ans = -1;
	printf("%d\n",ans);
	return 0;
}
