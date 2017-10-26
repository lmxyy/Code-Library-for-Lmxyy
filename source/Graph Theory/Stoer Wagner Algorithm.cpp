int G[maxn][maxn],node[maxn],dis[maxn]; bool visit[maxn];

inline int solve(int n)
{
	if (n == 1) return inf;
	int answer = inf;
	for (int i = 0;i < n;++i) node[i] = i;
	while (n > 1)
	{
		int mx = 1;
		for (int i = 0;i < n;++i)
		{
			dis[node[i]] = G[node[0]][node[i]];
			if (dis[node[i]] > dis[node[mx]]) mx = i;
		}
		int prev = 0;
		memset(visit,false,sizeof visit);
		visit[node[0]] = true;
		for (int i = 1;i < n;++i)
		{
			if (i == n-1)
			{
				answer = min(answer,dis[node[mx]]);
				for (int k = 0;k < n;++k)
					G[node[k]][node[prev]] = (G[node[prev]][node[k]] += G[node[k]][node[mx]]);
				node[mx] = node[--n];
			}
			visit[node[mx]] = true; prev = mx; mx = -1;
			for (int j = 1;j < n;++j)
				if (!visit[node[j]])
				{
					dis[node[j]] += G[node[prev]][node[j]];
					if (mx == -1||dis[node[mx]] < dis[node[j]]) mx = j;
				}
		}
	}
	return answer;
}
