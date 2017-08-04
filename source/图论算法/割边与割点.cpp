// 求割边和割点
const int maxn = 200010;
int N,M,cnt,Ts,dfn[maxn],low[maxn],nxt[maxn];
int toit[maxn],side[maxn];
bool bridge[maxn],cut[maxn];

inline void dfs(int now,int fa)
{
	dfn[now] = low[now] = ++Ts; int child = 0;
	for (int i = side[now];i;i = nxt[i])
	{
		if (toit[i] == fa) continue;
		if (!dfn[toit[i]])
		{
			dfs(toit[i],now); ++child;
			low[now] = min(low[now],low[toit[i]]);
			if (low[toit[i]] > dfn[now]) bridge[i] = true;
			if (low[toit[i]] >= dfn[now]) cut[now] = true;
		}
		else low[now] = min(low[now],dfn[toit[i]]);
	}
	if (!fa&&child == 1) cut[now] = false;
}
