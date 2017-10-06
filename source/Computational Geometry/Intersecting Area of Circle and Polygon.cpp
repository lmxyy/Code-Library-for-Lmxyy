const int maxn = 510;
const double eps = 1e-9;

inline int dcmp(double a)
{
	if (a > eps) return 1;
	else if (a < -eps) return -1;
	else return 0;
}

struct Point
{
	double x,y;
	Point() = default;
	Point(double _x,double _y):x(_x),y(_y) {}
	inline double norm() const { return sqrt(x*x+y*y); }
	inline Point unit() const { double len = norm(); return Point(x/len,y/len); }
	friend Point operator +(const Point &a,const Point &b) { return Point(a.x+b.x,a.y+b.y); }
	friend Point operator -(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend Point operator *(const Point &a,double b) { return Point(a.x*b,a.y*b); }
	friend Point operator *(double b,const Point &a) { return Point(a.x*b,a.y*b); }
	friend Point operator /(const Point &a,double b) { return Point(a.x/b,a.y/b); }
	friend double operator /(const Point &a,const Point &b) { return a.x*b.y-b.x*a.y; }
	friend double operator *(const Point &a,const Point &b) { return a.x*b.x+a.y*b.y; }
	inline void read() { scanf("%lf %lf",&x,&y); }
}P[maxn],A,B;
int N; double K;

inline double getSectorArea(const Point &a,const Point &b,double r)
{
	double c = (2*r*r-((a-b)*(a-b)))/(2*r*r);
	double alpha = acos(c);
	return r*r*alpha/2.0;
}

inline pair <double,double> getSolution(double a,double b,double c)
{
	double delta = b*b-4*a*c;
	if (dcmp(delta) < 0) return make_pair(0,0);
	else return make_pair((-b-sqrt(delta))/(2*a),(-b+sqrt(delta))/(2*a));
}

inline pair <Point,Point> getIntersection(const Point &a,const Point &b,double r)
{
	Point d = b-a;
	double A = d*d,B = 2*(d*a),C = (a*a)-r*r;
	pair <double,double> s = getSolution(A,B,C);
	return make_pair(a+(d*s.first),a+(d*s.second));
}

inline double getPointDist(const Point &a,const Point &b)
{
	Point d = b-a;
	int sA = dcmp(a*d),sB = dcmp(b*d);
	if (sA*sB <= 0) return (a/b)/((a-b).norm());
	else return min(a.norm(),b.norm());
}

double getArea(const Point &a,const Point &b,double r)
{
	double dA = a*a,dB = b*b,dC = getPointDist(a,b),ans = 0;
	if (dcmp(dA-r*r) <= 0&&dcmp(dB-r*r) <= 0) return (a/b)/2;
	Point tA = a.unit()*r,tB = b.unit()*r;
	if (dcmp(dC-r) > 0) return getSectorArea(tA,tB,r);
	pair <Point,Point> ret = getIntersection(a,b,r);
	if (dcmp(dA-r*r) > 0&&dcmp(dB-r*r) > 0)
	{
		ans += getSectorArea(tA,ret.first,r);
		ans += (ret.first/ret.second)/2;
		ans += getSectorArea(ret.second,tB,r);
		return ans;
	}
	if (dcmp(dA-r*r) > 0) return (ret.first/b)/2+getSectorArea(tA,ret.first,r);
	else return (a/ret.second)/2.0+getSectorArea(ret.second,tB,r);
}

double getArea(int n,Point *p,const Point &c,double r)
{
	double ret = 0;
	for (int i = 0;i < n;++i)
	{
		int sgn = dcmp((p[i]-c)/(p[(i+1)%n]-c));
		if (sgn > 0) ret += getArea(p[i]-c,p[(i+1)%n]-c,r);
		else ret -= getArea(p[(i+1)%n]-c,p[i]-c,r);
	}
	return fabs(ret);
}

