//凸包上最大四边形面积
int N,M; double ans;
struct Point { double x,y; }P[maxn],convex[maxn];

inline void Graham()
{
	ConvexHull();
	for (int i = 1;i <= M;++i) convex[i+M] = convex[i];
	int p1,p2,p3,p4;
	for (p1 = 1;p1 <= M;++p1)
	{
		p2 = p1+1; p3 = p2+1; p4 = p3+1;
		for (;p3 < p1+M-1;++p3)
		{
			Point v = convex[p3]-convex[p1];
			while (p2 < p3&&fabs((convex[p2]-convex[p1])/v) < fabs((convex[p2+1]-convex[p1])/v)) ++p2;
			while (p4 < p1+M&&fabs((convex[p4]-convex[p1])/v) < fabs((convex[p4+1]-convex[p1])/v)) ++p4;
			ans = max(ans,fabs((convex[p2]-convex[p1])/v)+fabs((convex[p4]-convex[p1])/v));
		}
	}
	ans = ans/2;
}
