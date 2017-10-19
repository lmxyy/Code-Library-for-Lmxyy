// noi2009 诗人小G
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define limit (1e18)
#define maxn 100010
#define maxm 40
int N,L,P,pre[maxn],top;
char s[maxm];
long double f[maxn];
struct node { int l,r,key; }stack[maxn];

inline long double qsm(int a,int b)
{
	long double  ret = 1;
	while (b--) ret *= 1.0*a;
	return ret;
}

inline long double calc(int a,int b)
{
	return f[b]+qsm(abs(pre[a]-pre[b]-L),P);
}

inline int find(int a)
{
	int l = 1,r = top,mid;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (stack[mid].l<=a&&stack[mid].r>=a) return stack[mid].key;
		if (a < stack[mid].l) r = mid - 1;
		else l = mid + 1;
	}
}

inline void updata(int now)
{
	int l = 1,r;
	while (top)
	{
		if (calc(stack[top].l,stack[top].key) >= calc(stack[top].l,now))
			--top;
		else
		{
			l = stack[top].l,r = stack[top].r;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (calc(mid,stack[top].key) >= calc(mid,now)) r = mid - 1;
				else l = mid + 1;
			}
			stack[top].r = r;
			break;
		}
	}
	if (l <= N) stack[++top] = (node){l,N,now};
}

inline void dp()
{
	f[0] = 0;
	stack[top = 1] = (node) {1,N,0};
	for (int i = 1;i <= N;++i)
	{
		int key = find(i);
		f[i] = calc(i,key);
		updata(i);
	}
}

int main()
{
	freopen("1563.in","r",stdin);
	freopen("1563.out","w",stdout);
	int T; scanf("%d",&T);
	while (T--)
	{
		scanf("%d %d %d\n",&N,&L,&P);
		L++;
		for (int i = 1;i <= N;++i)
		{
			scanf("%s",s);
			pre[i] = strlen(s)+1+pre[i-1];			
		}
		dp();
		if (f[N] > limit) printf("Too hard to arrange\n");
		else printf("%.0Lf\n",f[N]);
		printf("--------------------\n");
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
