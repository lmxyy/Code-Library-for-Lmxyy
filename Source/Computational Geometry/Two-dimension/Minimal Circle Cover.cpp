// ZOJ1450
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 110;
const double eps = 1e-7;
int N; double radius;

inline int dcmp(double a)
{
	if (a > eps) return 1;
	else if (a < -eps) return -1;
	else return 0;
}

struct Point
{
    double x,y;
	inline Point() = default;
	inline Point(double _x,double _y):x(_x),y(_y) {}
	inline double norm() const { return sqrt(x*x+y*y); }
	inline void read() { scanf("%lf %lf",&x,&y); }
    friend inline Point operator -(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline Point operator +(const Point &a,const Point &b) { return Point(a.x+b.x,a.y+b.y); }
	friend inline Point operator /(const Point &a,double b) { return Point(a.x/b,a.y/b); }
}P[maxn],center;

inline Point circle_center(const Point &p0,const Point &p1,const Point &p2)
{
	double a1 = p1.x-p0.x,b1 = p1.y-p0.y,c1 = (a1*a1+b1*b1)/2;
	double a2 = p2.x-p0.x,b2 = p2.y-p0.y,c2 = (a2*a2+b2*b2)/2;
	double d = a1*b2-a2*b1;
	return Point(p0.x+(c1*b2-c2*b1)/d,p0.y+(a1*c2-a2*c1)/d);	
}

inline bool point_in(const Point &p) { return dcmp((p-center).norm()-radius) < 0; }

double smallest_circle(Point P[],int n)
{
	random_shuffle(P,P+n);
	radius = 0; center = P[0];
	for (int i = 1;i < n;++i)
		if (!point_in(P[i]))
		{
			center = P[i]; radius = 0;
			for (int j = 0;j < i;++j)
				if (!point_in(P[j]))
				{
					center = (P[i]+P[j])/2;
					radius = (P[j]-center).norm();
					for (int k = 0;k < j;++k)
						if (!point_in(P[k]))
						{
							center = circle_center(P[i],P[j],P[k]);
							radius = (P[k]-center).norm();
						}
				}
		}
	return radius;
}

int main()
{
	freopen("1450.in","r",stdin);
	while (true)
	{
		scanf("%d",&N); if (!N) break;
		for (int i = 0;i < N;++i) P[i].read();
		smallest_circle(P,N);
		printf("%.2f %.2f %.2f\n",center.x,center.y,radius);
	}
	return 0;
}
