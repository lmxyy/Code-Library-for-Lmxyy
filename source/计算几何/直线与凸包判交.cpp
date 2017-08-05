//O(logN)
inline double getA(const Node &a)
{
	double ret = atan2(a.y,a.x);
	if (ret <= -pi/2) ret += 2*pi;
	return ret;
}

inline int find(double x)
{
	if (x <= w[1]||x >= w[m]) return 1;
	return upper_bound(w+1,w+m+1,x)-w;
}

inline bool intersect(const Node &a,const Node &b)
{
	int i = find(getA(b-a)),j = find(getA(a-b));
	if (dcmp((b-a)/(hull[i]-a))*dcmp((b-a)/(hull[j]-a)) > 0) return false;
	else return true;
}

inline void convex()
{
	for (int i = 1;i <= N;++i)
	{
		while (m > 1&&(hull[m]-hull[m-1])/(P[i]-hull[m-1]) <= 0) --m;
		hull[++m] = P[i];
	}
	int k = m;
	for (int i = N-1;i;--i)
	{
		while (m > k&&(hull[m]-hull[m-1])/(P[i]-hull[m-1]) <= 0) --m;
		hull[++m] = P[i];
	}
	if (N > 1) m--;
	for (int i = 1;i <= m;++i)
		w[i]= getA(hull[i+1]-hull[i]);
}
