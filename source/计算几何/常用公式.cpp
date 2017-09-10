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

inline bool parallel(const Line &a,const Line &b)
{ return !dcmp(a.v/b.v); } //直线平行
