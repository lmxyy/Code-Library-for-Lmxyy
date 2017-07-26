const int prime[] = {0,2,3,5,7,11,13,17,19,23,29,31};

inline ll mul(ll a,ll b,ll p) { return (a*b-((ll)((ld)a/p*b+1e-3)*p)+p)%p; }

inline bool check(ll m)
{
	if (m <= 2) return m == 2;
	ll tmp = m-1; int t = 0;
	while (!(tmp&1)) ++t,tmp >>= 1;
	for (int i = 1;i <= 10;++i)
	{
		int a = prime[i];
		if (a == m) return true;
		ll w = qsm(a,tmp,m);
		for (int it = 1;it <= t;++it)
		{
			ll pf = mul(w,w,m);
			if (pf == 1&&(w != 1&&w != m-1)) return false;
			w = pf;
		}
		if (w != 1) return false;
	}
	return true;
}
inline void rho(ll m)
{
	if (check(m)) { fac[++nn] = m; return; }
	while (true)
	{
		ll X = (ll)rand()*rand()%(m-1)+1,Y = X;
		ll c = (ll)rand()*rand()%(m-1)+1; int i,j;
		for (i = j = 2;;++i)
		{
			X = (mul(X,X,m)+c) % m;
			ll d = __gcd(abs(X-Y),m);
			if (1 < d&&d < m) { rho(d),rho(m/d); return; }
			if (X == Y) break; if (i == j) Y = X,j <<= 1;
		}
	}
}
inline void factor(ll m) { nn = 0; if (m > 1) rho(m); sort(fac+1,fac+nn+1); }
