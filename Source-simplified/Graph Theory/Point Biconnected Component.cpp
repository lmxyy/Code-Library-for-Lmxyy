// Source: HackerRank - bonnie-and-clyde
#include<algorithm>
#include<vector>
#include<stack>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 400010;
int N,M,Q,cnt = 1,side[maxn],toit[maxn],nxt[maxn],f[maxn][25],father[maxn],low[maxn];
int tot,dep[maxn],dfn[maxn],nside[maxn],ntoit[maxn],nnxt[maxn]; bool cut[maxn];
stack <int> S; vector <int> bel[maxn],bcc[maxn]; bool vis[maxn];

inline int find(int a) { if (father[a] != a) father[a] = find(father[a]); return father[a]; }

inline void add(int a,int b) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; }
inline void ins(int a,int b) { add(a,b); add(b,a); }
inline void nadd(int a,int b) { nnxt[++cnt] = nside[a]; nside[a] = cnt; ntoit[cnt] = b; }
inline void nins(int a,int b) { nadd(a,b); nadd(b,a); }

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline void tj(int now,int fa)
{
	dfn[now] = low[now] = ++cnt; int child = 0;
	for (int i = side[now];i;i = nxt[i])
	{
		if (toit[i] == fa) continue;
		if (!dfn[toit[i]])
		{
			S.push(i>>1); tj(toit[i],now); ++child;
			low[now] = min(low[now],low[toit[i]]);
			if (low[toit[i]] >= dfn[now])
			{
				cut[now] = true; ++tot;
				while (true)
				{
					int t = S.top(); S.pop();
					bel[toit[t<<1]].push_back(tot);	bel[toit[t<<1|1]].push_back(tot);
					bcc[tot].push_back(toit[t<<1]); bcc[tot].push_back(toit[t<<1|1]);
					if (t == (i>>1)) break;
				}
			}
		}
		else low[now] = min(low[now],dfn[toit[i]]);
	}
	if (!fa&&child == 1) cut[now] = false;
}

inline void build()
{
	vector <int> cuts; cnt = 1;
	for (int i = 1;i <= tot;++i)
	{
		sort(bcc[i].begin(),bcc[i].end());
		bcc[i].erase(unique(bcc[i].begin(),bcc[i].end()),bcc[i].end());
	}
	for (int i = 1;i <= N;++i) if (cut[i]) cuts.push_back(i);
	for (auto x:cuts)
	{
		sort(bel[x].begin(),bel[x].end());
		bel[x].erase(unique(bel[x].begin(),bel[x].end()),bel[x].end());
		++tot; for (auto y:bel[x]) nins(tot,y);
		bel[x].clear(); bel[x].push_back(tot); bcc[tot].push_back(x);
	}
}

inline void dfs(int now)
{
	vis[now] = true;
	for (int i = 1;(1<<i) <= dep[now];++i) f[now][i] = f[f[now][i-1]][i-1];
	for (int i = nside[now];i;i = nnxt[i])
	{
		if (vis[ntoit[i]]) continue; f[ntoit[i]][0] = now;
		dep[ntoit[i]] = dep[now]+1; dfs(ntoit[i]);
	}
}

inline int jump(int a,int b) { for (int i = 0;b;++i,b >>= 1) if (b&1) a = f[a][i]; return a; }
inline int lca(int a,int b)
{
	if (dep[a] < dep[b]) swap(a,b);
	a = jump(a,dep[a]-dep[b]); if (a == b) return a;
	for (int i = 0;i >= 0;)
	{
		if (f[a][i] != f[b][i]) a = f[a][i],b = f[b][i],++i;
		else --i;
	}
	return f[a][0];
}

inline bool check(int u,int v,int w)
{
	if (find(u) != find(v)||find(v) != find(w)) return false;
	if (u == w||v == w) return true; if (u == v) return false;
	int uu = bel[u][0],vv = bel[v][0],ww = bel[w][0],su,sv;
	if (uu == ww||vv == ww) return true;
	if (lca(uu,ww) == ww) su = jump(uu,dep[uu]-dep[ww]-1); else su = f[ww][0];
	if (lca(vv,ww) == ww) sv = jump(vv,dep[vv]-dep[ww]-1); else sv = f[ww][0];
	if (su == sv)
	{
		if (!cut[w]) return false;
		else
		{
			if (su == uu||sv == vv) return true; int ssu,ssv;
			if (lca(su,uu) == su) ssu = jump(uu,dep[uu]-dep[su]-1); else ssu = f[su][0];
			if (lca(sv,vv) == sv) ssv = jump(vv,dep[vv]-dep[sv]-1); else ssv = f[sv][0];
			if (ssu == ssv) return false; else return true;
		}
	}
	else return true;
}

int main()
{
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	N = gi(); M = gi(); Q = gi();
	for (int i = 1;i <= N;++i) father[i] = i;
	for (int i = 1,a,b;i <= M;++i)
	{
		ins(a = gi(),b = gi());
		a = find(a),b = find(b);
		if (a != b) father[a] = b;
	}
	cnt = 0; for (int i = 1;i <= N;++i) if (!dfn[i]) tj(i,0);
	build(); for (int i = 1;i <= N;++i) if (!vis[i]) dfs(i);
	while (Q--)
	{
		int u = gi(),v = gi(),w = gi();
		if (check(u,v,w)) puts("YES"); else puts("NO");
	}
	return 0;
}
