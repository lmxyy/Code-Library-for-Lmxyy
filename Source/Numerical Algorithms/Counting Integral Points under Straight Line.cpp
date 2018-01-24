// POJ - 3495
// \sum_{i = 0}^{n-1} (a+bi)/m
inline ll count(ll n,ll a,ll b,ll m)
{
	if (!b) return n*(a/m);
	else if (a >= m) return n*(a/m)+count(n,a%m,b,m);
	else if (b >= m) return (n-1)*n/2*(b/m)+count(n,a,b%m,m);
	else return count((a+b*n)/m,(a+b*n)%m,m,b);
}
