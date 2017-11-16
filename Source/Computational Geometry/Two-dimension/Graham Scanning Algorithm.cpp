// BZOJ1069
// 凸包上最大四边形面积
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 2010;
int N,M; double ans;

struct Point
{
	double x,y;
	Point() = default;
	Point(double _x,double _y):x(_x),y(_y) {}
	inline void read() { scanf("%lf %lf",&x,&y); }
	friend inline Point operator -(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline double operator /(const Point &a,const Point &b) { return a.x*b.y-a.y*b.x; }
	friend inline double operator <(const Point &a,const Point &b)
	{
		if (a.x != b.x) return a.x < b.x;
		else return a.y < b.y;
	}
}P[maxn],convex[maxn];

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline void ConvexHull()
{
	int m = 0;
	sort(P+1,P+N+1);  //x第一关键字，y第二关键字从小到大排序
    for (int i = 1;i <= N;++i)
    {
        while (m > 1&&(convex[m]-convex[m-1])/(P[i]-convex[m-1]) <= 0) --m;
        convex[++m] = P[i];
    }
    int k = m;
    for (int i = N-1;i;--i)
    {
        while (m > k&&(convex[m]-convex[m-1])/(P[i]-convex[m - 1]) <= 0) --m;
        convex[++m] = P[i];
    }
    if (N > 1) m--; M = m;
}

inline void Graham()
{
	for (int i = 1;i <= M;++i) convex[i+M] = convex[i];
	int p1,p2,p3,p4;
	for (p1 = 1;p1 <= M;++p1)
	{
		p2 = p1+1;
		p3 = p2+1;
		p4 = p3+1;
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

int main()
{
	N = gi();
	for (int i = 1;i <= N;++i) P[i].read();
	ConvexHull();
	Graham();
	printf("%.3f\n",ans);
	return 0;
}
