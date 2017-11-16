// hdu1392
struct Point
{
	double x,y;
    inline Point() = default;
	inline Point(double _x,double _y):x(_x),y(_y) {}
	inline double norm() const { return sqrt(x*x+y*y); }
	inline void read() { scanf("%lf %lf",&x,&y); }
    friend inline Point operator -(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline Point operator /(const Point &a,double b) { return Point(a.x/b,a.y/b); }
	friend inline double operator /(const Point &a,const Point &b) { return a.x*b.y-a.y*b.x; }
	friend inline bool operator <(const Point &a,const Point &b)
	{
		if (a.x != b.x) return a.x < b.x;
		else return a.y < b.y;
	}
}P[maxn],convex[maxn];

inline int ConvexHull()
{
	int m = 0;
    sort(P+1,P+N+1);  //x第一关键字，y第二关键字从小到大排序
    for (int i = 1;i <= N;++i)
    {
        while (m > 1&&(convex[m]-convex[m-1])/(P[i]-convex[m-1]) <= 0) --m;
        convex[++m] = P[i];
    }
    int k = m;
    for (int i = N-1;i > 0;--i)
    {
        while (m > k&&(convex[m]-convex[m-1])/(P[i]-convex[m - 1]) <= 0) --m;
        convex[++m] = P[i];
    }
    if (N > 1) m--;
	return m;
}
