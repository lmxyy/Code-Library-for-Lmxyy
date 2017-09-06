int dfn[maxn],low[maxn],timestamp; bool instk[maxn]; 
stack <int> stk; vector <int> scc[maxn];
inline void tarjan(int now)
{
	dfn[now] = low[now] = ++timestamp;
	stk.push(now); instk[now] = true;
	for (int i = side[now];i;i = nxt[i])
	{
		if (!dfn[toit[i]])
			tarjan(toit[i]),low[now] = min(low[now],low[toit[i]]);
		else if (instk[toit[i]]) low[now] = min(low[now],dfn[toit[i]]);
	}
	if (dfn[now] == low[now])
	{
		++tot;
		while (stk.top() != now)
		{
			++tot;
			while (stk.top() != now)
			{
				instk[stk.top()] = false;
				scc[tot].push_back(stk.top());
				bel[stk.top()] = tot; stk.pop();
			}
			instk[now] = false;
			scc[tot].push_back(stk.top());
			bel[stk.top()] = tot; stk.pop();
		}
	}
}
