//a b直线两点，o圆心
//若a b为线段，则0 <= t1,t2 <= 1
inline int dcmp(double a)
{
	if (a > eps) return 1;
	else if (a < -eps) return -1;
	else return 0;
}

inline double mysqrt(double a)
{
	if (a < 0) return 0;
	else return sqrt(a);
}
inline void CrossPoint(const Point &a,const Point &b,const Point &o,double r,Point *ret,int &num)
{
	double X0 = o.x,Y0 = o.y;
	double X1 = a.x,Y1 = a.y;
	double X2 = b.x,Y2 = b.y;
	double dx = X2-X1,dy = Y2-Y1;
	double A = dx*dx+dy*dy;
	double B = 2*dx*(X1-X0)+2*dy*(Y1-Y0);
	double C = (X1-X0)*(X1-X0)+(Y1-Y0)*(Y1-Y0)-r*r;
	double delta = B*B-4*A*C;
	num = 0;
	if (dcmp(delta) >= 0)
	{
		double t1 = (-B-mysqrt(delta))/(2*A);
		double t2 = (-B+mysqrt(delta))/(2*A);
		ret[++num] = Point(X1+t1*dx,Y1+t1*dy);
		ret[++num] = Point(X1+t2*dx,Y1+t2*dy);
	}
}
