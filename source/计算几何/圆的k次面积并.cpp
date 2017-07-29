// origin
struct Event {
	Point p;
	double ang;
	int delta;
	Event (Point p = Point(0, 0), double ang = 0, double delta = 0) : p(p), ang(ang), delta(delta) {}
};
bool operator < (const Event &a, const Event &b) {
	return a.ang < b.ang;
}
void addEvent(const Circle &a, const Circle &b, vector<Event> &evt, int &cnt) {
	double d2 = (a.o - b.o).len2(),
		   dRatio = ((a.r - b.r) * (a.r + b.r) / d2 + 1) / 2,
		   pRatio = sqrt(-(d2 - sqr(a.r - b.r)) * (d2 - sqr(a.r + b.r)) / (d2 * d2 * 4));
	Point d = b.o - a.o, p = d.rotate(PI / 2),
		  q0 = a.o + d * dRatio + p * pRatio,
		  q1 = a.o + d * dRatio - p * pRatio;
	double ang0 = (q0 - a.o).ang(),
		   ang1 = (q1 - a.o).ang();
	evt.push_back(Event(q1, ang1, 1));
	evt.push_back(Event(q0, ang0, -1));
	cnt += ang1 > ang0;
}
bool issame(const Circle &a, const Circle &b) { return sign((a.o - b.o).len()) == 0 && sign(a.r - b.r) == 0; }
bool overlap(const Circle &a, const Circle &b) { return sign(a.r - b.r - (a.o - b.o).len()) >= 0; }
bool intersect(const Circle &a, const Circle &b) { return sign((a.o - b.o).len() - a.r - b.r) < 0; }
Circle c[N];
double area[N];  // area[k] -> area of intersections >= k.
Point centroid[N];  //k次圆的质心
bool keep[N];
void add(int cnt, DB a, Point c) {
	area[cnt] += a;
	centroid[cnt] = centroid[cnt] + c * a;
}
void solve(int C) {
	for (int i = 1; i <= C; ++ i) {
        area[i] = 0;
        centroid[i] = Point(0, 0);
    }
	for (int i = 0; i < C; ++i) {
		int cnt = 1;
		vector<Event> evt;
		for (int j = 0; j < i; ++j) if (issame(c[i], c[j])) ++cnt;
		for (int j = 0; j < C; ++j) {
			if (j != i && !issame(c[i], c[j]) && overlap(c[j], c[i])) {
				++cnt;
			}
		}
		for (int j = 0; j < C; ++j) {
			if (j != i && !overlap(c[j], c[i]) && !overlap(c[i], c[j]) && intersect(c[i], c[j])) {
				addEvent(c[i], c[j], evt, cnt);
			}
		}
		if (evt.size() == 0u) {
			add(cnt, PI * c[i].r * c[i].r, c[i].o);
		} else {
			sort(evt.begin(), evt.end());
			evt.push_back(evt.front());
			for (int j = 0; j + 1 < (int)evt.size(); ++j) {
				cnt += evt[j].delta;
				add(cnt, det(evt[j].p, evt[j + 1].p) / 2, (evt[j].p + evt[j + 1].p) / 3);
				double ang = evt[j + 1].ang - evt[j].ang;
				if (ang < 0) {
					ang += PI * 2;
				}
                if (sign(ang) == 0) continue;
				double ang0 = evt[j].a,ang1 = evt[j+1].a;
                add(cnt, ang * c[i].r * c[i].r / 2, c[i].o +
                    Point(sin(ang1) - sin(ang0), -cos(ang1) + cos(ang0)) * (2 / (3 * ang) * c[i].r));
				add(cnt, -sin(ang) * c[i].r * c[i].r / 2, (c[i].o + evt[j].p + evt[j + 1].p) / 3);
			}
		}
	}
    for (int i = 1; i <= C; ++ i)
		if (sign(area[i])) {
			centroid[i] = centroid[i] / area[i];
		}
}

//modified
const double eps = 1e-7,pi = acos(-1.0);
int N,M; double area[maxn]; // area[k] -> area of intersections >= k.

inline int dcmp(double a)
{
	if (-eps <= a&&a <= eps) return 0;
	else if (a > 0) return 1; else return -1;
}

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
	friend inline Node operator/(const Node &a,double b) { return Node(a.x/b,a.y/b); }
	friend inline double operator/(const Node &a,const Node &b) { return a.x*b.y-a.y*b.x; }
};
struct Circle
{
	Node C; double r; int sgn; //sgn代表每个圆的权值
	inline Circle(const Node &_C = Node(),double _r = 0,int _sgn = 1):C(_C),r(_r),sgn(_sgn) {} 
	friend inline bool operator==(const Circle &a,const Circle &b)
	{
		if (dcmp(a.r-b.r)) return false;
		if (dcmp(a.C.x-b.C.x)) return false;
		if (dcmp(a.C.y-b.C.y)) return false;
		if (a.sgn != b.sgn) return false;
		return true;
	}
	friend inline bool operator!=(const Circle &a,const Circle &b) { return !(a == b); }
}cir[maxn];

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

inline bool overlap(const Circle &a,const Circle &b) { return dcmp(a.r-b.r-(a.C-b.C).norm()) >= 0; } // b是不是在a里面
inline bool intersect(const Circle &a,const Circle &b)
{
	if (overlap(a,b)) return false;
	if (overlap(b,a)) return false;
	return dcmp((a.C-b.C).norm()-a.r-b.r) < 0;
}

struct Event
{
	Node p; double a; int d;
	inline Event(const Node &_p = Node(),double _a = 0,double _d = 0):p(_p),a(_a),d(_d) {}
	friend inline bool operator <(const Event &a,const Event &b) { return a.a < b.a; }
};

inline void solve()
{
	for (int i = 1;i <= M;++i) area[i] = 0;
	for (int i = 1;i <= M;++i)
	{
		int cnt = cir[i].sgn; if (cnt<0) cnt = 0; vector <Event> event;
		for (int j = 1;j < i;++j) if (cir[i] == cir[j]) cnt += cir[j].sgn;
		for (int j = 1;j <= M;++j)
			if (j != i&&cir[i] != cir[j]&&overlap(cir[j],cir[i])) cnt += cir[j].sgn;
		for (int j = 1;j <= M;++j)
			if (j != i&&intersect(cir[i],cir[j]))
			{	
				pair <Node,Node> res = crosspoint(cir[i],cir[j]);
				double alpha1 = (res.first-cir[i].C).angle(),alpha2 = (res.second-cir[i].C).angle();
				event.push_back(Event(res.second,alpha2,cir[j].sgn));
				event.push_back(Event(res.first,alpha1,-cir[j].sgn));
				cnt += (alpha2 > alpha1)*cir[j].sgn;
			}
		if (!event.size()) area[cnt] += pi*cir[i].r*cir[i].r*cir[i].sgn;
		else
		{
			sort(event.begin(),event.end());
			event.push_back(event.front());
			for (int j = 0;j+1 < (int)event.size();++j)
			{
				cnt += event[j].d;
				area[cnt] += event[j].p/event[j+1].p/2*cir[i].sgn;
				double alpha = event[j+1].a-event[j].a;
				if (alpha < 0) alpha += 2*pi;
				if (!dcmp(alpha)) continue;
				area[cnt] += alpha*cir[i].r*cir[i].r/2*cir[i].sgn;
				area[cnt] += -sin(alpha)*cir[i].r*cir[i].r/2*cir[i].sgn;
			}
		}
	}
}
