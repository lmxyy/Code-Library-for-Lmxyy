#include<vector>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const double pi = acos(-1.0),eps = 1e-9;
const int maxn = 1010;
int N,cnt,mark[maxn][maxn];

inline int dcmp(double x)
{
	if (x < -eps) return -1;
	else if (x > eps) return 1;
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
	friend inline Point operator +(const Point &a,const Point &b) { return Point(a.x+b.x,a.y+b.y,a.x+b.z); }
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
}info[maxn];
inline double mix(const Point &a,const Point &b,const Point &c) { return a*(b/c); } // The return-value divide 6 is the volume

inline double volume(int a,int b,int c,int d) { return mix(info[b]-info[a],info[c]-info[a],info[d]-info[a]); }

struct Face
{
	int a,b,c;
	inline Face() = default;
	inline Face(int _a,int _b,int _c):a(_a),b(_b),c(_c) {}
};
vector <Face> face;

inline void add(int v)
{
	vector <Face> tmp;
	int a,b,c; cnt++;
	for (int i = 0;i < (int)face.size();++i)
	{
		a = face[i].a; b = face[i].b; c = face[i].c;
		if (dcmp(volume(v,a,b,c)) < 0)
			mark[a][b] = mark[b][a] = mark[b][c] = mark[c][b] = mark[c][a] = mark[a][c] = cnt;
		else tmp.push_back(face[i]);
	}
	face = tmp;
	for (int i = 0;i < (int)tmp.size();++i)
	{
		a = face[i].a; b = face[i].b; c = face[i].c;
		if (mark[a][b] == cnt) face.push_back(Face(b,a,v));
		if (mark[b][c] == cnt) face.push_back(Face(c,b,v));
		if (mark[c][a] == cnt) face.push_back(Face(a,c,v));
	}
}

inline bool find()
{
	for (int i = 2;i < N;++i)
	{
		Point ndir = (info[0]-info[i])/(info[1]-info[i]);
		if (!dcmp(ndir.norm())) continue;
		swap(info[i],info[2]);
		for (int j = i+1;j < N;++j)
			if (dcmp(volume(0,1,2,j)) != 0)
			{
				swap(info[j],info[3]);
				face.push_back(Face(0,1,2));
				face.push_back(Face(0,2,1));
				return true;
			}
	}
	return false;
}

inline double ConvexHull()
{
	sort(info,info+N); N = unique(info,info+N)-info; face.clear();
	random_shuffle(info,info+N);
	if (find())
	{
		memset(mark,0,sizeof mark);	cnt = 0;
		for (int i = 3;i < N;++i) add(i);
		double ans = 0;
		for (int i = 0;i < (int)face.size();++i)
		{
			Point p = (info[face[i].a]-info[face[i].b])/(info[face[i].c]-info[face[i].b]);
			ans += p.norm();
		}
		return ans/2;
	}
	return -1;
}

int main()
{
	while (scanf("%d",&N) != EOF)
	{
		for (int i = 0;i < N;++i) info[i].read();
		printf("%.3f\n",ConvexHull());
	}
	return 0;
}
