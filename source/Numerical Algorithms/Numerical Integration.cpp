//self-adapt simpson
inline long double simpson(long double l,long double r,long double mid,long double Cl,long double Cr,long double Cm)
{
    long double tCl = calc((l+mid)/2),tCr = calc((mid+r)/2);
	long double ans=(r-l)*(Cl+Cr+4*Cm)/6,lans=(mid-l)*(Cl+Cm+4*tCl)/6,rans=(r-mid)*(Cr+Cm+4*tCr)/6;
    if (r-l <= 1e-3&&fabs(lans+rans-ans)<eps) return ans;
	// if (dep > lim&&fabs(lans+rans-ans)<eps) return ans;
    else return simpson(l,mid,(l+mid)/2,Cl,Cm,tCl)+simpson(mid,r,(mid+r)/2,Cm,Cr,tCr);
}

//romberg---To Be Verified
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
	while (fabs(last - cur) > eps);
	return t.back();
}
