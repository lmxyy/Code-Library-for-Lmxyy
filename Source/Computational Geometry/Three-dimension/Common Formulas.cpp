// --------------------Point--------------------
struct Point
{
	double x,y,z;
	inline Point() = default;
	inline Point(double _x,double _y,double _z):x(_x),y(_y),z(_z) {}
	inline void read() { scanf("%lf %lf %lf",&x,&y,&z); }
	inline double norm() const { return sqrt(x*x+y*y+z*z); }
	inline Point unit() const { double len = norm(); if (dcmp(len)) return *this/len; else return Point(1,0,0); }
	friend inline Point operator -(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y,a.z-b.z); }
	friend inline Point operator +(const Point &a,const Point &b) { return Point(a.x+b.x,a.y+b.y,a.x+b.z); }
	friend inline Point operator *(const Point &a,double b) { return Point(a.x*b,a.y*b,a.z*b); }
	friend inline Point operator *(double b,const Point &a) { return Point(a.x*b,a.y*b,a.z*b); }
	friend inline Point operator /(const Point &a,double b) { return Point(a.x/b,a.y/b,a.z/b); }
	friend inline Point operator /(const Point &a,const Point &b) { return Point(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x); }
	friend inline double operator *(const Point &a,const Point &b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
	friend inline bool operator <(const Point &a,const Point &b)
	{
		if (dcmp(a.x-b.x)) return a.x < b.x;
		else if (dcmp(a.y-b.y)) return a.y < b.y;
		else if (dcmp(a.z-b.z)) return a.z < b.z;
		else return false;
	}
	friend inline bool operator ==(const Point &a,const Point &b) { return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y)&&!dcmp(a.z-b.z); }
};
inline double mix(const Point &a,const Point &b,const Point &c) { return a*(b/c); } // The return-value divide 6 is the volume

// a向量绕b向量逆时针选择angle弧度（从b方向看）
inline Point rotate(const Point &a,const Point &b,double angle)
{
	Point e1,e2,e3 = b.unit();
	double len = a*e3;
	Point p = e3*len;
	e1 = a-p; if (dcmp(e1.norm())) e1 = e1.unit();
	e2 = e1/e3;
	double x1 = a*e1,y1 = a*e2;
	double x = x1*cos(angle)-y1*sin(angle);
	double y = x1*sin(angle)-y1*cos(angle);
	return e1*x+e2*y+p;
}
// --------------------Line--------------------
struct Line
{
	Point a,b; //直线上两点
	inline Line() = default;
	inline Line(const Point &_a,const Point &_b):a(_a),b(_b) {}
};

inline bool same_side(const Point &p1,const Point &p2,const Line &l) { return dcmp(((l.a-l.b)/(p1-l.b))*((l.a-l.b)/(p2-l.b))) > 0; }// 两点直线同侧
inline bool opposite_side(const Point &p1,const Point &p2,const Line &l) { return dcmp(((l.a-l.b)/(p1-l.b))*((l.a-l.b)/(p2-l.b))) < 0; }// 两点直线异侧

// 判断两条线段是否有交
inline bool intersect_in(const Line &u,const Line &v)
{
	if (!dots_onplane(u.a,u.b,v.a,v.b)) return false;
	if (!dots_inline(u.a,u.b,v.a)&&!dots_inline(u.a,u.b,v.b))
		return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
	else return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}
