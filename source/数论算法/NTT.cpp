struct node
{
	int a[maxn*2],len;
	inline void NTT(int loglen,int len,int on)
	{
		for (int i = 0,j,t,p;i < len;++i)
		{
			for (j = 0,t = i,p = 0;j < loglen;++j,t >>= 1)
				p <<= 1,p |= t&1;
			if (p < i) swap(a[p],a[i]);
		}
		for (int s = 1,k = 2;s < loglen;++s,k <<= 1)
		{
			int wn; if (on) wn = e[s]; else wn = ine[s];
			for (int i = 0;i < len;i += k)
			{
				int w = 1;
				for (int j = 0;j < (k >> 1);++j,w = (ll)wn*w%rhl)
				{
					int u = a[i+j],v = (ll)w*a[i+j+(k>>1)]%rhl;
					a[i+j] = u+v; if (a[i+j] >= rhl) a[i+j] -= rhl;
					a[i+j+(k>>1)] = u-v;
					if (a[i+j+(k>>1)] < 0) a[i+j+(k>>1)] += rhl;
				}
			}
		}
		if (!on)
		{
			int inv = qsm(len,rhl-2,rhl);
			for (int i = 0;i < len;++i) a[i] = (ll)a[i]*inv%rhl;
		}
	}
	friend inline bool operator *(node x,node y)
	{
		int loglen = 0,len;
		for (;(1<<loglen)<x.len+y.len;++loglen); len = 1<<loglen;
		x.NTT(loglen,len,1); y.NTT(loglen,len,1);
		for (int i = 0;i < (1<<loglen);++i) x.a[i] = (ll)x.a[i]*y.a[i]%rhl;
		x.NTT(loglen,len,0);
	}
};

int main()
{
	for (int i = 1;i < 20;++i)
		e[i] = qsm(gg,(rhl-1)>>i,rhl),ine[i] = qsm(e[i],rhl-2,rhl);
}
