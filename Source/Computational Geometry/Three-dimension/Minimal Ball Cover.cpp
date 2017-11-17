// POJ 2069

// --------------------Simulate Anneal--------------------
// 点数较少时使用
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 110;
const double range = 100,eps = 1e-7;
int N;

inline int dcmp(double a)
{
	if (a > eps) return 1;
	else if (a < -eps) return -1;
	else return 0;
}

struct Point
{
	double x,y,z;
	inline Point() = default;
	inline Point(double _x,double _y,double _z):x(_x),y(_y),z(_z) {}
	inline void read() { scanf("%lf %lf %lf",&x,&y,&z); }
	inline double norm() const { return sqrt(x*x+y*y+z*z); }
	inline Point unit() const { double len = norm(); if (dcmp(len)) return *this/len; else return Point(1,0,0); }
	friend inline Point operator -(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y,a.z-b.z); }
	friend inline Point operator +(const Point &a,const Point &b) { return Point(a.x+b.x,a.y+b.y,a.z+b.z); }
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
}P[maxn];

inline double smallest_ball()
{
	double step = range,ret = 1e30; // range为坐标范围
	Point now(0,0,0);
	while (step > eps)
	{
		double mx = (now-P[1]).norm(); int s = 1;
		for (int i = 2;i <= N;++i)
		{
			double t = (now-P[i]).norm();
			if (t > mx) mx = t,s = i;
		}
		ret = min(ret,mx);
		Point v = (P[s]-now).unit();
		now = now+(v*step);
		step *= 0.98;
		// cout << s << endl;
	}
	return ret;
}

int main()
{
	freopen("2069.in","r",stdin);
	while (true)
	{
		scanf("%d",&N);
		if (!N) break;
		for (int i = 1;i <= N;++i) P[i].read();
		printf("%.9f\n",smallest_ball());
		// cerr << endl;
	}
	return 0;
}

// --------------------Random Augment--------------------
// 复杂度：O(N)
