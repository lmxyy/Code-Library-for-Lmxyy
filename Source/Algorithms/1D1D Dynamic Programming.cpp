// noi2009 诗人小G
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;

const double limit = 1e18;
const int maxn = 100010,maxm = 40;
int N,L,P,pre[maxn],top;
char s[maxm];
long double f[maxn];
struct Node
{
	int l,r,key;
	inline Node() = default;
	inline Node(int _l,int _r,int _key):l(_l),r(_r),key(_key) {}
}stk[maxn];

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
		if (stk[mid].l<=a&&stk[mid].r>=a) return stk[mid].key;
		if (a < stk[mid].l) r = mid - 1;
		else l = mid + 1;
	}
	return -1;
}

inline void updata(int now)
{
	int l = 1,r;
	while (top)
	{
		if (calc(stk[top].l,stk[top].key) >= calc(stk[top].l,now))
			--top;
		else
		{
			l = stk[top].l,r = stk[top].r;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (calc(mid,stk[top].key) >= calc(mid,now)) r = mid - 1;
				else l = mid + 1;
			}
			stk[top].r = r;
			break;
		}
	}
	if (l <= N) stk[++top] = Node(l,N,now);
}

inline void dp()
{
	f[0] = 0;
	stk[top = 1] =  Node(1,N,0);
	for (int i = 1;i <= N;++i)
	{
		int key = find(i);
		f[i] = calc(i,key);
		updata(i);
	}
}

int main()
{
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
	return 0;
}
