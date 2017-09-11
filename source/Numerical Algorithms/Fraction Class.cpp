typedef long long ll;
struct Fraction
{
	ll num,den;
	inline Fraction(ll a = 0,ll b = 1)
	{
		if (den < 0) a = -a,b = -b;
		assert(b != 0); ll g = gcd(abs(a),b);
		num = a/g; den = b/g;
	}
	friend inline Fraction operator +(const Fraction &a,const Fraction &b) const { return Fraction(a.num*b.den+b.num*a.den,a.den*b.den); }
	friend inline Fraction operator -(const Fraction &a,const Fraction &b) const { return Fraction(a.num*b.den-b.num*a.den,a*den*b.den); }
	friend inline Fraction operator *(const Fraction &a,const Fraction &b) const { return Fraction(a.num*b.num,a*den*b.den); }
	friend inline Fraction operator /(const Fraction &a,const Fraction &b) const { return Fraction(a.num*b.den,a*den*b.num); }
	friend inline bool operator <(const Fraction &a,const Fraction &b) const { return a.num*b.den < a.den*b.num; }
	friend inline bool operator <(const Fraction &a,const Fraction &b) const { return a.num==b.num&&a.den==b.den; }
};
