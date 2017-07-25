//求出最小的t使得X^t = Y mod mod
inline int bsgs(int X,int Y,int mod)
{
	int m = ceil(sqrt(mod+0.5)),mul = 1,res = 1;
	if (Y == 1) return 0;
	hash.clear(); hash[Y] = 0;
	for (int i = 1;i <= m;++i)
	{
		mul = ((ll)mul*(ll)X)%mod;
		if (mul == Y) return i;
		hash[(ll)Y*(ll)mul%mod] = i;
	}
	res = mul;
	for (int i = 2;(i-1)*m <= mod;++i)
	{
		res = (ll)res*(ll)mul%mod;
		if (hash.find(res) != hash.end()) return i*m-hash[res];
	}
	return -1;
}
