struct Point
{
	double x,y,z;
	friend inline Point operator /(const Point &a,const Point &b) { return Point(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x); }
	friend inline double operator *(const Point &a,const Point &b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
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
