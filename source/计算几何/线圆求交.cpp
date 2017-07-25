//a b直线两点，o圆心
//若a b为线段，则0 <= t1,t2 <= 1
inline void cp(const Node &a,const Node &b,const Node &o,double r,Node *ret,int &num)
{
	double X0 = o.x,Y0 = o.y;
	double X1 = a.x,Y1 = a.y;
	double X2 = b.x,Y2 = b.y;
	double dx = X2-X1,dy = Y2-Y1;
	double A = dx*dx+dy*dy;
	double B = 2*dx*(X1-X0)+2*dy*(Y1-Y0);
	double C = (X1-X0)*(X1-X0)+(Y1-Y0)*(Y1-Y0)-r*r;
	double delta = B*B-4*A*C+eps;
	num = 0;
	if (delta >= 0)
	{
		double t1 = (-B-sqrt(delta))/(2*A);
		double t2 = (-B+sqrt(delta))/(2*A);
		ret[++num] = Node(X1+t1*dx,Y1+t1*dy);
		ret[++num] = Node(X1+t2*dx,Y1+t2*dy);
	}
}
