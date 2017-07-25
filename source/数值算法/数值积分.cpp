template <class T>
inline double simpson(const T &f,double a,double b,int n)
{
	double h = (b-a)/n,ret = f(a)+f(b);
	for (int i = 1;i < n;i += 2) ret += 4*f(a+i*h);
	for (int i = 2;i < n;i += 2) ret += 2*f(a+i*h);
	return ret*h/3;
}

template <class T>
inline double romberg(const T &f,double a,double b,double eps = 1e-8)
{
	vector <double> t; double h = b-a,last,cur;
	int k = 1,i = 1;
	t.push_back(h*(f(a)+f(b))/2);
	do
	{
		last = t.back(); cur = 0; double x = a+h/2;
		for (int j = 0;j < k;++j) cur += f(x),x += h;
		cur = (t[0]+h*cur)/2;
		double k1 = 4.0/3,k2 = 1.0/3;
		for (int j = 0;j < i;++j)
		{
			double temp = k1*cur-k2*t[j];
			t[j] = cur; cur = temp; k2 /= 4*k1-k2; k1 = k2+1;
		}
		t.push_back(cur); k *= 2; h /= 2; ++i;
	}
	while (fabs(last - cur) > esp);
	return t.back();
}
