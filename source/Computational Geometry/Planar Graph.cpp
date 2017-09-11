// 包括平面图转对偶图
inline int dcmp(double a)
{
	if (fabs(a) <= eps) return 0;
	else if (a > 0) return 1;
	else return -1;
}
struct Node
{
	double x,y;
	inline Node(double _x = 0,double _y = 0):x(_x),y(_y) {}
	inline void read() { x = gi(),y = gi(); }
	friend inline Node operator-(const Node &a,const Node &b) { return Node(a.x-b.x,a.y-b.y); }
	friend inline double operator/(const Node &a,const Node &b) { return a.x*b.y-a.y*b.x; }
	inline double angle() { return atan2(y,x); }
}pp[maxn];
struct Segment
{
	int from,to,h,id,sur; // from号点到to号点，h为边权,suf为这条有向边维出来的平面编号。
	inline Segment(int _from = 0,int _to = 0,int _h = 0,int _id = 0,int _sur = 0):from(_from),to(_to),h(_h),id(_id),sur(_sur) {}
	friend inline bool operator<(const Segment &a,const Segment &b) { return (pp[a.to]-pp[a.from]).angle() < (pp[b.to]-pp[b.from]).angle(); }
}edge[maxm*2];
vector <int> G[maxn];

inline void nadd(int u,int v,int h) { ++ncnt; G[u].push_back(ncnt); edge[ncnt] = Segment(u,v,h); }
inline void nins(int u,int v,int h) { nadd(u,v,h); nadd(v,u,h); }

inline bool cmp(int a,int b) { return edge[a] < edge[b]; }

inline void find_surface()
{
	for (int i = 1;i <= N;++i) sort(G[i].begin(),G[i].end(),cmp);
	for (int i = 1;i <= N;++i)
	{
		int nn = G[i].size();
		for (int j = 0;j < nn;++j)
			edge[G[i][j]].id = j;
	}
	for (int i = 2;i <= ncnt;++i)
		if (!edge[i].sur)
		{
			++tot; int j = i,p,nn; vector <Node> vec;
			while (!edge[j].sur)
			{
				edge[j].sur = tot; vec.push_back(pp[edge[j].from]);
				p = edge[j].to; nn = G[p].size();
				j ^= 1; j = G[p][(edge[j].id+1)%nn];
			}
			double res = 0; nn = vec.size();
			for (j = 0;j < nn;++j)
				res += (vec[j]-vec[0])/(vec[(j+1)%nn]-vec[0]);
			res /= 2; space[tot] = res; // 第tot个平面的有向面积，外面的大平面面积为正，其余为负,大平面可能有多个（平面图不连通）
		}
	// 开始建边，以mst为例
	// for (int i = 2;i <= cnt;i += 2)
	// {
	// 	if (space[edge[i].sur]<0&&space[edge[i^1].sur]<0)
	// 		arr[++all] = (ARR) { edge[i].sur,edge[i^1].sur,edge[i].h };
	// 	else arr[++all] = (ARR) { edge[i].sur,edge[i^1].sur,inf};
	// }
}

// 点定位
struct Scan
{
	double x,y; int bel,sign;
	inline Scan(double _x = 0,double _y = 0,int _bel = 0,int _sign = 0):x(_x),y(_y),bel(_bel),sign(_sign) {}
	friend inline bool operator < (const Scan &a,const Scan &b)
	{
		if (a.x != b.x) return a.x < b.x;
		else return a.sign > b.sign;
	}
}bac[maxn*4];

struct Splay
{
	int num,root,ch[maxn][2],fa[maxn],key[maxn]; queue <int> team;

	inline int newnode()
	{
		int ret;
		if (team.empty()) ret = ++num;
		else ret = team.front(),team.pop();
		fa[ret] = ch[ret][0] = ch[ret][1] = 0;
		return ret;
	}

	inline void init() { num = 0; root = newnode(); key[root] = cnt; }

	inline void rotate(int x)
	{
		int y = fa[x],z = fa[y],l = ch[y][1] == x,r = l^1;
		if (z != 0) ch[z][ch[z][1] == y] = x;
		fa[x] = z; fa[y] = x; fa[ch[x][r]] = y;
		ch[y][l] = ch[x][r]; ch[x][r] = y;
	}

