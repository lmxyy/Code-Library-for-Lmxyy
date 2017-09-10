struct Point
{
    double x,y;
	inline Point() = default;
	inline Point(double _x,double _y):x(_x),y(_y) {}
	friend inline bool operator ==(const Point &p,const Point &q)
	{ return !dcmp(p.x-q.x)&&!dcmp(p.y-q.y); }
    friend inline Point operator + (const Point &p,const Point &q)
	{ return Point(p.x+q.x,p.y+q.y); }
    friend inline Point operator - (const Point &p,const Point &q)
	{ return Point(p.x-q.x,p.y-q.y); }
    friend inline Point operator * (const Point &p,const double &q)
	{ return Point(p.x*q,p.y*q); }
    friend inline double operator /(const Point &p,const Point &q)
	{ return p.x*q.y-p.y*q.x; }
	inline double norm() { return sqrt(x*x+y*y); }
    inline double angle() { return atan2(y,x); }
}P[maxn],convex[maxn];

inline void ConvexHull()
{
    sort(P+1,P+N+1);  //x第一关键字，y第二关键字从小到大排序
    for (int i = 1;i <= N;++i)
    {
        while (m > 1&&(convex[m]-convex[m-1])/(P[i]-convex[m-1]) <= 0) --m;
        convex[++m] = P[i];
    }
    int k = m;
    for (int i = N-1;i;--i)
    {
        while (m > k&&(convex[m]-convex[m-1])/(P[i]-convex[m - 1]) <= 0) --m;
        convex[++m] = P[i];
    }
    if (N > 1) m--;
}
