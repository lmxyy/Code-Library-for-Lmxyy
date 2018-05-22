// Be hacked on uoj57, 97%.
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;

const double eps = 1e-7;
const int inf = 1<<30,oo = 100000000,maxv = 300010,maxe = 300010;
const int maxn = 300010,maxm = 300010,maxq = 300010;

int N,M,T,ncnt = 1,cnt = 1,tot,all;
int side[maxv],nxt[maxe*2],toit[maxe*2],len[maxe*2];
int father[maxv],dep[maxv],f[maxv][30],g[maxv][30];
int query[maxq][2]; double space[maxn];

inline int gi()
{
	int f = 1,ret = 0; char ch;
	do ch = getchar(); while ((ch < '0'||ch > '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline int dcmp(double a)
{
	if (fabs(a) <= eps) return 0;
	else if (a > 0) return 1;
	else return -1;
}

struct Point
{
	double x,y;
	inline Point() = default;
	inline Point(double _x,double _y):x(_x),y(_y) {}
	inline void read() { x = gi(),y = gi(); }
	friend inline Point operator-(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline double operator/(const Point &a,const Point &b) { return a.x*b.y-a.y*b.x; }
	inline double angle() { return atan2(y,x); }
}P[maxn];

struct Segment
{
	int from,to,h,id,sur; // from号点到to号点，h为边权,suf为这条有向边围出来的平面编号。
	inline Segment() = default;
	inline Segment(int _from,int _to,int _h = 0,int _id = 0,int _sur = 0):from(_from),to(_to),h(_h),id(_id),sur(_sur) {}
	friend inline bool operator<(const Segment &a,const Segment &b) { return (P[a.to]-P[a.from]).angle() < (P[b.to]-P[b.from]).angle(); }
}edge[maxm*2];
vector <int> G[maxn];

inline void nadd(int u,int v,int h) { ++ncnt; G[u].push_back(ncnt); edge[ncnt] = Segment(u,v,h); }
inline void nins(int u,int v,int h) { nadd(u,v,h); nadd(v,u,h); }

inline bool cmp(int a,int b) { return edge[a] < edge[b]; }

struct Edge
{
	int u,v,h;
	inline Edge() = default;
	inline Edge(int _u,int _v,int _h):u(_u),v(_v),h(_h) {}
	friend inline bool operator < (const Edge &a,const Edge &b) { return a.h < b.h; }
}edges[maxn];

void find_surface()
{
	for (int i = 1;i <= N;++i)
		stable_sort(G[i].begin(),G[i].end(),cmp);
	for (int i = 1;i <= N;++i)
	{
		int nn = G[i].size();
		for (int j = 0;j < nn;++j)
			edge[G[i][j]].id = j;
	}
	for (int i = 2;i <= ncnt;++i)
		if (!edge[i].sur)
		{
			++tot; int p,nn; vector <Point> vec;
			for (int j = i;!edge[j].sur;j = G[p][(edge[j^1].id+1)%nn]) // 逆时针旋转
			{
				edge[j].sur = tot; vec.push_back(P[edge[j].from]);
				p = edge[j].to; nn = G[p].size();
			}
			double res = 0; nn = vec.size();
			for (int j = 0;j < nn;++j)
				res += (vec[j]-vec[0])/(vec[(j+1)%nn]-vec[0]);
			res /= 2; space[tot] = res; // 面积为正为无穷大平面
		}
	for (int i = 2;i <= ncnt;i += 2)
	{
		if (space[edge[i].sur]<0&&space[edge[i^1].sur]<0)
			edges[++all] = Edge(edge[i].sur,edge[i^1].sur,edge[i].h);
		else edges[++all] = Edge(edge[i].sur,edge[i^1].sur,inf);
	}
}

inline void add(int a,int b,int c) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; len[cnt] = c; }
inline void ins(int a,int b,int c) { add(a,b,c); add(b,a,c); }

inline int find(int a) { if (father[a] != a) father[a] = find(father[a]); return father[a];}
void dfs(int now)
{
	for (int i = 1;(1<<i) <= dep[now];++i)
	{
		f[now][i] = f[f[now][i-1]][i-1];
		g[now][i] = max(g[now][i-1],g[f[now][i-1]][i-1]);
	}
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != f[now][0])
		{
			f[toit[i]][0] = now;
			dep[toit[i]] = dep[now]+1;
			g[toit[i]][0] = len[i];
			dfs(toit[i]);
		}
}
void mst()
{
	for (int i = 1;i <= tot;++i) father[i] = i;
	sort(edges+1,edges+all+1);
	int k = 0;
	for (int i = 1;i <= all;++i)
	{
		int r1 = find(edges[i].u),r2 = find(edges[i].v);
		if (r1 != r2)
		{
			father[r1] = r2; ++k;
			ins(edges[i].u,edges[i].v,edges[i].h);
		}
		if (k == tot-1) break;
	}
	dfs(1);
}

inline int jump(int &a,int step)
{
	int ret = 0;
	for (int i = 0;step;step >>= 1,++i)
		if (step&1) ret = max(g[a][i],ret),a = f[a][i];
	return ret;
}
inline int lca(int a,int b)
{
	int ret = 0;
	if (dep[a] < dep[b]) swap(a,b);
	ret = jump(a,dep[a]-dep[b]);
	if (a == b) return ret;
	for (int i = 0;i >= 0;)
	{
		if (f[a][i] == f[b][i]) --i;
		else
		{
			ret = max(max(g[a][i],ret),g[b][i]);
			a = f[a][i]; b = f[b][i]; ++i;
		}
	}
	ret = max(max(g[a][0],ret),g[b][0]);
	return ret;
}

// 点定位
struct Event
{
	double x,y; int bel,sign;
	inline Event() = default;
	inline Event(double _x,double _y,int _bel,int _sign):x(_x),y(_y),bel(_bel),sign(_sign) {}
	friend inline bool operator < (const Event &a,const Event &b)
	{
		if (a.x != b.x) return a.x < b.x;
		else return a.sign > b.sign;
	}
}event[maxn*4];

double nowX; int flag;
struct Node
{
	int id; Point p,v;
	inline Node() = default;
	inline Node(int _id,Point _p,Point _v):id(_id),p(_p),v(_v) {}
	friend inline bool operator <(const Node &a,const Node &b)
	{
		double ay = a.p.y+(nowX-a.p.x)*a.v.y/a.v.x;
		double by = b.p.y+(nowX-b.p.x)*b.v.y/b.v.x;
		if (dcmp(ay-by)) return dcmp(ay-by) < 0;
		else if (dcmp(a.v/b.v))
		{
			return dcmp(a.v/b.v) == flag;
		}
		else return a.id < b.id;
	}
};	
multiset <Node> S;

void locate()
{
	int nn = 0;
	P[++N] = Point(-oo,oo); P[++N] = Point(oo,oo);
	edge[++ncnt] = Segment(N-1,N);
	for (int i = 2;i <= ncnt;i += 2)
	{
		if (!dcmp(P[edge[i].from].x-P[edge[i].to].x)) continue;
		event[++nn] = Event(P[edge[i].from].x,P[edge[i].from].y,i,2);
		event[++nn] = Event(P[edge[i].to].x,P[edge[i].to].y,i,3);
	}
	scanf("%d",&T); double x,y;
	// 查询(x,y)所在平面
	for (int i = 1;i <= T;++i)
	{
		scanf("%lf %lf",&x,&y);
		event[++nn] = Event(x,y,i,0);
		scanf("%lf %lf",&x,&y);
		event[++nn] = Event(x,y,i,1);
	}
	sort(event+1,event+nn+1);
	for (int i = 1;i <= nn;++i)
	{
		nowX = event[i].x;
		if (event[i].sign == 2||event[i].sign == 3)
		{
			int t = event[i].bel;
			if (event[i].sign == 2)
			{
				flag = 1;
				S.insert(Node(t,P[edge[t].from],P[edge[t].to]-P[edge[t].from]));
			}
			else
			{
				flag = -1;
				S.erase(S.find(Node(t,P[edge[t].from],P[edge[t].to]-P[edge[t].from])));
			}
		}
		else
		{
			int t = S.lower_bound(Node(0,Point(event[i].x,event[i].y),Point(1,1)))->id;
			query[event[i].bel][event[i].sign] = edge[t].sur;
		}
	}
}

inline void work()
{
	for (int i = 1;i <= T;++i)
	{
		if (!query[i][0]||!query[i][1]||space[query[i][0]] > 0|| space[query[i][1]] > 0)
			puts("-1");
		else
		{
			int ans = lca(query[i][0],query[i][1]);
			if (ans > 1000000000) puts("-1");
			else printf("%d\n",ans);
		}
	}
}

int main()
{
	N = gi(); M = gi();
	for (int i = 1;i <= N;++i) P[i].read();
	for (int i = 1;i <= M;++i)
	{
		int u = gi(),v = gi(),h = gi();
		if (P[u].x > P[v].x) swap(u,v);
		nins(u,v,h);
	}
	find_surface();
	mst();
	locate();
	work();
	return 0;
}
