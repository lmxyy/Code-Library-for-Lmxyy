// 接口int matching(),返回最大匹配数,G为邻接矩阵
inline void push(int x)
{
	team.push(x); check[x] = true;
	if (!treec[x]) tra[++cnt] = x,treec[x] = true;
}
inline int root(int x) { return f[x]?f[x] = root(f[x]):x; }

inline void clear()
{
	for (int i = 1,j;i <= cnt;++i)
	{
		j = tra[i]; father[j] = 0,f[j] = 0;
		check[j] = treec[j] = false;
	}
}

inline int lca(int u,int v)
{
	int len = 0;
	for (;u;u = father[match[u]])
		pathc[path[++len] = u = root(u)] = true;
	for (;;v = father[match[v]])
		if (pathc[v = root(v)]) break;
	for (int i = 1;i <= len;++i)
		pathc[path[i]] = false;
	return v;
}

inline void reset(int u,int p)
{
	for (int v;root(u) != p;)
	{
		if (!check[v = match[u]]) push(v);
		if (!f[u]) f[u] = p; if (!f[v]) f[v] = p;
		u = father[v]; if (root(u) != p) father[u] = v;
	}
}

inline void flower(int u,int v)
{
	int p = lca(u,v);
	if (root(u) != p) father[u] = v;
	if (root(v) != p) father[v] = u;
	reset(u,p); reset(v,p);
}

inline bool find(int x)
{
	while (!team.empty()) team.pop();
	cnt = 0; push(x);
	while (!team.empty())
	{
		int i = team.front(); team.pop();
		for (int j = 1;j <= N;++j)
			if (G[i][j]&&root(i) != root(j)&&match[j] != i)
			{
				if (match[j]&&father[match[j]]) flower(i,j);
				else if (!father[j])
				{
					father[tra[++cnt] = j] = i; treec[j] = true;
					if (match[j]) push(match[j]);
					else
					{
						for (int k = i,l = j,p;k;l = p,k = father[l])
							p = match[k],match[k] = l,match[l] = k;
						return true;
					}
				}
			}
	}
	return false;
}

inline int matching()
{
	memset(father,0,sizeof father);  memset(f,0,sizeof f); memset(path,0,sizeof path);
	memset(tra,0,sizeof tra); memset(match,0,sizeof match); memset(check,false,sizeof check);
	memset(treec,false,sizeof treec); memset(pathc,false,sizeof pathc);
	int ret = cnt = 0;
	for (int i = 1;i <= N;++i)
	{
		if (match[i]) continue;
		if (find(i)) ++ret; clear();
	}
	return ret;
}
