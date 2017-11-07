//判断是否存在x，使得x^2=a mod n，存在返回最小x，否则返回-1
inline int modsqr(int a,int n)
{
	int b,k,i,x;
	if (n == 2) return a & 1;
	if (qsm(a,(n-1)>>1,n) == 1)
	{
		if (n % 4 == 3) x = qsm(a,(n+1)>>2,n);
		else
		{
			for (b = 1;qsm(b,(n-1)>>1,n) == 1;++b);
			i = (n-1)>>1; k = 0;
			do
			{
				i >>= 1,k >>= 1;
				if (!((qsm(a,i,n)*(ll)qsm(b,k,n)+1)%n)) k += ((n-1)>>1);
			}
			while (!(i&1));
			x = (qsm(a,(i+1)>>1,n)*(ll)qsm(b,k>>1,n)) % n;
		}
		if ((x << 1) > n) x = n-x;
		return x;
	}
	return -1;
}
