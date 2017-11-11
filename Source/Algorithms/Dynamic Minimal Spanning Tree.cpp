// 每次修改一条边，每次修改一条边权值，求最小生成树
// BZOJ 2001
#include<algorithm>
#include<cstring>
#include<vector>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

typedef long long ll;
const int maxn = 100010; const ll inf = 1LL<<40;
int N,M,Q,father[maxn],cnt[maxn],reid[maxn]; ll ans[maxn];

inline int find(int a) { if (father[a] != a) return father[a] = find(father[a]); return father[a]; }

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
	int a,b,id; ll c;
	inline Edge() = default;
	inline Edge(int _a,int _b,int _id,ll _c):a(_a),b(_b),id(_id),c(_c) {}
	inline void read(int i) { a = gi(),b = gi(),c = gi(); id = i; }
	friend inline bool operator <(const Edge &x,const Edge &y) { return x.c < y.c; }	
}edge[22][maxn],tmp[maxn],bac[maxn];

struct Operation
{
	int x; ll y;
	inline Operation() = default;
	inline Operation(int _x,ll _y):x(_x),y(_y) {}
	inline void read() { x = gi(),y = gi(); }
}opt[maxn];

inline void construct(int &tot,ll &sum)
{
	sort(tmp+1,tmp+tot+1);
	for (int i = 1;i <= tot;++i)
		father[tmp[i].a] = tmp[i].a,father[tmp[i].b] = tmp[i].b;
	vector <Edge> vec;
	for (int i = 1;i <= tot;++i)
	{
		int u = find(tmp[i].a),v = find(tmp[i].b);
		if (u != v) father[u] = v,vec.push_back(tmp[i]);
	}
	for (int i = 0;i < (int)vec.size();++i)
		father[vec[i].a] = vec[i].a,father[vec[i].b] = vec[i].b;
	for (int i = 0;i < (int)vec.size();++i)
	{
		Edge e = vec[i];
		if (e.c != -inf) father[find(e.a)] = find(e.b),sum += e.c;
	}
	vec.clear();
	for (int i = 1;i <= tot;++i)
	{
		int u = find(tmp[i].a),v = find(tmp[i].b);
		if (u != v)
		{
			tmp[i].a = u,tmp[i].b = v;
			vec.push_back(tmp[i]);
		}
	}
	for (int i = 0;i < (int)vec.size();++i) tmp[i+1] = vec[i];
	for (int i = 1;i <= tot;++i) reid[tmp[i].id] = i;
	tot = (int)vec.size();
}

inline void destruct(int &tot)
{
	sort(tmp+1,tmp+tot+1);
	for (int i = 1;i <= tot;++i)
		father[tmp[i].a] = tmp[i].a,father[tmp[i].b] = tmp[i].b;
	vector <Edge> vec;
	for (int i = 1;i <= tot;++i)
	{
		int u = find(tmp[i].a),v = find(tmp[i].b);
		if (u != v) father[u] = v,vec.push_back(tmp[i]);
		else if (tmp[i].c == inf) vec.push_back(tmp[i]);
	}
	for (int i = 0;i < (int)vec.size();++i) tmp[i+1] = vec[i];
	tot = (int)vec.size();
}

inline void work(int l,int r,int dep,ll sum)
{
	int tot = cnt[dep];
	for (int i = 1;i <= tot;++i) tmp[i] = edge[dep][i];
	if (l == r)
	{
		bac[opt[l].x].c = opt[l].y;
		for (int i = 1;i <= tot;++i)
		{
			tmp[i].c = bac[tmp[i].id].c;
			father[tmp[i].a] = tmp[i].a;
			father[tmp[i].b] = tmp[i].b;
		}
		sort(tmp+1,tmp+tot+1);
		for (int i = 1;i <= tot;++i)
		{
			int u = find(tmp[i].a),v = find(tmp[i].b);
			if (u != v) sum += tmp[i].c,father[u] = v;
		}
		ans[l] = sum; return;
	}
	for (int i = 1;i <= tot;++i)
		tmp[i].c = bac[tmp[i].id].c,reid[tmp[i].id] = i;
	for (int i = l;i <= r;++i) tmp[reid[opt[i].x]].c = -inf;
	construct(tot,sum);
	for (int i = l;i <= r;++i)
		tmp[reid[opt[i].x]].c = inf;
	destruct(tot);
	for (int i = 1;i <= tot;++i) edge[dep+1][i] = tmp[i];
	int mid = (l+r)>>1; cnt[dep+1] = tot;
	work(l,mid,dep+1,sum); work(mid+1,r,dep+1,sum);
}

int main()
{
	// freopen("B.in","r",stdin);
	N = gi(),M = gi(),Q = gi();
	for (int i = 1;i <= M;++i) bac[i].read(i),edge[0][i] = bac[i];
	for (int i = 1;i <= Q;++i) opt[i].read();
	for (int i = 1;i <= N;++i) father[i] = i;
	cnt[0] = M; work(1,Q,0,0);
	for (int i = 1;i <= Q;++i) printf("%lld\n",ans[i]);
	return 0;
}
