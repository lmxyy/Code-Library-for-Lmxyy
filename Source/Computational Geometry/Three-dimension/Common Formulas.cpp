// --------------------Point--------------------
struct Point
{
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

// 两点直线同侧，异侧改为<-eps
inline bool SameSide(const Point &p1,const Point &p2,const Line &l) { return dcmp(((l.a-l.b)/(p1-l.b))*((l.a-l.b)/(p2-l.b))) > 0; }

