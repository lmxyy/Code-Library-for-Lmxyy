struct Point
{
	double x,y; int id;
	inline Point(double _x = 0,double _y = 0,int _id = 0):x(_x),y(_y),id(_id) {}
	inline void read(int i = 0) { scanf("%lf %lf",&x,&y); id = i; }
	inline double norm() { return sqrt(x*x+y*y); }
	friend inline Point operator+(const Point &a,const Point &b) { return Point(a.x+b.x,a.y+b.y); }
	friend inline Point operator-(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline double operator*(const Point &a,const Point &b) { return a.x*b.x+a.y*b.y; }
	friend inline double operator/(const Point &a,const Point &b) { return a.x*b.y-a.y*b.x; }
}P[maxn];

struct Rectangle
{
	double lx,rx,ly,ry;
	inline Rectangle(double _lx = 0,double _rx = 0,double _ly = 0,double _ry = 0):lx(_lx),rx(_rx),ly(_ly),ry(_ry) {}
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
	inline double dist(const Point &p)
	{
		if (p.x <= lx&&p.y <= ly) return (p-Point(lx,ly)).norm();
		else if (p.x <= rx&&p.y <= ly) return p.y-ly;
		else if (p.x >= rx&&p.y <= ly) return (p-Point(rx,ly)).norm();
		else if (p.x >= rx&&p.y <= ry) return p.x-rx;
		else if (p.x >= rx&&p.y >= ry) return (p-Point(rx,ry)).norm();
		else if (p.x >= lx&&p.y >= ry) return p.y-ry;
		else if (p.x <= lx&&p.y >= ry) return (p-Point(lx,ry)).norm();
		else if (p.x <= lx&&p.y >= ly) return p.x-lx;
		return 0;
	}
};

struct Node
{
	int child[2]; Point p; Rectangle r;
	inline Node(const Point &_p = Point(),const Rectangle &_r = Rectangle()):p(_p),r(_r) { r.set(p); memset(child,0,8); }
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

inline int build(int l,int r,bool dim)
{
	int now = ++size,mid = (l+r)>>1;
	nth_element(vec.begin()+l-1,vec.begin()+mid-1,vec.begin()+r,dim?cmpx:cmpy);
	tree[now].set(vec[mid-1]);
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
