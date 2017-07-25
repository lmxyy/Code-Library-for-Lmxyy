//计算几何常用公式
inline int dcmp(double a)
{
	if (fabs(a) <= eps) return 0;
	else if (a > 0) return 1;
	else return -1;
}
struct Node
{
    double x,y;
	inline Node(double _x = 0,double _y = 0):x(_x),y(_y) {}
	friend inline bool operator ==(const Node &p,const Node &q)
	{ return !dcmp(p.x-q.x)&&!dcmp(p.y-q.y); }
    friend inline Node operator + (const Node &p,const Node &q)
	{ return Node(p.x+q.x,p.y+q.y); }
    friend inline Node operator - (const Node &p,const Node &q)
	{ return Node(p.x-q.x,p.y-q.y); }
    friend inline Node operator * (const Node &p,const double &q)
	{ return Node(p.x*q,p.y*q); }
    friend inline double operator /(const Node &p,const Node &q)
	{ return p.x*q.y-p.y*q.x; }
	inline double norm() { return sqrt(x*x+y*y); }
    inline double angle() { return atan2(y,x); }
};
struct Line
{
    Node p,v; double slop;
    inline void maintain() { slop = v.alpha(); }
    friend inline bool operator <(const Line &l1,const Line &l2)
	{ return l1.slop < l2.slop; }
	inline double dis(const Node &a) { fabs((a-p)/v)/(v.len()); } //点到直线距离
};

inline bool ol(const Line &l,const Node &p) { return !dcmp(l.v/(p-l.p)); } //点在直线上

inline Node cp(const Line &a,const Line &b)  //直线交点
{
    Node u = a.p - b.p;
    double t = (b.v/u)/(a.v/b.v);
    return a.p+a.v*t;
}

inline bool para(const Line &a,const Line &b)
{ return !dcmp(a.v/b.v); } //直线平行
