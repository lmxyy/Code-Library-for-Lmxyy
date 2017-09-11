//N为开始圆的个数，M为离散化后圆的个数，cnt为去包含后圆的个数
int N,M,cnt;

struct Node
{
	double x,y;
	inline  Node(double _x = 0,double _y = 0):x(_x),y(_y) {}
	inline void read() { x = gi(),y = gi(); }
	inline double norm() const { return sqrt(x*x+y*y); }
	inline double angle() const { return atan2(y,x); }
	inline Node unit() const { double len = norm(); return Node(x/len,y/len); }
	friend inline Node operator-(const Node &a,const Node &b) { return Node(a.x-b.x,a.y-b.y); }
	friend inline Node operator+(const Node &a,const Node &b) { return Node(a.x+b.x,a.y+b.y); }
	friend inline Node operator*(const Node &a,double b) { return Node(a.x*b,a.y*b); }
	friend inline Node operator*(double b,const Node &a) { return Node(a.x*b,a.y*b); }
	friend inline double operator/(const Node &a,const Node &b) { return a.x*b.y-a.y*b.x; }
};
struct Circle
{
	Node C; double r;
	inline Circle(const Node &_C = Node(),double _r = 0):C(_C),r(_r) {} 
	friend inline bool operator<(const Circle &a,const Circle &b)
	{
		if (dcmp(a.r-b.r)) return dcmp(a.r-b.r) < 0;
		else if (dcmp(a.C.x-b.C.x)) return dcmp(a.C.x-b.C.x) < 0;
		else return dcmp(a.C.y-b.C.y) < 0;
	}
	friend inline bool operator==(const Circle &a,const Circle &b)
	{
		if (dcmp(a.r-b.r)) return false;
		if (dcmp(a.C.x-b.C.x)) return false;
		if (dcmp(a.C.y-b.C.y)) return false;
		return true;
	}
}tc[maxn],cir[maxn];

inline Node rotate(const Node &p,double cost,double sint)
{
	double x = p.x,y = p.y;
	return Node(x*cost-y*sint,x*sint+y*cost);
}
inline pair <Node,Node> crosspoint(const Node &ap,double ar,const Node &bp,double br)
{
	double d = (ap-bp).norm(),cost = (ar*ar+d*d-br*br)/(2*ar*d),sint = sqrt(1-cost*cost);
	Node v = ((bp-ap).unit())*ar;
	return make_pair(ap+rotate(v,cost,-sint),ap+rotate(v,cost,sint));
}
inline pair <Node,Node> crosspoint(const Circle &a,const Circle &b) { return crosspoint(a.C,a.r,b.C,b.r); }

struct Event
{
	Node p; double a; int d;
	inline Event(const Node &_p = Node(),double _a = 0,double _d = 0):p(_p),a(_a),d(_d) {}
	friend inline bool operator <(const Event &a,const Event &b) { return a.a < b.a; }
};

inline double work()
{
	sort(tc+1,tc+M+1); M = unique(tc+1,tc+M+1)-tc-1;
	for (int i = M;i;--i)
	{
		bool ok = true;
		for (int j = i+1;j <= M;++j)
		{
			double d = (tc[i].C-tc[j].C).norm();
			if (dcmp(d-fabs(tc[i].r-tc[j].r)) <= 0) { ok = false; break; }
		}
		if (ok) cir[++cnt] = tc[i];
	}
	// for (int i = M;i;--i) cir[++cnt] = tc[i];
	double ret = 0;
	for (int i = 1;i <= cnt;++i)
	{
		vector <Event> event;
		Node boundary = cir[i].C+Node(cir[i].r,0);
		event.push_back(Event(boundary,-pi,0));
		event.push_back(Event(boundary,pi,0));
		for (int j = 1;j <= cnt;++j)
		{
			if (i == j) continue;
			double d = (cir[i].C-cir[j].C).norm();
			if (dcmp(d-(cir[i].r+cir[j].r)) < 0)
			{
				pair <Node,Node> res = crosspoint(cir[i],cir[j]);
				double x = (res.first-cir[i].C).angle(),y = (res.second-cir[i].C).angle();
				if (dcmp(x-y) > 0)
				{
					event.push_back(Event(res.first,x,1));
					event.push_back(Event(boundary,pi,-1));
					event.push_back(Event(boundary,-pi,1));
					event.push_back(Event(res.second,y,-1));
				}
				else
				{
					event.push_back(Event(res.first,x,1));
					event.push_back(Event(res.second,y,-1));
				}
			}
		}
		sort(event.begin(),event.end());
		int sum = event[0].d;
		for (int j = 1;j < (int)event.size();++j)
		{
			if (!sum)
			{
				ret += (event[j-1].p/event[j].p)/2;
				double x = event[j-1].a,y = event[j].a;
				double area = cir[i].r*cir[i].r*(y-x)/2;
				Node v1 = event[j-1].p-cir[i].C,v2 = event[j].p-cir[i].C;
				area -= (v1/v2)/2; ret += area;
			}
			sum += event[j].d;
		}
	}
	return ret;
}
