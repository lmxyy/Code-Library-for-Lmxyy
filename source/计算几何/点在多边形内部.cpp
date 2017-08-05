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
}poly;
