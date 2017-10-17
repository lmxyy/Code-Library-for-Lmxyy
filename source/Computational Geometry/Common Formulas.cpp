//计算几何常用公式
inline int dcmp(double a)
{
	if (fabs(a) <= eps) return 0;
	else if (a > 0) return 1;
	else return -1;
}
struct Point
{
    double x,y;
	inline Point() = default;
	inline Point(double _x,double _y):x(_x),y(_y) {}
	inline Point unit() const
	{
		double len = norm();
		if (!dcmp(len)) return Point(1,0);
		else return *this/len;
	}
	inline double norm() const { return sqrt(x*x+y*y); }
	inline Point reflect(const Point &p) const
	{
		Point v = *this-p; double len = v.norm();
		v = v/len; return p+v*(1/len);
	}
	inline void read() { scanf("%lf %lf",&x,&y); }
	inline Point vertical() const { return Point(y,-x); }
	inline double angle() const
	{
		double ret = atan2(y,x);
		if (ret < 0) ret += 2*pi;
		return ret;
	}
	friend inline bool operator ==(const Point &a,const Point &b) { return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y); }
    friend inline Point operator -(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline Point operator +(const Point &a,const Point &b) { return Point(a.x+b.x,a.y+b.y); }
	friend inline Point operator /(const Point &a,double b) { return Point(a.x/b,a.y/b); }
	friend inline Point operator *(const Point &a,double b) { return Point(a.x*b,a.y*b); }
	friend inline Point operator *(double b,const Point &a) { return Point(a.x*b,a.y*b); }
	friend inline double operator /(const Point &a,const Point &b) { return a.x*b.y-a.y*b.x; }
};
struct Line
{
    Point p,v; double slop;
	inline Line() = default;
	inline Line(const Point &_p,const Point &_v):p(_p),v(_v) {}
    inline void update() { slop = v.alpha(); }
    friend inline bool operator <(const Line &l1,const Line &l2)
	{ return l1.slop < l2.slop; }
	inline double dis(const Point &a) { fabs((a-p)/v)/(v.len()); } //点到直线距离
};

inline bool OnLine(const Line &l,const Point &p) { return !dcmp(l.v/(p-l.p)); } //点在直线上

inline Point CrossPoint(const Line &a,const Line &b)  //直线交点
{
    Point u = a.p - b.p;
    double t = (b.v/u)/(a.v/b.v);
    return a.p+a.v*t;
}

inline bool parallel(const Line &a,const Line &b) { return !dcmp(a.v/b.v); } //直线平行
