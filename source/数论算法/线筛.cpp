//欧拉函数
inline void ready()
{
    phi[1] = 1;
    for (int i = 2;i < maxn;++i)
    {
        if (!exist[i]) phi[i] = i-1,prime[++tot] = i;
        for (int j = 1;j <= tot;++j)
        {
            if (i*prime[j] >= maxn) break;
            exist[i*prime[j]] = true;
            if (i % prime[j] == 0)
				{ phi[i*prime[j]] = phi[i]*prime[j]; break; }
            else phi[i*prime[j]] = phi[i]*phi[prime[j]];
        }
    }
}
//莫比乌斯函数
inline void ready()
{
	mu[1] = 1;
	for (int i = 2;i <= 50000;++i)
	{
		if (!exist[i]) { prime[++tot] = i; mu[i] = -1; }
		for (int j = 1;j <= tot&&prime[j]*i <= 50000;++j)
		{
			exist[i*prime[j]] = true;
			if (i % prime[j] == 0) { mu[i*prime[j]] = 0; break; }
			mu[i*prime[j]] = -mu[i];
		}
	}
}
