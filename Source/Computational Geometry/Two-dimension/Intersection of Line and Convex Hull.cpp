// 询问一条直线与凸包是否有交
// O(logN)
inline int dcmp(double a)
{
	if (a > eps) return 1;
	else if (a < -eps) return -1;
	else return 0;
}

struct Point
{
    double x,y;
	inline Point() = default;
	inline Point(double _x,double _y):x(_x),y(_y) {}
	inline void read() { scanf("%lf %lf",&x,&y); }
	inline double angle() const	{ return atan2(y,x); }
	friend inline Point operator -(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline double operator /(const Point &a,const Point &b) { return a.x*b.y-a.y*b.x; } // 叉积
	friend inline bool operator <(const Point &a,const Point &b)
	{
		if (a.x != b.x) return a.x < b.x;
		else return a.y < b.y;
	}
}convex[maxn],P[maxn];

inline bool cmp(double a,double b) { return dcmp(a-b) < 0; }

inline double getA(const Point &a)
{
	double ret = atan2(a.y,a.x);
	if (dcmp(ret+pi/2) <= 0) ret += 2*pi;
	return ret;
}
inline bool intersect(const Point &a,const Point &b)
{
	int i = upper_bound(w+1,w+M+1,getA(b-a),cmp)-w,j = upper_bound(w+1,w+M+1,getA(a-b),cmp)-w;
	if (dcmp((b-a)/(convex[i]-a))*dcmp((b-a)/(convex[j]-a)) > 0) return false;
	else return true;
}

inline int ConvexHull()
{
	sort(P+1,P+N+1);
	int m = 0;
	for (int i = 1;i <= N;++i)
	{
		while (m > 1&&(convex[m]-convex[m-1])/(P[i]-convex[m-1]) <= 0) --m;
		convex[++m] = P[i];
	}
	int k = m;
	for (int i = N-1;i > 0;--i)
	{
		while (m > k&&(convex[m]-convex[m-1])/(P[i]-convex[m-1]) <= 0) --m;
		convex[++m] = P[i];
	}
	if (N > 1) m--;
	if (m > 1)
	{
		convex[m+1] = convex[1];
		for (int i = 1;i <= m;++i)
			w[i]= getA(convex[i+1]-convex[i]);
		sort(w+1,w+m+1,cmp);
	}
	return m;
}
