const int ten[4] = {1,10,100,1000},maxl = 1010;
struct BigNumber
{
	int d[maxl];
	
	inline BigNumber(const string &s)
	{
		memset(d,0,sizeof d);
		int len = s.size(),i,j,k; d[0] = (len-1)/4+1;
		for (i = 1;i < maxl;++i) d[i] = 0;
		for (i = len-1;i >= 0;--i)
		{
			j = (len-i-1)/4+1,k = (len-i-1)%4;
			d[j] += ten[k]*(s[i]-'0');
		}
		while (d[0] > 1&& !d[d[0]]) --d[0];
	}
	
	
	inline BigNumber() { *this = BigNumber(string("0")); }

	inline string toString() const
	{
		string s(""); int i,j,temp;
		for (i = 3;i >= 1;--i) if (d[d[0]] >= ten[i]) break;
		temp = d[d[0]];
		for (j = i;j >= 0;--j) s += (char)(temp/ten[j]+'0'),temp %= ten[j];
		for (i = d[0]-1;i;--i)
		{
			temp = d[i];
			for (j = 3;j >= 0;--j) s += (char)(temp/ten[j]+'0'),temp %= ten[j];
		}
		return s;
	}

	friend inline bool operator <(const BigNumber &a,const BigNumber &b) const
	{
		if (a.d[0] != b.d[0]) return a.d[0] < b.d[0];
		for (int i = a.d[0];i;--i) if (a.d[i] != b.d[i]) return a.d[i] < b.d[i];
		return false;
	}

	friend inline BigNumber operator +(const BigNumber &a,const BigNumber &b) const
	{
		BigNumber c; int x = 0; c.d[0] = max(a.d[0],b.d[0]);
		for (int i = 1;i <= c.d[0];++i) x += a.d[i]+b.d[i],c.d[i] = x % 10000,x /= 10000;
		while (x) c.d[++c.d[0]] = x % 10000,x /= 10000;
		return c;
	}

	friend inline BigNumber operator -(const BigNumber &a,const BigNumber &b) const
	{
		BigNumber c; int x = 0; c.d[0] = a.d[0];
		for (int i = 1;i <= c.d[0];++i) x += a.d[i]-b.d[i]+10000,c.d[i] = x%10000,x = x/10000-1;
		while (c.d[0] > 1&&!c.d[c.d[0]]) --c.d[0];
		return c;
	}

	friend inline BigNumber operator *(const BigNumber &a,const BigNumber &b) const
	{
		BigNumber c; c.d[0] = a.d[0]+b.d[0];
		for (int i = 1,j,x;i <= a.d[0];++i)
		{
			for (j = 1,x = 0;j <= b.d[0];++j)
				x += a.d[i]*b.d[j]+c.d[i+j-1],c.d[i+j-1] = x%10000,x /= 10000;
			c.d[i+b.d[0]] = x;
		}
		while (c.d[0] > 1&&!c.d[c.d[0]]) --c.d[0];
		return c;
	}

	friend inline BigNumber operator *(const BigNumber &a,const int &k)
	{
		BigNumber c; int x = 0; c.d[0] = a.d[0];
		for (i = 1;i <= a.d[0];++i) x += a.d[i]*k,c.d[i] = x%10000,x /= 10000;
		while (x) c.d[++c.d[0]] = x%10000,x /= 10000;
	}

	friend inline bool operator ==(const BigNumber &a,const BigNumber &b)
	{
		if (a.d[0] != b.d[0]) return false;
		for (int i = 1;i <= a.d[0]) if (a.d[i] != b.d[i]) return false;
		return true;
	}
};
