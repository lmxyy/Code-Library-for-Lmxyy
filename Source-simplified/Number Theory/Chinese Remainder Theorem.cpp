//快速乘 and 慢速幂
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
