//朱刘算法
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define maxn (25010)
#define inf (0x3fffffff)
int n,m,tot,nn,need[55],id[maxn],pre[maxn],vis[maxn],change[maxn];
double ans,in[maxn]; double wf[55]; bool exist[maxn];
struct node { int p1,p2; double cost; }edge[3010];

inline void read(int a,int b,double Cost)
{ tot++; edge[tot].p1 = a; edge[tot].p2 = b; edge[tot].cost = Cost; }

inline void init()
{ for (int i = 0;i<=nn;i++) in[i] = inf,id[i] = -1,vis[i] = -1; }
inline void zhuliu(int root)
{
	while (true)
	{
		init();
		for (int i = 1;i<=tot;i++)
		{
			int u = edge[i].p1,v = edge[i].p2;
			if (u == v||edge[i].cost>in[v]) continue;
			in[v] = edge[i].cost,pre[v] = u;
		}
		in[root] = 0; int cir = 0;
		for (int i = 0;i<=nn;i++) ans += in[i];
		for (int i = 0;i<=nn;i++)
		{
			if (in[i] == inf) continue;
			if (vis[i] == -1)
			{
				int t = i;
				while (vis[t] == -1 && id[t] == -1 && t != root)
					vis[t] = i,t = pre[t];
				if (vis[t]!=i||t==root || id[t] != -1) continue;
				for (int j = pre[t];j!=t;j = pre[j]) id[j] = cir;
				id[t] = cir++;
			}
		}
		if (!cir) break;
		for (int i = 0;i<=nn;i++)
			if (id[i] == -1 && in[i] != inf) id[i] = cir++;
		for (int i = 1;i<=tot;i++)
		{
			int u = edge[i].p1,v = edge[i].p2;
			edge[i].p1 = id[u]; edge[i].p2 = id[v];
			if (id[u] != id[v]) edge[i].cost -= in[v];
		}
		nn = cir - 1;
		root = id[root];
	}
}

int main()
{
    freopen("shopping.in","r",stdin);
    freopen("shopping.out","w",stdout);
    scanf("%d",&n);
    for (int i = 1;i<=n;i++)	
    {
		double a; int b;
		scanf("%lf %d",&a,&b);
		if (b)
		{
			nn++; need[nn] = b; change[i] = nn;
			read(0,nn,a); wf[nn] = a;
		}
		if (!b) exist[i] = true;
	}
    scanf("%d",&m);
    for (int i = 1;i<=m;i++)
    {
		int b,c; double a;
		scanf("%d%d%lf",&b,&c,&a);
		if (!exist[b]&&!exist[c])
		{
			read(change[b],change[c],a);
			wf[change[c]] = min(wf[change[c]],a);
		}
	}
    zhuliu(0);
    for (int i = 1 ; i <= n ; i ++)
		if (need[change[i]]-1 > 0)
			ans += wf[change[i]]*(need[change[i]]-1) ;
    printf("%.2lf",ans);
    fclose(stdin);fclose(stdout);
    return 0;
}
