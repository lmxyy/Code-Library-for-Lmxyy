inline ll exgcd(ll a,ll b,ll c) //ax mod b = c
{
	if (a == 0) return -1;
	else if (c % a == 0) return c/a;
	ll t = exgcd(b % a,a,((-c % a)+a)%a);
	if (t == -1) return -1;
	return (t*b+c)/a;
}
