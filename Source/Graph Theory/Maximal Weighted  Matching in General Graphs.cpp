// UOJ - 81
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;

typedef long long ll;
const int maxn = 410,inf = (1<<30)-1;
int N,M,nx,label[maxn*2],match[maxn*2],slack[maxn*2],st[maxn*2],pa[maxn*2];
int flower_from[maxn*2][maxn],S[maxn*2],vis[maxn*2];
vector <int> flower[maxn*2]; queue <int> team;
struct Edge
{
	int u,v,w;
	inline Edge() = default;
	inline Edge(int _u,int _v,int _w):u(_u),v(_v),w(_w) {}
}G[maxn*2][maxn*2];

inline void init()
{
	for (int i = 1;i <= N;++i)
		for (int j = 1;j <= N;++j)
			G[i][j] = Edge(i,j,0);
}

inline int e_delta(const Edge &e) { return label[e.u]+label[e.v]-G[e.u][e.v].w*2; }
inline void update_slack(int u,int x) { if (!slack[x]||e_delta(G[u][x]) < e_delta(G[slack[x]][x])) slack[x] = u; }
inline void set_slack(int x)
{
	slack[x] = 0;
	for (int i = 1;i <= N;++i)
		if (G[i][x].w > 0&&st[i] != x&&S[st[i]] == 0)
			update_slack(i,x);
}
inline void q_push(int x)
{
	if (x <= N) team.push(x);
	else for (auto v:flower[x]) q_push(v);
}
inline void set_st(int x,int b)
{
	st[x] = b; if (x <= N) return;
	for (auto v:flower[x]) set_st(v,b);
}
inline int get_pr(int b,int xr)
{
	int pr = find(flower[b].begin(),flower[b].end(),xr)-flower[b].begin();
	if (pr&1)
	{
		reverse(flower[b].begin()+1,flower[b].end());
		return (int)flower[b].size()-pr;
	}
	else return pr;
}
inline void set_match(int u,int v)
{
	match[u] = G[u][v].v;
	if (u > N)
	{
		Edge e = G[u][v];
		int xr = flower_from[u][e.u],pr = get_pr(u,xr);
		for (int i = 0;i < pr;++i) set_match(flower[u][i],flower[u][i^1]);
		set_match(xr,v);
		rotate(flower[u].begin(),flower[u].begin()+pr,flower[u].end());
	}
}
inline void augment(int u,int v)
{
	while (true)
	{
		int xnv = st[match[u]];
		set_match(u,v);
		if (!xnv) return;
		set_match(xnv,st[pa[xnv]]);
		u = st[pa[xnv]],v = xnv;
	}
}
inline int get_lca(int u,int v)
{
	static int t = 0;
	for (++t;u||v;swap(u,v))
	{
		if (u == 0) continue;
		if (vis[u] == t) return u;
		vis[u] = t; u = st[match[u]];
		if (u) u = st[pa[u]];
	}
	return 0;
}
inline void add_blossom(int u,int lca,int v)
{
	int b = N+1;
	while (b <= nx&&st[b]) ++b;
	if (b > nx) ++nx;
	label[b] = S[b] = 0; match[b] = match[lca];
	flower[b].clear(); flower[b].push_back(lca);
	for (int x = u,y;x != lca;x = st[pa[y]])
		flower[b].push_back(x),flower[b].push_back(y = st[match[x]]),q_push(y);
	reverse(flower[b].begin()+1,flower[b].end());
	for (int x = v,y;x != lca;x = st[pa[y]])
		flower[b].push_back(x),flower[b].push_back(y = st[match[x]]),q_push(y);
	set_st(b,b);
	for (int x = 1;x <= nx;++x) G[b][x].w = G[x][b].w = 0;
	for (int x = 1;x <= N;++x) flower_from[b][x] = 0;
	for (auto xs:flower[b])
	{
		for (int x = 1;x <= nx;++x)
			if (G[b][x].w == 0||e_delta(G[xs][x]) < e_delta(G[b][x]))
				G[b][x] = G[xs][x],G[x][b] = G[x][xs];
		for (int x = 1;x <= N;++x)
			if (flower_from[xs][x]) flower_from[b][x] = xs;
	}
	set_slack(b);
}
inline void expand_blossom(int b)
{
	for (auto v:flower[b]) set_st(v,v);
	int xr = flower_from[b][G[b][pa[b]].u],pr = get_pr(b,xr);
	for (int i = 0;i < pr;i += 2)
	{
		int xs = flower[b][i],xns = flower[b][i+1];
		pa[xs] = G[xns][xs].u;
		S[xs] = 1,S[xns] = 0;
		slack[xs] = 0,set_slack(xns);
		q_push(xns);
	}
	S[xr] = 1,pa[xr] = pa[b];
	for (int i = pr+1;i < (int)flower[b].size();++i)
	{
		int xs = flower[b][i];
		S[xs] = -1,set_slack(xs);
	}
	st[b] = 0;
}
inline bool on_found_edge(const Edge &e)
{
	int u = st[e.u],v = st[e.v];
	if (S[v] == -1)
	{
		pa[v] = e.u,S[v] = 1;
		int nu = st[match[v]];
		slack[v] = slack[nu] = 0;
		S[nu] = 0,q_push(nu);
	}
	else if (S[v] == 0)
	{
		int lca = get_lca(u,v);
		if (!lca) return augment(u,v),augment(v,u),true;
		else add_blossom(u,lca,v);
	}
	return false;
}
inline bool matching()
{
	memset(S+1,-1,sizeof(int)*nx);
	memset(slack+1,0,sizeof(int)*nx);
	while (!team.empty()) team.pop();
	for (int x = 1;x <= nx;++x)
		if (st[x] == x&&!match[x]) pa[x] = 0,S[x] = 0,q_push(x);
	if (team.empty()) return false;
	while (true)
	{
		while (!team.empty())
		{
			int u = team.front(); team.pop();
			if (S[st[u]] == 1) continue;
			for (int v = 1;v <= N;++v)
				if (G[u][v].w > 0&&st[u] != st[v])
				{
					if (e_delta(G[u][v]) == 0) { if (on_found_edge(G[u][v])) return true; }
					else update_slack(u,st[v]);
				}
		}
		int d = inf;
		for (int b = N+1;b <= nx;++b)
			if (st[b] == b&&S[b] == 1) d = min(d,label[b]/2);
		for (int x = 1;x <= nx;++x)
			if (st[x] == x&&slack[x])
			{
				if (S[x] == -1) d = min(d,e_delta(G[slack[x]][x]));
				else if (S[x] == 0) d = min(d,e_delta(G[slack[x]][x])/2);
			}
		for (int u = 1;u <= N;++u)
		{
			if (S[st[u]] == 0)
			{
				if (label[u] <= d) return 0;
				else label[u] -= d;
			}
			else if (S[st[u]] == 1) label[u] += d;
		}
		for (int b = N+1;b <= nx;++b)
			if (st[b] == b)
			{
				if (S[st[b]] == 0) label[b] += d*2;
				else if (S[st[b]] == 1) label[b] -= d*2;
			}
		while (!team.empty()) team.pop();
		for (int x = 1;x <= nx;++x)
			if (st[x] == x&&slack[x]&&st[slack[x]] != x&&e_delta(G[slack[x]][x]) == 0)
				if (on_found_edge(G[slack[x]][x])) return true;
		for (int b = N+1;b <= nx;++b)
			if (st[b] == b&&S[b] == 1&&label[b] == 0) expand_blossom(b);
	}
}
inline pair <ll,int> weight_blossom()
{
	memset(match+1,0,sizeof(int)*N); nx = N;
	int nmatch = 0; ll sum = 0;
	for (int i = 0;i <= N;++i) st[i] = i,flower[i].clear();
	int mx = 0;
	for (int u = 1;u <= N;++u)
		for (int v = 1;v <= N;++v)
		{
			flower_from[u][v] = (u == v?u:0);
			mx = max(mx,G[u][v].w);
		}
	for (int u = 1;u <= N;++u) label[u] = mx;
	while (matching()) ++nmatch;
	for (int u = 1;u <= N;++u)
		if (match[u]&&match[u] < u)
			sum += G[u][match[u]].w;
	return make_pair(sum,nmatch);
}

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

int main()
{
	freopen("81.in","r",stdin);
	N = gi(),M = gi();
	init();
	for (int i = 1;i <= M;++i)
	{
		int u = gi(),v = gi();
		G[u][v].w = G[v][u].w = gi();
	}
	cout << weight_blossom().first << endl;
	for (int i = 1;i <= N;++i)
		printf("%d%c",match[i]," \n"[i == N]);
	return 0;
}
