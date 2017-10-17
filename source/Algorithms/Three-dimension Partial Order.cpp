//三维偏序，CDQ分治
#define lowbit(a) (a&-a)
int M,N,A,B,tree[maxn];

inline void ins(int a,int b) { for (;a < maxn;a += lowbit(a)) tree[a] = max(tree[a],b); }
inline void clear(int a) { for (;a < maxn;a += lowbit(a)) tree[a] = 0; }
inline int calc(int a) { int ret = 0; for (;a;a -= lowbit(a)) ret = max(tree[a],ret); return ret; }

struct Node
{
	int x,y,z,res;
	inline Node(int _x = 0,int _y = 0,int _z = 0,int _res = 0):x(_x),y(_y),z(_z),res(_res) {}
	inline void update() { ++x,++y,++z; }
}E[maxn];

inline bool cmpx(const Node &a,const Node &b)
{
	if (a.x != b.x) return a.x < b.x;
	else if (a.y != b.y) return a.y > b.y;
	else return a.z > b.z;
}
inline bool cmpy(const Node &a,const Node &b) { return a.y < b.y; }

inline void work(int l,int r)
{
	if (l == r) { E[l].res = max(E[l].res,1); return; }
	int mid = (l+r) >> 1,p = l;
	work(l,mid);
	sort(E+l,E+mid+1,cmpy);
	sort(E+mid+1,E+r+1,cmpy);
	for (int i = mid+1;i <= r;++i)
	{
		for (;p <= mid&&E[p].y < E[i].y;++p) ins(E[p].z,E[p].res);
		E[i].res = max(E[i].res,calc(E[i].z-1)+1);
	}
	while (p > l) clear(E[--p].z);
	sort(E+mid+1,E+r+1,cmpx);
	work(mid+1,r);
}

inline int run()
{
	for (int i = 1;i <= N+M;++i) E[i].update();
	sort(E+1,E+N+M+1,cmpx); work(1,N+M);
	int ret = 0;
	for (int i = 1;i <= N+M;++i) ret = max(ret,E[i].res);
	return ret;
}
