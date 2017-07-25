// dinic
int source,sink;
inline bool bfs()
{
	queue <int> team; team.push(source); d[source] = 0;
	memset(in,false,tot+10); in[source] = true; team.push(source);
	while (!team.empty())
	{
		int now = team.front(); team.pop(); cur[now] = side[now];
		for (int i = side[now];i;i = next[i])
		{
			if (!cap[i]) continue;
			if (!in[toit[i]])
				in[toit[i]] = true,d[toit[i]] = d[now]+1,team.push(toit[i]);
		}
	}
	return in[sink];
}

inline int dfs(int now,int f)
{
	if (now == sink||!f) return f;
	int used = 0,w;
	for (int &i = cur[now];i;i = next[i])
		if (cap[i]&&d[toit[i]] == d[now]+1)
		{
			w = dfs(toit[i],min(cap[i],f-used));
			used += w; cap[i] -= w; cap[i^1] += w;
			if (used == f) break;
		}
	return used;
}

inline int dinic(int S,int T)
{
	source = S; sink = T; int ret = 0;
	while (bfs()) ret += dfs(source,inf);
	return ret;
}
