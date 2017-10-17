// Truly O(n^3),最大权匹配
// 邻接矩阵，不能连的边设为-INF，求最小权匹配时边权取负，但不能连的还是 -INF，使用时先对 1 -> n 调用 hungary() ，再 get_ans() 求值
struct KM
{
	int w[maxn][maxn],lx[maxn],ly[maxn],match[maxn],way[maxn],slack[maxn];
	bool used[maxn];

	inline void init()
	{
		for (int i = 1;i <= N;++i)
			match[i] = lx[i] = ly[i] = way[i] = 0;
	}
	
	inline void hungary(int x)
	{
		match[0] = x; int j0 = 0;
		for (int j = 0;j <= N;++j)
			slack[j] = inf,used[j] = false;
		do
		{
			used[j0] = true;
			int i0 = match[j0],delta = inf,j1 = 0;
			for (int j = 1;j <= N;++j)
				if (!used[j])
				{
					int cur = -w[i0][j]-lx[i0]-ly[j];
					if (cur < slack[j])
						slack[j] = cur,way[j] = j0;
					if (slack[j] < delta)
						delta = slack[j],j1 = j;
				}
			for (int j = 0;j <= N;++j)
			{
				if (used[j]) lx[match[j]] += delta,ly[j] -= delta;
				else slack[j] -= delta;
			}
			j0 = j1;
		}
		while (match[j0]);
		do
		{
			int j1 = way[j0];
			match[j0] = match[j1];
			j0 = j1;
		}
		while (j0);
	}

	inline void work() { for (int i = 1;i <= N;++i) hungary(i); }
	
	inline int get_ans()
	{
		int sum = 0;
		for (int i = 1;i <= N;++i)
		{
			// if (w[match[i]][i] == -inf) ; //无解
			if (match[i] > 0) sum += w[match[i]][i];
		}
		return sum;
	}
}km;
//最小权匹配
struct KM
{
	int w[maxn][maxn],lx[maxn],ly[maxn],match[maxn],way[maxn],slack[maxn]; bool used[maxn];

	inline void init()
	{
		for (int i = 1;i <= N;++i)
			match[i] = lx[i] = ly[i] = way[i] = 0;
	}

	inline void hungary(int x)
	{
		match[0] = x; int j0 = 0;
		for (int j = 0;j <= N;++j)
			slack[j] = -inf,used[j] = false;
		do
		{
			used[j0] = true;
			int i0 = match[j0],delta = -inf,j1 = 0;
			for (int j = 1;j <= N;++j)
				if (!used[j])
				{
					int cur = -w[i0][j]-lx[i0]-ly[j];
					if (cur > slack[j]) slack[j] = cur,way[j] = j0;
					if (slack[j] > delta) delta = slack[j],j1 = j;
				}
			for (int j = 0;j <= N;++j)
			{
				if (used[j]) lx[match[j]] += delta,ly[j] -= delta;
				else slack[j] -= delta;
			}
			j0 = j1;
		}
		while (match[j0]);
		do
		{
			int j1 = way[j0];
			match[j0] = match[j1];
			j0 = j1;
		}
		while (j0);
	}

	inline void work() { for (int i = 1;i <= N;++i) hungary(i); }
	
	inline int get_ans()
	{
		int sum = 0;
		for (int i = 1;i <= N;++i)
		{
			// if (w[match[i]][i] == inf) ; // 无解
			if (match[i] > 0) sum += w[match[i]][i];
		}
		return sum;
	}
}km;
