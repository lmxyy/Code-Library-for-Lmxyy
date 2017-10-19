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


//__int128 Version
typedef __int128 int128;
inline int128 mul(int128 a,int128 b,int128 mod)
{
	int128 ret = 0; a %= mod,b %= mod;
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

inline int128 qsm(int128 a,int128 b,int128 mod)
{
	int128 ret = 1;
	for (;b;b >>= 1,a = mul(a,a,mod)) if (b&1) ret = mul(ret,a,mod);
	return ret;
}

inline void ready()
{
	for (int i = 2;i <= 100;++i)
	{
		if (prime[i]) continue; prime[++tot] = i;
		for (int j = i*i;j <= 100;j += i) prime[j] = 1;
	}
}

inline int128 gi()
{
	int128 ret = 0; char ch;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9'));
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret;
}

inline int128 gcd(int128 a,int128 b) { if (b == 0) return a; return gcd(b,a%b); }

inline int128 Abs(int128 a) { if (a < 0) return -a; return a; }

inline bool check(int128 m)
{
	if (m <= 2) return m == 2;
	int128 tmp = m-1; int t = 0;
	while (!(tmp&1)) ++t,tmp >>= 1;
	for (int i = 1;i <= tot;++i)
	{
		int a = prime[i];
		if (a == m) return true;
		int128 w = qsm(a,tmp,m);
		for (int it = 1;it <= t;++it)
		{
			int128 pf = mul(w,w,m);
			if (pf == 1&&(w != 1&&w != m-1)) return false;
			w = pf;
		}
		if (w != 1) return false;
	}
	return true;
}
inline void rho(int128 m)
{
	if (check(m)) { fac[++nn] = m; return; }
	while (true)
	{
		int128 X = (int128)rand()*(int128)rand()%(m-1)+1,Y = X;
		int128 c = (int128)rand()*(int128)rand()%(m-1)+1; int i,j;
		for (i = j = 2;;++i)
		{
			X = (mul(X,X,m)+c)%m;
			int128 d = gcd(Abs(X-Y),m);
			if (1 < d&&d < m) { rho(d),rho(m/d); return; }
			if (X == Y) break; if (i == j) Y = X,j <<= 1;
		}
	}
}

inline void factor(int128 m) { nn = 0; if (m > 1) rho(m); sort(fac+1,fac+nn+1); }
