// uoj 179
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define maxn (30)
#define eps (1e-8)

int N,M,op,tot,q[maxn],idx[maxn],idy[maxn]; double a[maxn][maxn],A[maxn];

inline void pivot(int x,int y)
{
	swap(idy[x],idx[y]);
	double tmp = a[x][y]; a[x][y] = 1/a[x][y];
	for (int i = 0;i <= N;++i) if (y != i) a[x][i] /= tmp;
	tot = 0; for (int i = 0;i <= N;++i) if (i != y&&(a[x][i] > eps||a[x][i] < -eps)) q[++tot] = i;
	for (int i = 0;i <= M;++i)
	{
		if ((x == i)||(a[i][y] < eps&&a[i][y] > -eps)) continue;
		for (int j = 1;j <= tot;++j) a[i][q[j]] -= a[x][q[j]]*a[i][y];
		a[i][y] = -a[i][y]/tmp;
	}
}

int main()
{
	freopen("179.in","r",stdin);
	freopen("179.out","w",stdout);
	scanf("%d %d %d",&N,&M,&op); srand(233);
	for (int i = 1;i <= N;++i) scanf("%lf",a[0]+i);
	for (int i = 1;i <= M;++i)
	{
		for (int j = 1;j <= N;++j) scanf("%lf",a[i]+j);
		scanf("%lf",a[i]);
	}
	for (int i = 1;i <= N;++i) idx[i] = i;
	for (int i = 1;i <= M;++i) idy[i] = i+N;
	while (true)
	{
		int x = 0,y = 0;
		for (int i = 1;i <= M;++i) if (a[i][0] < -eps&&((!x)||(rand()&1))) x = i; if (!x) break;
		for (int i = 1;i <= N;++i) if (a[x][i] < -eps&&((!y)||(rand()&1))) y = i; if (!y) return puts("Infeasible"),0;
		pivot(x,y);
	}
	while (true)
	{
		int x = 0,y = 0; double mn = 1e15;
		for (int i = 1;i <= N;++i) if (a[0][i] > eps) { y = i; break; } if (!y) break;
		for (int i = 1;i <= M;++i) if (a[i][y] > eps && a[i][0]/a[i][y] < mn) mn = a[i][0]/a[i][y],x = i; if (!x) return puts("Unbounded"),0;
		pivot(x,y);
	}
	printf("%.8lf\n",-a[0][0]); if (!op) return 0;
	for (int i = 1;i <= M;++i) if (idy[i] <= N) A[idy[i]] = a[i][0];
	for (int i = 1;i <= N;++i) printf("%.8lf ",A[i]);
	fclose(stdin); fclose(stdout);
	return 0;
}