inline bool intersect_ex(const Line &u,const Line &v) { return dots_onplane(u.a,u.b,v.a,v.b)&&opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u); }
// 求两直线交点（须保证共面不平行）
inline Point intersection(const Line &u,const Line &v)
{
	double t = ((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
		/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
	return u.a+(u.b-u.a)*t;
}
inline double ptoline(const Point &p,const Line &l) { ((p-l.a)/(l.b-l.a)).norm()/(l.a-l.b).norm(); } // 点到直线距离
// 直线到直线距离，平行时变成点到直线距离
inline double linetoline(const Line &u,const Line &v)
{
	Point n = (u.a-u.b)/(v.a-v.b);
	return fabs((u.a-v.a)*n)/n.norm();
}
// 两直线夹角cos
inline double angle_cos(const Line &u,const Line &v) { return ((u.a-u.b)*(v.a-v.b))/(u.a-u.b).norm()/(v.a-v.b).norm(); }

// --------------------Plane--------------------
struct Plane
{
	Point a,b,c;
	inline Plane() = default;
	inline Plane(const Point &_a,const Point &_b,const Point &_c):a(_a),b(_b),c(_c) {}
	inline Point pvec() const { return (a-b)/(b-c); } // normal vector
};
// 四点共面
inline bool dots_onplane(const Point &a,const Point &b,const Point &c,const Point &d) { return dcmp(Plane(a,b,c).pvec()*(d-a)) == 0; }
// 点在三角形内
inline bool dot_inplane_in(const Point &p,const Plane &s) { return dcmp(((s.a-s.b)/(s.a-s.c)).norm()-((p-s.a)/(p-s.b)).norm()-((p-s.b)/(p-s.c)).norm()-((p-s.c)/(p-s.a)).norm()) }
inline bool dot_inplane_ex(const Point &p,const Plane &s)
{
	if (!dot_inplane_in(p,s.a,s.b,s.c)) return false;
	int s1 = dcmp((p-s.a)/(p-s.b)),s2 = dcmp((p-s.b)/(p-s.c)),s3 = dcmp((p-s.c)/(p-s.a));
	return ((s1 > 0&&s2 > 0&&s3 > 0)||(s1 < 0&&s2 < 0&&s3 < 0));
}
inline bool same_side(const Point &p1,const Point &p2,const Plane &s) // 同侧
{
	Point v = s.pvec();
	return dcmp((v/(p1-s.a))*(v/(p2-s.a))) > 0;
}
inline bool opposite_side(const Point &p1,const Point &p2,const Plane &s) // 异侧
{
	Point v = s.pvec();
	return dcmp((v/(p1-s.a))*(v/(p2-s.a))) < 0;
}
// 直线与平面是否有交
inline bool intersect_in(const Line &l,const Plane &s)
{
	return !same_side(l.a,l.b,s)&&
		!same_side(s.a,s.b,Plane(l.a,l.b,s.c))&&
		!same_side(s.b,s.c,Plane(l.a,l.b,s.a))&&
		!same_side(s.c,s.a,Plane(l.a,l.b,s.b));
}
inline bool intersect_ex(const Line &l,const Plane &s)
{
	return opposite_side(l.a,l.b,s)&&
		opposite_side(s.a,s.b,Plane(l.a,l.b,s.c))&&
		opposite_side(s.b,s.c,Plane(l.a,l.b,s.a))&&
		opposite_side(s.c,s.a,Plane(l.a,l.b,s.b));
}
// 线面交点
inline Point intersection(const Line &l,const Plane &s)
{
	Point n = s.pvec();
	double t = ((n*(s.a-l.a)))/(n*(l.b-l.a));
	return l.a+(l.b-l.a)*t;
}
// 求两平面交线
inline Line intersection(const Plane &pl1,const Plane &pl2)
{
	Line ret;
	ret.a = parallel(Line(pl2.a,pl2.b),pl1)?intersection(Line(pl2.b,pl2.c),pl1):intersection(Line(pl2.a,pl2.b),pl1);
	ret.b = ret.a+(pl1.pvec()/pl2.pvec());
	return ret;
}
// 点到直线距离
inline double ptoplane(const Point &p,const Plane &s) { double n = s.pvec(); return fabs(n*(p-s.a))/n.norm(); }
inline double angle_cos(const Plane &u,const Plane &v)
{
	Point n1 = u.pvec(),n2 = v.pvec();
	return (n1*n2)/n1.norm()/n2.norm();
}
inline double angle_sin(const Line &l,const Plane &s)
{
	Point n = s.pvec();
	return ((l.a-l.b)*n)/(l.a-l.b).norm()/n.norm();
}
