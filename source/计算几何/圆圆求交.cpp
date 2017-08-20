//圆圆求交，需先判定两圆有交

inline Point rotate(const Point &p,double cost,double sint)
{
	double x = p.x,y = p.y;
	return Point(x*cost-y*sint,x*sint+y*cost);
}

inline pair <Point,Point> cp(const Point &ap,double ar,const Point &bp,double br)
{
	double d = (ap-bp).norm();
	double cost = (ar*ar+d*d-br*br)/(2*ar*d),sint = sqrt(1-cost*cost);
	Point v = ((bp-ap)/(bp-ap).norm())*ar;
	return make_pair(ap+rotate(v,cost,-sint),ap+rotate(v,cost,sint));
}
