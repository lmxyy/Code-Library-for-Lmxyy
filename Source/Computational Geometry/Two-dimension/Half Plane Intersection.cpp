// POJ3525
// 半平面交，直线左侧半平面，注意最后空平面是tail-head <= 0还是tail-head <= 1
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
	inline void read() { x = gi(),y = gi(); }
	inline Point vertical() const { return Point(-y,x); }
	inline Point unit() const
	{
		double len = norm();
		if (!dcmp(len)) return Point(1,0);
		else return *this/len;
	}
	inline double norm() const { return sqrt(x*x+y*y); }
	inline double angle() const { return atan2(y,x); }
	friend inline Point operator+(const Point &a,const Point &b) { return Point(a.x+b.x,a.y+b.y); }
	friend inline Point operator-(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline Point operator*(const Point &a,double b) { return Point(a.x*b,a.y*b); }
	friend inline Point operator*(double b,const Point &a) { return Point(a.x*b,a.y*b); }
	friend inline Point operator/(const Point &a,double b) { return Point(a.x/b,a.y/b); }
	friend inline double operator/(const Point &a,const Point &b) { return a.x*b.y-a.y*b.x; }
}P[maxn],pp[maxn],pol[maxn];

struct Line
{
	Point p,v; double slope;
	inline Line() = default;
	inline Line(const Point _p,const Point _v):p(_p),v(_v),slope(_v.angle()) {}
	friend inline bool operator<(const Line &a,const Line &b) { return a.slope < b.slope; } // 一定要存下来，不然会sort会RE
}lines[maxn],qq[maxn],bac[maxn];

inline bool onleft(const Line &L,const Point &p)
{
	return dcmp(L.v/(p-L.p)) > 0;
}
inline bool parallel(const Line &a,const Line &b) { return !dcmp(a.v/b.v); }
inline Point crosspoint(const Line &a,const Line &b)
{
	Point u = a.p-b.p;
	double t = (b.v/u)/(a.v/b.v);
	return a.p+(a.v*t);
}

inline int half_plane_intersection(int n)
{
	sort(lines+1,lines+n+1);  //直线按斜率排序
    int head,tail;
    qq[head = tail = 1] = lines[1];
    for (int i = 2;i <= n;++i)
    {
        while (head < tail&&!onleft(lines[i],pp[tail-1])) --tail;
        while (head < tail&&!onleft(lines[i],pp[head])) ++head;
        qq[++tail] = lines[i];
        if (parallel(qq[tail],qq[tail-1]))
        {
            tail--;
            if (onleft(qq[tail],lines[i].p)) qq[tail] = lines[i];
        }
        if (head < tail) pp[tail-1] = crosspoint(qq[tail],qq[tail-1]);
    }
    while (head < tail && !onleft(qq[head],pp[tail-1])) --tail;
    if (tail-head <= 1) return 0;
	int m = 0;
    pp[tail] = crosspoint(qq[tail],qq[head]);
    for (int i = head;i <= tail;++i) pol[++m] = pp[i];  //半平面交点
    pol[0] = pol[m];
    return m;
}
