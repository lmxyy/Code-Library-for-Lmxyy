#include<stack>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define maxn 210
#define maxm 2010
int n,m,cnt,side[maxn],next[maxm],toit[maxm],dfn[maxn],id[maxn];
int tot,low[maxn],d[maxn],DFN;
stack <int> S; bool vis[maxn];

inline void init()
{
	DFN = tot = cnt = 0; memset(vis,false,2*(n+4));
	memset(side,0,8*(n+4)); memset(dfn,0,8*(n+4)); 
}

inline void add(int a,int b) { next[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; }

inline void dfs(int now)
{
	S.push(now); dfn[now] = low[now] = ++DFN;
	for (int i = side[now];i;i = next[i])
	{
		if (vis[toit[i]]) continue;
		if (!dfn[toit[i]]) dfs(toit[i]);
		low[now] = min(low[toit[i]],low[now]);
	}
	if (low[now] == dfn[now])
	{
		++tot;
		while (S.top() != now) id[S.top()] = tot,vis[S.top()] = true,S.pop();
		id[S.top()] = tot,vis[S.top()] = true,S.pop();
	}
}

int main()
{
	freopen("1823.in","r",stdin);
	freopen("1823.out","w",stdout);
	int T; scanf("%d",&T);
	while (T--)
	{
		scanf("%d %d\n",&n,&m);
		init();
		while (m--)
		{
			char c1,c2; int a,b; bool o1,o2;
			scanf("%c%d %c%d\n",&c1,&a,&c2,&b);
			o1 = c1 == 'h'; o2 = c2 == 'h';
			add((o1^1)*n+a,o2*n+b);
			add((o2^1)*n+b,o1*n+a);
		}
		int i;
		for (i = 1;i <= n<<1;++i) if (!dfn[i]) dfs(i);
		for (i = 1;i <= n;++i) if (id[i] == id[i+n]) { printf("BAD\n"); break; }
		if (i <= n) continue;
		printf("GOOD\n");
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
