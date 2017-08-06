inline bool PointOnSegment(const Point &t,const Point &a,const Point &b)
{
	if (dcmp((t-a)/(b-a))) return false;
	if (dcmp((t-a)*(t-b)) > 0) return false;
	return true;
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
}poly;
