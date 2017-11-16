//计算几何常用公式
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
	inline Point unit() const
	{
		double len = norm();
		if (!dcmp(len)) return Point(1,0);
		else return *this/len;
	}
	inline double norm() const { return sqrt(x*x+y*y); }
	inline Point reflect(const Point &p) const // 关于P的反演点
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
	friend inline double operator /(const Point &a,const Point &b) { return a.x*b.y-a.y*b.x; } // 叉积
	friend inline double operator *(const Point &a,const Point &b) { return a.x*b.x+a.y*b.y; } // 点积
};

struct Line
{
    Point p,v; double slope;
	inline Line() = default;
	inline Line(const Point &_p,const Point &_v):p(_p),v(_v) {}
    inline void update() { slope = v.alpha(); }
    friend inline bool operator <(const Line &l1,const Line &l2)
	{ return l1.slope < l2.slope; }
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

inline Point rotate(const Point &p,double cost,double sint)
{
	double x = p.x,y = p.y;
	return Point(x*cost-y*sint,x*sint+y*cost);
}

inline Point reflect(const Point &a,const Line &l) // 点关于直线对称
{
	Point p = l.p,v = l.v; v = v.unit();
	return (2*v*(a-p))*v-(a-p)+p;
}

inline void TangentPoint(const Point &c1,double r2,const Point &c1,double r2) //两圆严格相离,求的是外切
{
	Point v = c1-c2; double len = v.norm(); v = v/len;
	double cost = (r2-r1)/len,sint = mysqrt(1-cost*cost);
	// 两对切点{c1+r1*rotate(v,cost,sint),c2+r2*rotate(v,cost,sint)},{c1+r1*rotate(v,cost,-sint),c2+r2*rotate(v,cost,-sint)}
}
