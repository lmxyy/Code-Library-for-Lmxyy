inline bool PointOnSegment(const Point &t,const Point &a,const Point &b)
{
	if (dcmp((t-a)/(b-a))) return false;
	if (dcmp((t-a)*(t-b)) > 0) return false;
	return true;
}

inline bool in(const Point &a,const Point &b,const Point &c)
{
	double alpha = a.angle(),beta = b.angle(),gamma = c.angle(); // angle返回[0,2pi)
	if (alpha <= beta) return dcmp(gamma-alpha) > 0&&dcmp(beta-gamma) > 0;
	else return dcmp(gamma-alpha) > 0||dcmp(beta-gamma) > 0; 
}

struct Polygon
{
	int n; Point a[maxn];
	inline Polygon() {}
	inline void read()
	{
		n = gi();
		for (int i = 0;i < n;++i) a[i].read();
		a[n] = a[0];
	}
	// 点是否在多边形内部，内部为1，外部为0，边界为2，不管顺逆时针
	inline int Point_In(const Point &t) const
	{
		int num = 0;
		for (int i = 0;i < n;++i)
		{
			if (PointOnSegment(t,a[i],a[i+1])) return 2;
			int k = dcmp((a[i+1]-a[i])/(t-a[i]));
			int d1 = dcmp(a[i].y-t.y),d2 = dcmp(a[i+1].y-t.y);
			if (k > 0&&d1 <= 0&&d2 > 0) ++num;
			if (k < 0&&d2 <= 0&&d1 > 0) --num; 
		}
		return num != 0;
	}
	// 判断多边形的方向，true为逆时针，false为顺时针，用叉积判断哪个多
	inline bool CalculateClockDirection()
	{
		int res = 0;
		for (int i = 0;i < n;++i)
		{
			int p = i-1,s = i+1,sgn;
			if (p < 0) p += n; if (s >= n) s -= n;
			sgn = dcmp((a[i]-a[p])/(a[s]-a[i]));
			if (sgn) { if (sgn > 0) ++res; else --res; }
		}
		return res > 0;
	}
	// 判断多边形方向，true为逆时针，false为顺时针，用Green公式
	inline bool CalculateClockDirection()
	{
		double res = 0;
		for (int i = 0;i < n;++i)
			res -= 0.5*(a[i+1].y+a[i].y)*(a[i+1].x-a[i].x);
		return res > 0;
	}

	// 线段p[ia]p[ib]是否有点严格在多边形内部，先判断线段是否与多边形边界有交，再判断ab是否与多边形有交，内部false，外部true
	inline bool can(int ia,int ib)
	{
		Point a = P[ia],b = P[ib],v = b-a;
		if (in(P[ia+1]-a,P[ia-1]-a,b-a)||in(P[ib+1]-b,P[ib-1]-b,a-b)) return false;
		for (register int i = 0;i < N;++i)
		{
			if (dcmp(v/(P[i]-a))*dcmp(v/(P[i+1]-a)) < 0&&dcmp(vec[i]/(a-P[i]))*dcmp(vec[i]/(b-P[i])) < 0)
				return false;
			if (PointOnSegment(a,P[i],P[i+1])||PointOnSegment(b,P[i],P[i+1])) return false;
			if (PointOnSegment(P[i],a,b)||PointOnSegment(P[i+1],a,b)) return false;
		}
		return true;
	}
}poly;
