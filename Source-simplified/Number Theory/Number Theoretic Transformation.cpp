// The Second Version
typedef long long ll;
ll e[20],ine[20];

inline ll qsm(ll a,int b,int c)
{
	ll ret = 1;
	for (;b;b >>= 1,(a *= a) %= c) if (b&1) (ret *= a) %= c;
	return ret;
}

inline void NTT(ll *a,int loglen,int len,int on)
{
	for (int i = 0,j,t,p;i < len;++i)
	{
		for (j = 0,t = i,p = 0;j < loglen;++j,t >>= 1)
			p <<= 1,p |= t&1;
		if (p > i) swap(a[p],a[i]);
	}
	for (int s = 1,k = 2;s <= loglen;++s,k <<= 1)
	{
		int wn; if (on) wn = e[s]; else wn = ine[s];
		for (int i = 0;i < len;i += k)
		{
			int w = 1;
			for (int j = 0;j < (k >> 1);++j,w = (ll)wn*w%lhh)
			{
				int u = a[i+j],v = (ll)w*a[i+j+(k>>1)]%lhh;
				a[i+j] = u+v; if (a[i+j] >= lhh) a[i+j] -= lhh;
				a[i+j+(k>>1)] = u-v;
				if (a[i+j+(k>>1)] < 0) a[i+j+(k>>1)] += lhh;
			}
		}
	}
	if (!on)
	{
		int inv = qsm(len,lhh-2,lhh);
		for (int i = 0;i < len;++i) a[i] = a[i]*inv%lhh;
	}
}

struct Polynomial
{
	int len; ll array[maxn<<2];
	inline Polynomial(int _len = 0):len(_len) {}
	inline Polynomial(ll a[],int n):len(n) { for (int i = 0;i < n;++i) array[i] = a[i]; }
	inline ll operator [](int n) const { return array[n]; }
	inline ll &operator [](int n) { return array[n]; }
	inline void set(int n) { len = n; }
	inline void set(int n,ll a[]) { len = n; for (int i = 0;i < n;++i) array[i] = a[i]; }
	inline void extend(int key)
	{
		for (int i = len;i < (1<<key);++i)
			array[i] = 0;
	}
	inline void cut(int key) { len = key; }
	inline void transform(int loglen,int on) { NTT(array,loglen,1<<loglen,on); }
}; //变量只能定义在全局，不然会re

inline Polynomial multiply(Polynomial &pa,Polynomial &ret) // self-multiply
{
	int loglen = 0;
	while ((1<<loglen) < (pa.len<<1)-1) ++loglen;
	pa.extend(1<<loglen); pa.transform(loglen,1);
	for (int i = 0;i < (1<<loglen);++i) ret[i] = pa[i]*pa[i]%lhh;
	ret.transform(loglen,0); ret.cut((pa.len<<1)-1);
	return ret;
}
inline Polynomial multiply(Polynomial &pa,Polynomial &pb,Polynomial &ret)
{
	int loglen = 0;
	while ((1<<loglen) < (pa.len+pb.len-1)) ++loglen;
	pa.extend(1<<loglen); pa.transform(loglen,1);
	pb.extend(1<<loglen); pb.transform(loglen,1);
	for (int i = 0;i < (1<<loglen);++i) ret[i] = pa[i]*pb[i]%lhh;
	ret.transform(loglen,0); ret.cut(pa.len+pb.len-1);
	return ret;
}

int main()
{
	for (int i = 1;i < 20;++i)
		e[i] = qsm(g,(lhh-1)>>i,lhh),ine[i] = qsm(e[i],lhh-2,lhh);
}
