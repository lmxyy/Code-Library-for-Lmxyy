int dfn[maxn],low[maxn],timestamp;
stack <int> stk; vector <int> scc[maxn];
void tarjan(int now)
{
	dfn[now] = low[now] = ++timestamp;
	stk.push(now);
	for (int i = side[now];i;i = nxt[i])
	{
		if (!dfn[toit[i]])
			tarjan(toit[i]),low[now] = min(low[now],low[toit[i]]);
		else if (!bel[toit[i]]) low[now] = min(low[now],dfn[toit[i]]);
	}
	if (dfn[now] == low[now])
	{
		++tot;
		while (stk.top() != now)
		{
			scc[tot].push_back(stk.top());
			bel[stk.top()] = tot; stk.pop();
		}
		scc[tot].push_back(stk.top());
		bel[stk.top()] = tot; stk.pop();
	}
}
