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
