// Input and Output of Int
// Be careful of Max_Int and Min_Int
inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline void pi(int a)
{
	if (!a) putchar('0');
	if (a < 0) a = -a,putchar('-');
	int num[10],n = 0;
	while (a) num[n++] = a%10,a /= 10;
	for (int i = n-1;i >= 0;--i) putchar('0'+num[i]);
}
