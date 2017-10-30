//建出来的树点的编号i在原图中是redfn[i]
int N,M,Ts,cnt,side[maxn],nxt[maxn],toit[maxn],dfn[maxn],redfn[maxn],idom[maxn],best[maxn],semi[maxn];
int ans[maxn],anc[maxn],fa[maxn],child[maxn],size[maxn]; vector <int> prod[maxn],bucket[maxn],son[maxn];

inline void init()
{
	cnt = 1; memset(side,0,sizeof side); memset(ans,0,sizeof ans);
	for (int i = 0;i <= N;++i) prod[i].clear(),bucket[i].clear(),son[i].clear();
}

inline void add(int a,int b) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; }

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline void dfs(int now)
{
	dfn[now] = ++Ts; redfn[Ts] = now;
	anc[Ts] = idom[Ts] = child[Ts] = size[Ts] = 0;
	semi[Ts] = best[Ts] = Ts;
	for (int i = side[now];i;i = nxt[i])
	{
		if (!dfn[toit[i]])
			dfs(toit[i]),fa[dfn[toit[i]]] = dfn[now];
		prod[dfn[toit[i]]].push_back(dfn[now]);
	}
}

inline void compress(int now)
{
	if (anc[anc[now]] != 0)
	{
		compress(anc[now]);
		if (semi[best[now]] > semi[best[anc[now]]])
			best[now] = best[anc[now]];
		anc[now] = anc[anc[now]];
	}
}

inline int eval(int now)
{
	if (!anc[now]) return now;
	else
	{
		compress(now);
		return semi[best[anc[now]]] >= semi[best[now]]?best[now]:best[anc[now]];
	}
}

inline void link(int v,int w)
{
	int s = w;
	while (semi[best[w]] < semi[best[child[w]]])
	{
		if (size[s]+size[child[child[s]]] >= 2*size[child[s]])
			anc[child[s]] = s,child[s] = child[child[s]];
		else size[child[s]] = size[s],s = anc[s] = child[s];
	}
	best[s] = best[w]; size[v] += size[w];
	if (size[v] < 2*size[w]) swap(s,child[v]);
	while (s) anc[s] = v,s = child[s];
}

inline void lengauer_tarjan()
{
	memset(dfn,0,sizeof dfn); memset(fa,-1,sizeof fa); Ts = 0;
	dfs(N); fa[1] = 0;
	for (int w = Ts;w > 1;--w)
	{
		for (auto x:prod[w])
		{
			int u = eval(x);
			if (semi[w] > semi[u]) semi[w] = semi[u];
		}
		bucket[semi[w]].push_back(w);
		link(fa[w],w); if (!fa[w]) continue;
		for (auto x:bucket[fa[w]])
		{
			int u = eval(x);
			if (semi[u] < fa[w]) idom[x] = u;
			else idom[x] = fa[w];
		}
		bucket[fa[w]].clear();
	}
	for (int w = 2;w <= Ts;++w)
		if (idom[w] != semi[w])
			idom[w] = idom[idom[w]];
	idom[1] = 0;
	for (int i = Ts;i > 1;--i)
	{
		if (fa[i] == -1) continue;
		son[idom[i]].push_back(i);
	}
}

// 例题：询问i号点到N号点所有必经点编号和
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 100010;
int N,M,Ts,cnt,side[maxn],nxt[maxn],toit[maxn],dfn[maxn],redfn[maxn],idom[maxn],best[maxn],semi[maxn];
int ans[maxn],anc[maxn],fa[maxn],child[maxn],size[maxn]; vector <int> prod[maxn],bucket[maxn],son[maxn];

inline void init()
{
	cnt = 1; memset(side,0,sizeof side); memset(ans,0,sizeof ans);
	for (int i = 0;i <= N;++i) prod[i].clear(),bucket[i].clear(),son[i].clear();
}

inline void add(int a,int b) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; }

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline void dfs(int now)
{
	dfn[now] = ++Ts; redfn[Ts] = now;
	anc[Ts] = idom[Ts] = child[Ts] = size[Ts] = 0;
	semi[Ts] = best[Ts] = Ts;
	for (int i = side[now];i;i = nxt[i])
	{
		if (!dfn[toit[i]])
			dfs(toit[i]),fa[dfn[toit[i]]] = dfn[now];
		prod[dfn[toit[i]]].push_back(dfn[now]);
	}
}

inline void compress(int now)
{
	if (anc[anc[now]] != 0)
	{
		compress(anc[now]);
		if (semi[best[now]] > semi[best[anc[now]]])
			best[now] = best[anc[now]];
		anc[now] = anc[anc[now]];
	}
}

inline int eval(int now)
{
	if (!anc[now]) return now;
	else
	{
		compress(now);
		return semi[best[anc[now]]] >= semi[best[now]]?best[now]:best[anc[now]];
	}
}

inline void link(int v,int w)
{
	int s = w;
	while (semi[best[w]] < semi[best[child[w]]])
	{
		if (size[s]+size[child[child[s]]] >= 2*size[child[s]])
			anc[child[s]] = s,child[s] = child[child[s]];
		else size[child[s]] = size[s],s = anc[s] = child[s];
	}
	best[s] = best[w]; size[v] += size[w];
	if (size[v] < 2*size[w]) swap(s,child[v]);
	while (s) anc[s] = v,s = child[s];
}

inline void lengauer_tarjan()
{
	memset(dfn,0,sizeof dfn); memset(fa,-1,sizeof fa); Ts = 0;
	dfs(N); fa[1] = 0;
	for (int w = Ts;w > 1;--w)
	{
		for (auto x:prod[w])
		{
			int u = eval(x);
			if (semi[w] > semi[u]) semi[w] = semi[u];
		}
		bucket[semi[w]].push_back(w);
		link(fa[w],w); if (!fa[w]) continue;
		for (auto x:bucket[fa[w]])
		{
			int u = eval(x);
			if (semi[u] < fa[w]) idom[x] = u;
			else idom[x] = fa[w];
		}
		bucket[fa[w]].clear();
	}
	for (int w = 2;w <= Ts;++w)
		if (idom[w] != semi[w])
			idom[w] = idom[idom[w]];
	idom[1] = 0;
	for (int i = Ts;i > 1;--i)
	{
		if (fa[i] == -1) continue;
		son[idom[i]].push_back(i);
	}
}

inline void get_ans(int now)
{
	ans[redfn[now]] += redfn[now];
	for (auto x:son[now])
		ans[redfn[x]] += ans[redfn[now]],get_ans(x);
}	

int main()
{
	//freopen("I.in","r",stdin);
	while (scanf("%d %d",&N,&M) != EOF)
	{
		init();
		for (int i = 1,a,b;i <= M;++i)
			a = gi(),b = gi(),add(a,b);
		lengauer_tarjan(); get_ans(1);
		for (int i = 1;i <= N;++i)
			printf("%d%c",ans[i]," \n"[i == N]);
	}
	return 0;
}
