// bzoj2330
#include<iostream>
#include<stack>
#include<queue>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define maxn 100010
#define maxm 200010
int cnt,side[maxn],next[maxm],toit[maxm],cost[maxm],d[maxn];
int nside[maxn],nnext[maxm],ntoit[maxm],ncost[maxm],m,tot;
int dfn[maxn],low[maxn],sum[maxn],id[maxn],arr[maxn],n;
bool vis[maxn]; stack <int> S;
													  
inline void add(int a,int b,int c)
{
	next[++cnt] = side[a]; side[a] = cnt;
	toit[cnt] = b; cost[cnt] = c;
}

inline void ins(int a,int b,int c)
{
	nnext[++cnt] = nside[a]; nside[a] = cnt;
	ntoit[cnt] = b; ncost[cnt] = c; ++d[b];
}

inline void dfs(int now)
{
	S.push(now); dfn[now] = low[now] = ++cnt;
	for (int i = side[now];i;i = next[i])
		if (!vis[toit[i]])
		{
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

inline bool rebuild()
{
	cnt = 0;
	for (int i = 1;i <= n;++i)
		for (int j = side[i];j;j = next[j])
		{
			if (id[toit[j]] == id[i]) sum[id[i]] += cost[j];
			else ins(id[i],id[toit[j]],cost[j]);
		}
	for (int i = 1;i <= tot;++i) if (sum[i]) return false;
	return true;
}

inline void topsort()
{
	queue <int> team;
	for (int i = 1;i <= tot;++i) if (!d[i]) team.push(i),arr[i] = 1;
	while (!team.empty())
	{
		int now = team.front(); team.pop();
		for (int i = nside[now];i;i = nnext[i])
		{
			arr[ntoit[i]] = max(arr[now]+ncost[i],arr[ntoit[i]]);
			if (!--d[ntoit[i]]) team.push(ntoit[i]);
		}
	}
}

int main()
{
	freopen("2330.in","r",stdin);
	freopen("2330.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1;i <= m;++i)
	{
		int x,a,b; scanf("%d %d %d",&x,&a,&b);
		if (x == 1) add(a,b,0),add(b,a,0);
		else if (x == 2) add(a,b,1);
		else if (x == 3) add(b,a,0);
		else if (x == 4) add(b,a,1);
		else add(a,b,0);
	}
	cnt = 0; for (int i = n;i;--i) if (!dfn[i]) dfs(i);
	if (!rebuild()) printf("-1"),exit(0); 
	topsort();
	long long ans = 0;
	for (int i = 1;i <= n;++i) ans += (long long)arr[id[i]];
	printf("%lld",ans);
	fclose(stdin); fclose(stdout);
	return 0;
}
