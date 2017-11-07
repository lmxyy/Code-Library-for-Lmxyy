//The Second Version
const double pi = acos(-1.0);
struct Complex
{
	double re,im;
	inline Complex() = default;
	inline Complex(double _re,double _im):re(_re),im(_im) {}
	friend inline Complex operator*(const Complex &a,const Complex &b) { return Complex(a.re*b.re-a.im*b.im,a.re*b.im+a.im*b.re); }
	friend inline Complex operator+(const Complex &a,const Complex &b) { return Complex(a.re+b.re,a.im+b.im); }
	friend inline Complex operator-(const Complex &a,const Complex &b) { return Complex(a.re-b.re,a.im-b.im); }
	friend inline Complex operator/(const Complex &a,double r) { return Complex(a.re/r,a.im/r); }
};

inline void FFT(Complex *a,int loglen,int len,int on)
{
	for (register int i = 0,j,t,p;i < len;++i)
	{
		for (p = j = 0,t = i;j < loglen;++j,t >>= 1)
			p <<= 1,p |= (t&1);
		if (p > i) swap(a[p],a[i]);
	}
	for (register int m = 2,s = 1;s <= loglen;++s,m <<= 1)
	{
		register Complex w(cos(2*pi*on/m),sin(2*pi*on/m));
		for (int i = 0;i < len;i += m)
		{
			register Complex wn(1,0);
			for (register int j = 0;j < (m>>1);++j,wn = wn*w)
			{
				register Complex u = a[i+j],v = wn*a[i+j+(m>>1)];
				a[i+j] = u+v; a[i+j+(m>>1)] = u-v;
			}
		}
	}
	if (on == -1) for (int i = 0;i < len;++i) a[i] = a[i]/len;
}

struct Polynomial
{
	int len; Complex array[maxn<<2];
	inline Polynomial(int _len = 0):len(_len) {}
	inline Polynomial(Complex a[],int n):len(n) { for (int i = 0;i < n;++i) array[i] = a[i]; }
	inline Complex operator [](int n) const { return array[n]; }
	inline Complex &operator [](int n) { return array[n]; }
	inline void set(int n) { len = n; }
	inline void set(int n,Complex a[]) { len = n; for (int i = 0;i < n;++i) array[i] = a[i]; }
	inline void extend(int key)
	{
		for (int i = len;i < (1<<key);++i)
			array[i] = Complex(0,0);
	}
	inline void cut(int key) { len = key; }
	inline void transform(int loglen,int on) { FFT(array,loglen,1<<loglen,on); }
}; //变量只能定义在全局，不然会re

inline Polynomial multiply(Polynomial &pa,Polynomial &ret) // self-multiply
{
	int loglen = 0;
	while ((1<<loglen) < (pa.len<<1)-1) ++loglen;
	pa.extend(1<<loglen); pa.transform(loglen,1);
	for (int i = 0;i < (1<<loglen);++i) ret[i] = pa[i]*pa[i];
	ret.transform(loglen,-1); ret.cut((pa.len<<1)-1);
	return ret;
}
inline Polynomial multiply(Polynomial &pa,Polynomial &pb,Polynomial &ret)
{
	int loglen = 0;
	while ((1<<loglen) < (pa.len+pb.len-1)) ++loglen;
	pa.extend(1<<loglen); pa.transform(loglen,1);
	pb.extend(1<<loglen); pb.transform(loglen,1);
	for (int i = 0;i < (1<<loglen);++i) ret[i] = pa[i]*pb[i];
	ret.transform(loglen,-1); ret.cut(pa.len+pb.len-1);
	return ret;
}
