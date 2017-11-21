// POJ 2069

// --------------------Simulate Anneal--------------------
// 点数较少时使用，精度很解体，poj数据有误，导致下面做法过不了
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
// poj那题过不了，估计std模拟退火
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 110;
const double range = 100,eps = 1e-7;
int N,nouter; double radius;

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
}P[maxn],outer[4],res;

void ball()
{
	Point q[3]; double m[3][3],sol[3],L[3],det;
	res = Point(0,0,0); radius = 0;
	switch (nouter)
	{
	case 1: res = outer[0]; break;
	case 2: res = (outer[0]+outer[1])/2; radius = (res-outer[0]).norm(); break;
	case 3:
		for (int i = 0;i < 2;++i) q[i] = outer[i+1]-outer[0];
		for (int i = 0;i < 2;++i) for (int j = 0;j < 2;++j) m[i][j] = q[i]*q[j]*2;
		for (int i = 0;i < 2;++i) sol[i] = q[i]*q[i];
		if (dcmp(det = m[0][0]*m[1][1]-m[0][1]*m[1][0]) == 0) return;
		L[0] = (sol[0]*m[1][1]-sol[1]*m[0][1])/det;
		L[1] = (sol[1]*m[0][0]-sol[0]*m[1][0])/det;
		res = outer[0]+(L[0]*q[0])+(L[1]*q[1]);
		radius = (res-outer[0]).norm(); break;
	case 4:
		for (int i = 0;i < 3;++i)
			q[i] = outer[i+1]-outer[0],sol[i] = q[i]*q[i];
		for (int i = 0;i < 3;++i) for (int j = 0;j < 3;++j) m[i][j] = q[i]*q[j]*2;
		det = m[0][0]*m[1][1]*m[2][2]
			+ m[0][1]*m[1][2]*m[2][0]
			+ m[0][2]*m[2][1]*m[1][0]
			- m[0][2]*m[1][1]*m[2][0]
			- m[0][1]*m[1][0]*m[2][2]
			- m[0][0]*m[1][2]*m[2][1];
		if (dcmp(det) == 0) return;
		for (int j = 0;j < 3;++j)
		{
			for (int i = 0;i < 3;++i) m[i][j] = sol[i];
			L[j] = (m[0][0]*m[1][1]*m[2][2]
					+ m[0][1]*m[1][2]*m[2][0]
					+ m[0][2]*m[2][1]*m[1][0]
					- m[0][2]*m[1][1]*m[2][0]
					- m[0][1]*m[1][0]*m[2][2]
					- m[0][0]*m[1][2]*m[2][1])/det;
			for (int i = 0;i < 3;++i) m[i][j] = q[i]*q[j]*2;
		}
		res = outer[0]+(L[0]*q[0])+(L[1]*q[1])+(L[2]*q[2]);
		radius = (res-outer[0]).norm();
	}
}

void minball(int n)
{
	ball();
	if (nouter < 4)
		for (int i = 0;i < n;++i)
			if (dcmp((res-P[i]).norm()-radius) > 0)
			{
				outer[nouter++] = P[i];
				minball(i); --nouter;
				if (i > 0)
				{
					Point Tt = P[i];
					memmove(&P[1],&P[0],sizeof(Point)*i);
					P[0] = Tt;
				}
			}
}

inline double smallest_ball()
{
	random_shuffle(P,P+N);
	radius = -1;
	for (int i = 0;i < N;++i)
		if (dcmp((res-P[i]).norm()-radius) > 0)
			nouter = 1,outer[0] = P[i],minball(i);
	return radius;
}

int main()
{
	freopen("2069.in","r",stdin);
	while (true)
	{
		scanf("%d",&N);
		if (!N) break;
		for (int i = 0;i < N;++i) P[i].read();
		printf("%.9f\n",smallest_ball());
	}
	return 0;
}
