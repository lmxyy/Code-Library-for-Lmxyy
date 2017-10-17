// 最小乘积匹配
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 80,inf = 1<<29;
int N,ans,A[maxn][maxn],B[maxn][maxn];

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

struct KM
{
	int w[maxn][maxn],lx[maxn],ly[maxn],match[maxn],way[maxn],slack[maxn]; bool used[maxn];

	inline void init()
	{
		for (int i = 1;i <= N;++i)
			match[i] = lx[i] = ly[i] = way[i] = 0;
	}

	inline void hungary(int x)
	{
		match[0] = x; int j0 = 0;
		for (int j = 0;j <= N;++j)
			slack[j] = -inf,used[j] = false;
		do
		{
			used[j0] = true;
			int i0 = match[j0],delta = -inf,j1 = 0;
			for (int j = 1;j <= N;++j)
				if (!used[j])
				{
					int cur = -w[i0][j]-lx[i0]-ly[j];
					if (cur > slack[j]) slack[j] = cur,way[j] = j0;
					if (slack[j] > delta) delta = slack[j],j1 = j;
				}
			for (int j = 0;j <= N;++j)
			{
				if (used[j]) lx[match[j]] += delta,ly[j] -= delta;
				else slack[j] -= delta;
			}
			j0 = j1;
		}
		while (match[j0]);
		do
		{
			int j1 = way[j0];
			match[j0] = match[j1];
			j0 = j1;
		}
		while (j0);
	}

	inline void work() { for (int i = 1;i <= N;++i) hungary(i); }
	
	inline int get_ans()
	{
		int sum = 0;
		for (int i = 1;i <= N;++i)
		{
			// if (w[match[i]][i] == inf) ; // 无解
			if (match[i] > 0) sum += w[match[i]][i];
		}
		return sum;
	}

	inline void getp(int &x,int &y)
	{
		x = y = 0;
		for (int i = 1;i <= N;++i)
			x += A[match[i]][i],y += B[match[i]][i];
	}
}km;

inline void work(int X1,int Y1,int X2,int Y2)
{
	km.init();
	for (int i = 1;i <= N;++i)
		for (int j = 1;j <= N;++j)
			km.w[i][j] = (X2-X1)*B[i][j]+(Y1-Y2)*A[i][j];
	km.work();
	if (km.get_ans() >= X2*Y1-X1*Y2) return;
	int x,y; km.getp(x,y);
	ans = min(ans,x*y);
	work(X1,Y1,x,y); work(x,y,X2,Y2);
}

int main()
{
	// freopen("B.in","r",stdin);
	for (int T = gi();T--;)
	{
		N = gi(); ans = inf;
		for (int i = 1;i <= N;++i) for (int j = 1;j <= N;++j) A[i][j] = gi();
		for (int i = 1;i <= N;++i) for (int j = 1;j <= N;++j) B[i][j] = gi();
		int X1,Y1,X2,Y2;
		km.init();
		for (int i = 1;i <= N;++i)
			for (int j = 1;j <= N;++j)
				km.w[i][j] = A[i][j];
		km.work(); km.getp(X1,Y1);
		km.init();
		for (int i = 1;i <= N;++i)
			for (int j = 1;j <= N;++j)
				km.w[i][j] = B[i][j];
		km.work(); km.getp(X2,Y2);
		ans = min(X1*Y1,X2*Y2);
		work(X1,Y1,X2,Y2);
		cout << ans << endl;
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
