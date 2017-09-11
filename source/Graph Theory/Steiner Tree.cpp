/* 
 *  Steiner Tree：求，使得指定K个点连通的生成树的最小总权值 
 *  st[i] 表示顶点i的标记值，如果i是指定集合内第m(0<=m<K)个点，则st[i]=1<<m  
 *  endSt=1<<K 
 *  dptree[i][state] 表示以i为根，连通状态为state的生成树值 
 */  
inline void update(int &x,int y) { if (x == -1) x = y; else if (x > y) x = y; }
inline void spfa(int state)
{
	while (!team.empty())
	{
		int now = team.front(); team.pop();
		for (int i = side[now];i;i = nxt[i])
		{
			int v = toit[i];
			if (f[v][st[v]|state] == -1||f[v][st[v]|state] > f[now][state]+len[i])
			{
				f[v][st[v]|state] = f[now][state]+len[i];
				if ((st[v]|state) != state||vis[v][state]) continue;
				vis[v][state] = true; team.push(v);
			}
		}
		vis[now][state] = false;
	}
}
inline int work()
{
	endSt = 1<<(K<<1);
	memset(f,-1,sizeof(f)); memset(st,0,sizeof(st)); memset(dp,-1,sizeof(dp));
	memset(vis,false,sizeof(vis)); memset(side,0,sizeof(side));
	for (int i = 1;i <= K;++i) st[i] = 1<<(i-1);
	for (int i = 1;i <= K;++i) st[N-K+i] = 1<<(i+K-1);
	for (int i = 1;i <= N;++i) f[i][st[i]] = 0;
	for (int j = 1;j < endSt;++j)
	{
		for (int i = 1;i <= N;++i)
		{
			if (!st[i]||(st[i]&j)) 
				for (int sub = (j-1)&j;sub;sub = (sub-1)&j)
				{
					int x = sub|st[i],y = (j-sub)|st[i];
					if (f[i][x] != -1&&f[i][y] != -1)
						update(f[i][j],f[i][x]+f[i][y]);
				}
			if (f[i][j] != -1) team.push(i),vis[i][j] = true;
		}
		spfa(j);
	}
}
