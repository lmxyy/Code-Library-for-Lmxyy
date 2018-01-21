// poj1741
#include<algorithm>
#include<vector>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define lowbit(a) (a&-a)
const int maxn = 10010;
int ans,N,K,cnt,centriod;
int side[maxn],nxt[maxn*2],toit[maxn*2],len[maxn*2],size[maxn],large[maxn];
bool vis[maxn]; int tot,tree[maxn];

inline void init()
{
	cnt = 1; ans = 0;
	memset(side,0,sizeof(*tree)*(N+10));
	memset(vis,false,sizeof(*vis)*(N+10));
}

inline void ins(int a,int b) { for (;a <= tot;a += lowbit(a)) tree[a] += b; }
inline int calc(int a) { int ret = 0; for (;a;a -= lowbit(a)) ret += tree[a]; return ret; }

inline void add(int a,int b,int c) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; len[cnt] = c; }
inline void ins(int a,int b,int c) { add(a,b,c); add(b,a,c); }

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

void getroot(int now,int fa,int rest)
{
	size[now] = 1; large[now] = 0;
	for (int i = side[now];i;i = nxt[i])
	{
		if (toit[i] == fa||vis[toit[i]]) continue;
		getroot(toit[i],now,rest);
		size[now] += size[toit[i]];
		large[now] = max(large[now],size[toit[i]]);
	}
	large[now] = max(large[now],rest-size[now]);
	if (large[now] < large[centriod]) centriod = now;
}
inline int find_root(int now,int rest) { centriod = 0; getroot(now,0,rest); return centriod; }

vector <int> disc,tmp;

void predfs(int now,int fa,int dis)
{
	disc.push_back(dis);
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != fa&&!vis[toit[i]])
			predfs(toit[i],now,dis+len[i]);
}
void dfs(int now,int fa,int dis)
{
	size[now] = 1;
	tmp.push_back(dis); if (dis <= K) ++ans;
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != fa&&!vis[toit[i]])
			dfs(toit[i],now,dis+len[i]),size[now] += size[toit[i]];
}

void subdivide(int now)
{
	vis[now] = true;
	disc.clear();
	for (int i = side[now];i;i = nxt[i])
	{
		if (vis[toit[i]]) continue;
		predfs(toit[i],now,len[i]);
	}
	sort(disc.begin(),disc.end());
	disc.erase(unique(disc.begin(),disc.end()),disc.end());
	tot = disc.size();
	for (int i = 1;i <= tot;++i) tree[i] = 0;
	for (int i = side[now];i;i = nxt[i])
	{
		if (vis[toit[i]]) continue;
		tmp.clear(); dfs(toit[i],now,len[i]);
		for (int j = 0;j < (int)tmp.size();++j)
		{
			int lim = K-tmp[j],pos = upper_bound(disc.begin(),disc.end(),lim)-disc.begin();
			ans += calc(pos);
		}
		for (int j = 0;j < (int)tmp.size();++j)
			ins(lower_bound(disc.begin(),disc.end(),tmp[j])-disc.begin()+1,1);
	}
	for (int i = side[now];i;i = nxt[i])
	{
		if (vis[toit[i]]) continue;
		subdivide(find_root(toit[i],size[toit[i]]));
	}
}

int main()
{
	while (true)
	{
		scanf("%d %d",&N,&K);
		if (N == 0&&K == 0) break;
		init();
		for (int i = 1,a,b,c;i < N;++i)
			a = gi(),b = gi(),c = gi(),ins(a,b,c);
		large[0] = 1<<30; subdivide(find_root(1,N));
		printf("%d\n",ans);
	}
	return 0;
}
