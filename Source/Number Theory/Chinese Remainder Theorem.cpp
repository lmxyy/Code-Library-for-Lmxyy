//快速乘
inline ll qsc(ll a,ll b,ll mod)
{
	ll ret = 0; a %= mod,b %= mod;
	for (;b;b >>= 1)
	{
		if (b&1)
		{
			ret += a;
			if (ret >= mod) ret -= mod;
		}
		a += a; if (a >= mod) a -= mod;
	}
	return ret;
}

inline ll msm(ll a,ll b,ll mod)
{
	ll ret = 1;
	for (;b;b >>= 1,a = qsc(a,a,mod)) if (b&1) ret = qsc(ret,a,mod);
	return ret;
}

inline ll crt()
{
	ll lcm = 1,ret = 0;
	for (int i = 1;i <= K;++i) lcm *= (ll)P[i];
	for (int i = 1;i <= K;++i)
	{
		ll tm = lcm/P[i];
		ll inv = msm(tm,P[i]-2,P[i]);
		ret = (ret+qsj(qsj(tm,inv,lcm),res[i],lcm))%lcm;		
	}
	return ret;
}
