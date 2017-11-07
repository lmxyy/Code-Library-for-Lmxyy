// 有$n$个实数变量$x_1,x_2,\ldots,x_n$和$m$条约束，其中第$i$条约束形如 $\sum_{i = 1}^{n}a_{i,j}x_j \leq b_i$。
// 此外这$n$个变量需要满足非负性限制，$x_j \geq 0$。
// 在满足上述所有条件的情况下，你需要指定每个变量$x_j$的取值，使得目标函数$F = \sum_{j = 1}^{n}c_jx_j$的值最大。
// 第一行三个正整数$n,m,t$。其中$t \in \{ 0,1 \}$。
// 第二行有$n$个整数$c_1,c_2,\ldots,c_n$，整数间均用一个空格分隔。
// 接下来$m$行，每行代表一条约束，其中第$i$行有$n+1$个整数$a_{i1},a_{i2},\ldots,a_{in},b_i$，整数间均用一个空格分隔。
// 如果不存在满足所有约束的解，仅输出一行``Infeasible''。
// 如果对于任意的$M$，都存在一组解使得目标函数的值大于$M$，仅输出一行``Unbounded''。
// 否则，第一行输出一个实数，表示目标函数的最大值$F$。
// 如果$t=1$，那么你还需要输出第二行，用空格隔开的$n$个非负实数，表示此时$x_1,x_2,\ldots,x_n$的取值，如有多组方案请任意输出其中一个。
// uoj 179
const int maxn = 30;

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
	return 0;
}
