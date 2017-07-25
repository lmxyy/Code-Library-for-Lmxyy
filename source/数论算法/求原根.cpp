//Input:A prime p
//Output:p's primitive root
vector <ll> a;

inline g_test(ll g,ll p)
{
	for (ll i = a.size()-1;i >= 0;--i)
		if (qsm(g,(p-1)/a[i],p) == 1) return 0;
	return 1;
}

inline ll PrimitiveRoot(ll p)
{
	ll tmp = p - 1;
	for (ll i = 2;i <= tmp/i;++i)
	{
		if (!(tmp % i))
		{
			a.push_back(i);
			while (!(tmp%i)) tmp /= i;
		}
		if (tmp != 1) a.push_back(tmp);
	}
	for (ll g = 1;;++g) if (g_test(g,p)) return g;
}
