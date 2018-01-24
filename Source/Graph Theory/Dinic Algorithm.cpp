// Check by POJ - 1273
// dinic
int source,sink,cnt = 1;
int d[maxv],side[maxv],cur[maxv],nxt[maxe],toit[maxe],cap[maxe]; bool in[maxv];

inline void add(int a,int b,int c) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; cap[cnt] = c; }
inline void ins(int a,int b,int c) { add(a,b,c); add(b,a,0); }

inline bool bfs()
{
	queue <int> team; team.push(source); d[source] = 0;
	memset(in,false,tot+10); in[source] = true; team.push(source);
	while (!team.empty())
	{
		int now = team.front(); team.pop(); cur[now] = side[now];
		for (int i = side[now];i;i = nxt[i])
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
	for (int &i = cur[now];i;i = nxt[i])
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
