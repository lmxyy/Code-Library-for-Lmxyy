//Input:a,b,n
//Output:All the solutions in [0,n) to the equation ax=b(mod n)
inline vector <ll> LineModEquation(ll a,ll b,ll n)
{
	ll x,y,d = exgcd(a,n,x,y); vector <ll> ans;
	if (!(b % d))
	{
		x %= n; x += n; x % n;
		ans.push_back(x*(b/d)%n);
		for (ll i= 1;i < d;++i) ans.push_back((ans[0]+i*n/d)%n);
		//若找最小的，直接就是(ans[0]%(n/d))
	}
	return ans;
}
