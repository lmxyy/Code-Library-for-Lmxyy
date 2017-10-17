#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

typedef long long ll;
const int maxn = 500010; const ll inf = 1LL<<60;
int N,K,A[maxn]; ll pre[maxn],f[maxn];

struct Point
{
	ll x,y;
	inline Point() = default;
	inline Point(ll _x,ll _y):x(_x),y(_y) {}
	friend inline Point operator -(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline ll operator /(const Point &a,const Point &b) { return a.x*b.y-a.y*b.x; }
};

inline ll calc(const Point &a,int b) { return -a.x*b+a.y; }

struct Queue
{
	Point array[maxn]; int h,t;
	inline Queue() = default;
	inline void init() { h = t = 0; }
	inline void pop_front(int i) { while (t-h >= 2&&calc(array[h+1],i) > calc(array[h+2],i)) ++h; }
	inline void push(const Point &a,int i) { while (t-h >= 2&&(a-array[t-1])/(array[t]-array[t-1]) >= 0) --t; array[++t] = a; }
	inline Point front() const { return array[h+1]; }
}team;

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

int main()
{
	// freopen("E.in","r",stdin);
	for (int T = gi();T--;)
	{
		N = gi(),K = gi(); team.init();
		for (int i = 1;i <= N;++i) A[i] = gi();
		for (int i = 1;i <= N;++i) pre[i] = pre[i-1]+A[i];
		for (int i = 1;i <= N;++i)
		{
			if (i >= K)
			{
				if (f[i-K] != inf)
					team.push(Point(A[i-K+1],f[i-K]-pre[i-K]+(ll)(i-K)*A[i-K+1]),i);
				team.pop_front(i);
				f[i] = calc(team.front(),i)+pre[i];
			}
			else f[i] = inf;
		}
		cout << f[N] << endl;
	}
	return 0;
}
