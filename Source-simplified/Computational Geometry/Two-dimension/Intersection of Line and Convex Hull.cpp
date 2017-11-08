//O(logN)
inline double getA(const Node &a)
{
	double ret = atan2(a.y,a.x);
	if (ret <= -pi/2) ret += 2*pi;
	return ret;
}

inline int find(double x)
{
	if (x <= w[1]||x >= w[m]) return 1;
	return upper_bound(w+1,w+m+1,x)-w;
}

inline bool intersect(const Node &a,const Node &b)
{
	int i = find(getA(b-a)),j = find(getA(a-b));
	if (dcmp((b-a)/(convex[i]-a))*dcmp((b-a)/(convex[j]-a)) > 0) return false;
	else return true;
}

inline int prework()
{
	ConvexConvex(); convex[m+1] = convex[1];
	for (int i = 1;i <= m;++i)
		w[i]= getA(convex[i+1]-convex[i]);
}
