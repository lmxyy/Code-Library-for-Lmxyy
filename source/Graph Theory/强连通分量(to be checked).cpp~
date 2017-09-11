inline void dfs(int now)
{
    dfn[now] = low[now] = ++cnt;
    for (int i = side[now];i;i = next[i])
    {
        if (toit[i] == fa[now]) continue;
        if (!dfn[toit[i]]) fa[toit[i]] = now,dfs(toit[i]);
        low[now] = min(low[toit[i]],low[now]);
        if (dfn[now] < low[toit[i]])
			ans = max(ans,f[now]+f[toit[i]]+1),f[now] = max(f[now],f[toit[i]]+1);
    }
    for (int i = side[now];i;i = next[i])
        if (toit[i] != fa[now]&&dfn[toit[i]]>dfn[now]&&fa[toit[i]] != now)
			dp(now,toit[i]);
}
