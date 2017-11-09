//计算几何常用公式
struct Point
{
    double x,y;
	inline Point reflect(const Point &p) const
	{
		Point v = *this-p; double len = v.norm();
		v = v/len; return p+v*(1/len);
	}
};
struct Line
{
    Point p,v; double slop;
	inline Line() = default;
	inline Line(const Point &_p,const Point &_v):p(_p),v(_v) {}
    inline void update() { slop = v.alpha(); }
    inline double dis(const Point &a) { fabs((a-p)/v)/(v.len()); } //点到直线距离
};

inline Point CrossPoint(const Line &a,const Line &b)  //直线交点，记得判断平行
{
    Point u = a.p - b.p;
    double t = (b.v/u)/(a.v/b.v);
    return a.p+a.v*t;
}

inline Point rotate(const Point &p,double cost,double sint)
{
	double x = p.x,y = p.y;
	return Point(x*cost-y*sint,x*sint+y*cost);
}

inline Point reflect(const Point &a,const Line &l) //点关于直线对称
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
