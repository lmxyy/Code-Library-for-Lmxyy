//Input:p,N,a p is a prime
//Output:the solutions to equation x^N=a(mod p) in [0,p-1]
inline vector <int> residue(int p,int N,int a)
{
	int g = PrimitiveRoot(p); ll m = bsgs(g,a,p);
	vector <int> ret;
	if (!a) { ret.push_back(0); return ret; }
	if (m == -1) return ret;
	ll A = N,B = p-1,C = m,x,y,d = exgcd(A,B,x,y);
	if (C % d) return ret;
	x *= (C / d)%B;
	ll delta = B / d;
	for (int i = 0;i < d;++i)
	{
		x += delta; if (x >= B) x -= B;
		ret.push_back((int)qsm(g,x,p));
	}
	sort(ret.begin(),ret.end());
	ret.erase(unique(ret.begin(),ret.end()),ret.end());
	return ret;
}
