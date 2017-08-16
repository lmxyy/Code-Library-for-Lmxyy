#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define maxn (100010)
int best,cnt = 1,side[maxn],toit[maxn],next[maxn],large[maxn];
int sd[maxn],d[maxn],ns,nd,ans,N,K,size[maxn]; bool vis[maxn];

inline void add(int a,int b)
{ next[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; }
inline void ins(int a,int b)
{ add(a,b); add(b,a); }

inline void getroot(int now,int fa,int rest)
{
	size[now] = 1; large[now] = 0;
	for (int i = side[now];i;i = next[i])
	{
		if (toit[i] == fa||vis[toit[i]]) continue;
		getroot(toit[i],now,rest);
		size[now] += size[toit[i]];
		large[now] = max(large[now],size[toit[i]]);
	}
	large[now] = max(large[now],rest-size[now]);
	if (large[now] < large[best]) best = now;
}
inline int find_root(int now,int rest)
{ best = 0; getroot(now,0,rest); return best; }

inline void dfs(int now,int fa,int dep)
{
	size[now] = 1; nd = max(dep,nd); ++d[dep];
	for (int i = side[now];i;i = next[i])
		if (toit[i] != fa&&!vis[toit[i]])
			dfs(toit[i],now,dep+1),size[now] += size[toit[i]];
}

inline void cut(int now)
{
	vis[now] = true;
	for (int i = side[now];i;i = next[i])
	{
		if (vis[toit[i]]) continue;
		dfs(toit[i],now,1); ans += d[K];
		for (int j = 1;j < K;++j) ans += d[j]*sd[K-j];
		for (int j = 1;j <= nd;++j) sd[j] += d[j],d[j] = 0;
		ns = max(nd,ns); nd = 0;
	}
	memset(sd,0,4*(ns+1)); ns = 0;
	for (int i = side[now];i;i = next[i])
		if (!vis[toit[i]])
			cut(find_root(toit[i],size[toit[i]]));
}

int main()
{
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	scanf("%d %d",&N,&K);
	for (int i = 1,a,b;i < N;++i) scanf("%d %d",&a,&b),ins(a,b);
	large[0] = 1<<30; cut(find_root(1,N));
	printf("%d",ans);
	fclose(stdin); fclose(stdout);
	return 0;
}
