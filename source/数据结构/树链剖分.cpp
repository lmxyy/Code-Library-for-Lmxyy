inline void Div(int now,int tp)
{
	dfn[now] = ++DFN; seq[DFN] = now; top[now] = tp; int heavy = 0;
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != father[now]&&size[toit[i]] > size[heavy]) heavy = toit[i];
	if (!heavy) return; Div(heavy,tp);
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != father[now]&&toit[i] != heavy) Div(toit[i],toit[i]);
}

inline void dfs(int now)
{
	size[now] = 1;
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != father[now])
		{
			father[toit[i]] = now,con[toit[i]] = i;
			D[toit[i]] = D[now]+1,dfs(toit[i]);
			size[now] += size[toit[i]] ;
		}
}

inline int query(int a,int b)
{
	int ret = -inf;
	while (top[a] != top[b])
	{
		if (D[top[a]] < D[top[b]]) swap(a,b);
		ret = max(ret,ask(1,1,N,dfn[top[a]],dfn[a]));
		a = father[top[a]];
	}
	if (D[a] < D[b]) swap(a,b);
	modify(1,1,N,dfn[b],dfn[a],c);
	return ret;
}

