//By yxj
inline ll exgcd(ll a,ll b,ll c) //ax mod b = c
{
	if (a == 0) return -1;
	else if (c % a == 0) return c/a;
	ll t = exgcd(b % a,a,((-c % a)+a)%a);
	if (t == -1) return -1;
	return (t*b+c)/a;
}

//Input:a,b,&x,&y,ax+by = gcd(a,b)
//Output:gcd(a,b)
inline int exgcd(int a,int b,int &x,int &y)
{
	if (!b) { x = 1,y = 0; return a; }
	else
	{
		int r = exgcd(b,a%b,y,x);
		y -= x*(a/b); return r;
	}
}
