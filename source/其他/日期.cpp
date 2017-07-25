//ya年ma月da日与yb年mb月db日相差几天
const int days = 365,s[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
inline bool isleap(int y)
{
	if ((!(y%400)||y%100)&&!(y%4)) return true;
	return false;
}

inline int leap(int y)
{
	if (!y) return 0;
	return y/4-y/100+y/400;
}

inline int calc(int day,int mon,int year)
{
	int res = (year-1)*days+leap(year-1);
	for (int i = 1;i < mon;++i) res += s[i];
	if (isleap(year)&&mon > 2) res++;
	res += day; return res;
}

inline int count_day(int da,int ma,int ya,int db,int mb,int yb)
{
	int resa = calc(da,ma,ya);
	int resb = calc(db,mb,yb);
	return abs(resa-resb);
}
