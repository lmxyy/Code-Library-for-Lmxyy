// HDU - 5560
struct Point
{
	double x,y; int id;
	inline Point() = default;
	inline Point(double _x,double _y,int _id):x(_x),y(_y),id(_id) {}
	inline void read(int i = 0) { scanf("%lf %lf",&x,&y); id = i; }
	inline double norm() { return sqrt(x*x+y*y); } // 欧几里得距离
	friend inline Point operator+(const Point &a,const Point &b) { return Point(a.x+b.x,a.y+b.y); }
	friend inline Point operator-(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline double operator*(const Point &a,const Point &b) { return a.x*b.x+a.y*b.y; }
	friend inline double operator/(const Point &a,const Point &b) { return a.x*b.y-a.y*b.x; }
}P[maxn];

struct Rectangle
{
	double lx,rx,ly,ry;
	inline Rectangle() = default;
	inline Rectangle(double _lx,double _rx,double _ly,double _ry):lx(_lx),rx(_rx),ly(_ly),ry(_ry) {}
	inline void set(const Point &p) { lx = rx = p.x; ly = ry = p.y; }
	inline void merge(const Point &p)
	{
		lx = min(lx,p.x); rx = max(rx,p.x);
		ly = min(ly,p.y); ry = max(ry,p.y);
	}
	inline void merge(const Rectangle &r)
	{
		lx = min(lx,r.lx); rx = max(rx,r.rx);
		ly = min(ly,r.ly); ry = max(ry,r.ry);
	}
	// 最小距离，到4个角和4条边距离，顺序别乱
	inline double dist(const Point &p)
	{
		if (p.x <= lx&&p.y <= ly) return (p-Point(lx,ly)).norm();
		else if (p.x <= rx&&p.y <= ly) return ly-p.y;
		else if (p.x >= rx&&p.y <= ly) return (p-Point(rx,ly)).norm();
		else if (p.x <= lx&&p.y <= ry) return lx-p.x;
		else if (p.x >= rx&&p.y <= ry) return p.x-rx;
		else if (p.x <= lx&&p.y >= ry) return (p-Point(lx,ry)).norm();
		else if (p.x <= rx&&p.y >= ry) return p.y-ry;
		else if (p.x >= rx&&p.y >= ry) return (p-Point(rx,ry)).norm();
		else return 0;
	}
	// 最大距离，到4个角的距离
	inline double dist(const Point &p)
	{
		double ret = 0;
		ret += max((rx-p.x)*(rx-p.x),(lx-p.x)*(lx-p.x));
		ret += max((ry-p.y)*(ry-p.y),(ly-p.y)*(ly-p.y));
		return ret;
	}
};

struct Node
{
	int child[2]; Point p; Rectangle r;
	inline Node() = default;
	inline Node(const Point &_p,const Rectangle &_r):p(_p),r(_r) { r.set(p); memset(child,0,sizeof child); }
	inline void set(const Point &_p) { p = _p; r.set(p); memset(child,0,8); }
}tree[maxn];

inline bool cmpx(const Point &a,const Point &b)
{
	if (a.x != b.x) return a.x < b.x;
	else return a.y < b.y;
}
inline bool cmpy(const Point &a,const Point &b)
{
	if (a.y != b.y) return a.y < b.y;
	else return a.x < b.x;
}

inline bool cmp(pair <double,int> a,pair <double,int> b)
{
	int sgn = dcmp(a.first-b.first);
	if (sgn) return sgn < 0;
	else return a.second < b.second;
}	

// 查询k小
inline void query(int now,const Point &p,int k,pair <double,int> ret[],bool dim = false)
{
	if (dcmp(tree[now].r.dist(p)-ret[k].first) > 0) return;
	pair <double,int> val = make_pair((p-tree[now].p).norm(),tree[now].p.id);
	for (int i = 1;i <= k;++i)
		if (cmp(val,ret[i]))
		{
			for (int j = k+1;j > i;--j) ret[j] = ret[j-1];
			ret[i] = val; break;
		}
	if ((dim&&cmpx(p,tree[now].p))||(!dim&&cmpy(p,tree[now].p)))
	{
		if (tree[now].child[0]) query(tree[now].child[0],p,k,ret,dim^1);
		if (tree[now].child[1]) query(tree[now].child[1],p,k,ret,dim^1);
	}
	else
	{
		if (tree[now].child[1]) query(tree[now].child[1],p,k,ret,dim^1);
		if (tree[now].child[0]) query(tree[now].child[0],p,k,ret,dim^1);
	}
}

// 查询最小
inline void query(int x,const Point &p,pair <double,int> ret,bool dim = false)
{
	if (dcmp(tree[now].r.disp(p)-ret.first) > 0) return;
	pair <double,int> val = make_pair((p-tree[now].p).norm(),tree[now].p.id);
	if (cmp(val,ret)) ret = val;
	if ((dim&&cmpx(p,tree[now].p))||(!dim&&cmpy(p,tree[now].p)))
	{
		if (tree[now].child[0]) query(tree[now].child[0],p,ret,dim^1);
		if (tree[now].child[1]) query(tree[now].child[1],p,ret,dim^1);
	}
	else
	{
		if (tree[now].child[1]) query(tree[now].child[1],p,ret,dim^1);
		if (tree[now].child[0]) query(tree[now].child[0],p,ret,dim^1);
	}	
}

inline int build(int l,int r,bool dim)
{
	int now = ++size,mid = (l+r)>>1;
	nth_element(P+l,P+mid,P+r+1,dim?cmpx:cmpy);
	tree[now].set(P[mid]);
	if (l < mid)
	{
		tree[now].child[0] = build(l,mid-1,dim^1);
		tree[now].r.merge(tree[tree[now].child[0]].r);
	}
	if (r > mid)
	{
		tree[now].child[1] = build(mid+1,r,dim^1);
		tree[now].r.merge(tree[tree[now].child[1]].r);
	}
	return now;
}
