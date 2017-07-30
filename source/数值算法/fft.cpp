struct Vir
{
	double re,im;
	inline Vir(double _re = 0,double im = 0):re(_re),im(_im) {}
	friend inline Vir operator*(const Vir &a,const Vir &b) { return Vir(a.re*b.re-a.im*b.im,a.re*b.im+a.im*b.re); }
	friend inline Vir operator+(const Vir &a,const Vir &b) { return Vir(a.re+b.re,a.im+b.im); }
	friend inline Vir operator-(const Vir &a,const Vir &b) { return Vir(a.re-b.re,a.im-b.im); }
	friend inline Vir operator/(const Vir &a,double r) { return Vir(a.re/r,a.im/r); }
}pa[maxn],pb[maxn];

inline void fft(Vir *a,int loglen,int len,int on)
{
	for (register int i = 0,j,t,p;i < len;++i)
	{
		for (p = j = 0,t = i;j < loglen;++j,t >>= 1)
			p <<= 1,p |= (t&1);
		if (p > i) swap(a[p],a[i]);
	}
	for (register int m = 2,s = 1;s <= loglen;++s,m <<= 1)
	{
		register Vir w(cos(2*pi*on/m),sin(2*pi*on/m));
		for (int i = 0;i < len;i += m)
		{
			register Vir wn(1,0);
			for (register int j = 0;j < (m>>1);++j,wn = wn*w)
			{
				register Vir u = a[i+j],v = wn*a[i+j+(m>>1)];
				a[i+j] = u+v; a[i+j+(m>>1)] = u-v;
			}
		}
	}
	if (on == -1) for (int i = 0;i < len;++i) a[i] = a[i]/len;
}

inline void work()
{
	int loglen = 0,len;
	while ((1<<loglen) < l) ++loglen; len = 1 << loglen;
	fft(pa,loglen,len,1); fft(pb,loglen,len,1);
	for (int i = 0;i < len;++i) pa[i] = pa[i]*pb[i];
	fft(pa,loglen,len,-1);
}