	inline void splay(int x)
	{
		while (fa[x] != 0)
		{
			int y = fa[x],z = fa[y];
			if (fa[y] != 0)
			{
				if ((ch[y][0] == x)^(ch[z][0] == y)) rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
		root = x;
	}

	inline int lower_bound(const Node &p)
	{
		int now = root,ret = 0;
		while (now)
		{
			int k = key[now];
			if ((p-pp[edge[k].from])/(pp[edge[k].to]-pp[edge[k].from]) >= 0)
				ret = k,now = ch[now][0];
			else now = ch[now][1];
		}
		return ret;
	}

	inline int find(int w)
	{
		int now = root;
		double x = pp[edge[w].to].x,y = pp[edge[w].to].y;
		double ang = (pp[edge[w].to] - pp[edge[w].from]).angle();
		while (now)
		{
			int k = key[now];
			if (k == w) return now;
			NODE p = pp[edge[k].to] - pp[edge[k].from],q = pp[edge[k].from];
			double xx = x - q.x,yy = q.y+xx/p.x*p.y;
			if (equal(yy,y))
			{
				double t = p.angle();
				now = ch[now][ang < t];
			}
			else now = ch[now][y > yy];
		}
	}

	inline void erase(int w)
	{
		int p = find(w);
		while (ch[p][0] || ch[p][1])
		{
			if (ch[p][0])
			{
				rotate(ch[p][0]);
				if (p == root) root = fa[p];
			}
			else
			{
				rotate(ch[p][1]);
				if (p == root) root = fa[p];
			}
		}
		team.push(p);
		ch[fa[p]][ch[fa[p]][1] == p] = 0;
		fa[p] = 0;
	}

	inline void insert(int w)
	{
		int now = root,pre;
		double x = pp[edge[w].from].x,y = pp[edge[w].from].y;
		double ang = (pp[edge[w].to] - pp[edge[w].from]).angle();
		double xx,yy;
		while (true)
		{
			int k = key[now];
			NODE p = pp[edge[k].to] - pp[edge[k].from],q = pp[edge[k].from];
			xx = x - q.x,yy = q.y+xx/p.x*p.y;
			if (equal(yy,y))
			{
				double t = p.angle();
				pre = now,now = ch[now][ang > t];
				if (!now)
				{
					now = newnode();
					fa[now] = pre; ch[pre][ang > t] = now; key[now] = w;
					break;
				}
			}
			else
			{
				pre = now,now = ch[now][y > yy];
				if (!now)
				{
					now = newnode();
					fa[now] = pre; ch[pre][y>yy] = now; key[now] = w;
					break;
				}
			}
		}
		splay(now);
	}
}S;

inline void locate()
{
	int nn = 0;
	for (int i = 2;i <= cnt;i += 2)
	{
		if (!dcmp(pp[edge[i].from].x-pp[edge[i].to].x)) continue;
		bac[++nn] = Scan(pp[edge[i].from].x,pp[edge[i].from].y,i,2);
		bac[++nn] = Scan(pp[edge[i].to].x,pp[edge[i].to].y,i,3);
	}
	scanf("%d",&T); double x,y;
	// 查询(x,y)所在平面
	for (int i = 1;i <= T;++i)
	{
		scanf("%lf %lf",&x,&y);
		bac[++nn] = Scan(x,y,i,0);
		scanf("%lf %lf",&x,&y);
		bac[++nn] = Scan(x,y,i,1);
	}
	sort(bac+1,bac+nn+1);
	pp[++n] = Node(-oo,-oo); pp[++n] = (oo,-oo);
	edge[++cnt] = Edge(n-1,n);
	S.init(); int p;
	for (int i = 1;i <= nn;++i)
	{
		if (bac[i].sign == 2||bac[i].sign == 3)
		{
			if (bac[i].sign == 2) S.insert(bac[i].bel);
			else S.erase(bac[i].bel);
		}
		else
		{
			p = S.lower_bound(Node(bac[i].x,bac[i].y));
			query[bac[i].bel][bac[i].sign] = edge[p].sur;
		}
	}
}
