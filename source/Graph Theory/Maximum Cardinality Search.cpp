#include<algorithm>
#include<queue>
#include<cstdio>
#include<cstdlib>
#include<set>
using namespace std;

#define maxn 10010
#define maxc 510
#define maxm 1000010
int tot,n,m,cnt,color[maxn][maxc],label[maxn],all;
int side[maxn],next[maxm*2],toit[maxm*2],per[maxn];
bool in[maxn];
struct node
{
	int key,ord;
	friend bool operator < (node a,node b) {return a.key > b.key; }
};
multiset <node> S;

inline void add(int a,int b)
{
	next[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; 
}

inline void ins(int a,int b){add(a,b); add(b,a);}

inline void mcs()
{
	int i,u;
	for (i = 1;i <= n;++i) S.insert((node){0,i});
	while (all < n)
	{
		u = (*S.begin()).ord; S.erase(S.begin()); if (in[u]) continue;
		in[u] = true; per[++all] = u;
		for (i = side[u];i;i = next[i])
			if (!in[toit[i]])
			{
				label[toit[i]]++;
				S.insert((node){label[toit[i]],toit[i]});
			}
	}
}

inline void paint()
{
	int p,i,j,t;
	for (p = 1;p <= n;++p)
	{
		i = per[p];
		for (j = 1;j <= tot;++j)
			if (!color[i][j]) {t = j; break; }
		if (j == tot + 1) t = ++tot;
		for (j = side[i];j;j = next[j])
			color[toit[j]][t] = true;
	}
}

int main()
{
	freopen("1006.in","r",stdin);
	freopen("1006.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1;i <= m;++i)
	{ int a,b; scanf("%d %d",&a,&b); ins(a,b); }
	mcs();
	paint();
	printf("%d",tot);
	fclose(stdin); fclose(stdout);
	return 0;
}
