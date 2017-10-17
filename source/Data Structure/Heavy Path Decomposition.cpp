int side[maxn],toit[maxn<<1],nxt[maxn<<1],nxt[maxn<<1];
int timestamp,father[maxn],dfn[maxn],redfn[maxn],top[maxn],size[maxn];

void decompose(int now,int tp)
{
	redfn[dfn[now] = ++timestamp] = now;
	top[now] = tp; int heavy = 0;
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != father[now]&&size[toit[i]] > size[heavy]) heavy = toit[i];
	if (!heavy) return; decompose(heavy,tp);
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != father[now]&&toit[i] != heavy) decompose(toit[i],toit[i]);
}

void dfs(int now)
{
	size[now] = 1;
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != father[now])
		{
			father[toit[i]] = now,con[toit[i]] = i;
			dep[toit[i]] = dep[now]+1,dfs(toit[i]);
			size[now] += size[toit[i]] ;
		}
}

// 对点操作
inline int query(int a,int b)
{
	int ret = -inf;
	while (top[a] != top[b])
	{
		if (dep[top[a]] < dep[top[b]]) swap(a,b);
		ret = max(ret,ask(1,1,N,dfn[top[a]],dfn[a]));
		a = father[top[a]];
	}
	if (dep[a] < dep[b]) swap(a,b);
	ret = max(ret,query(1,1,N,dfn[b],dfn[a]));
	return ret;
}

// 对边操作
inline int query(int a,int b)
{
	int ret = -inf;
	while (top[a] != top[b])
	{
		if (dep[top[a]] < dep[top[b]]) swap(a,b);
		ret = max(ret,ask(1,1,N,dfn[top[a]],dfn[a]));
		a = father[top[a]];
	}
	if (a == b) return ret;
	if (dep[a] < dep[b]) swap(a,b);
	ret = max(ret,ask(1,1,N,dfn[b]+1,dfn[a]));
	return ret;
}
