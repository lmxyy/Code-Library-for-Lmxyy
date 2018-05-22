// SPOJ - QTREE
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 10010,inf = 1<<29;
int cnt,N,timestamp,side[maxn],toit[maxn*2],nxt[maxn*2],len[maxn*2];
int father[maxn],dfn[maxn],redfn[maxn],top[maxn],size[maxn],dep[maxn];
int edgeid[maxn],redgeid[maxn],tree[maxn*4],leaf[maxn];

inline void init()
{
	cnt = 1; timestamp = 0;
	memset(side,0,sizeof(*side)*(N+10));
}

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline void add(int a,int b,int c) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; len[cnt] = c; }
inline void ins(int a,int b,int c) { add(a,b,c); add(b,a,c); }

void decompose(int now,int tp)
{
	redfn[dfn[now] = ++timestamp] = now;
	top[now] = tp; int heavy = 0;
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != father[now]&&size[toit[i]] > size[heavy]) heavy = toit[i];
	if (!heavy) return;	decompose(heavy,tp);
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != father[now]&&toit[i] != heavy) decompose(toit[i],toit[i]);
}
void predfs(int now)
{
	size[now] = 1;
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != father[now])
		{
			father[toit[i]] = now;
			redgeid[edgeid[toit[i]] = i>>1] = toit[i];
			dep[toit[i]] = dep[now]+1;
			predfs(toit[i]);
			size[now] += size[toit[i]];
		}
}

inline void update(int now) { tree[now] = max(tree[now<<1],tree[now<<1|1]); }
void build(int now,int l,int r)
{
	if (l == r) { tree[now] = len[edgeid[redfn[l]]<<1]; leaf[l] = now; return; }
	int mid = (l+r)>>1;
	build(now<<1,l,mid); build(now<<1|1,mid+1,r);
	update(now);
}
void modify(int pos,int key)
{
	int now = leaf[pos]; tree[now] = key;
	for (now >>= 1;now;now >>= 1) update(now);
}
int ask(int now,int l,int r,int ql,int qr)
{
	if (l == ql&&r == qr) return tree[now];
	int mid = (l+r)>>1;
	if (qr <= mid) return ask(now<<1,l,mid,ql,qr);
	else if (ql > mid) return ask(now<<1|1,mid+1,r,ql,qr);
	else return max(ask(now<<1,l,mid,ql,mid),ask(now<<1|1,mid+1,r,mid+1,qr));
}

// // 对点操作
// inline int query(int a,int b)
// {
// 	int ret = -inf;
// 	while (top[a] != top[b])
// 	{
// 		if (dep[top[a]] < dep[top[b]]) swap(a,b);
// 		ret = max(ret,ask(1,1,N,dfn[top[a]],dfn[a]));
// 		a = father[top[a]];
// 	}
// 	if (dep[a] < dep[b]) swap(a,b);
// 	ret = max(ret,query(1,1,N,dfn[b],dfn[a]));
// 	return ret;
// }

// 对边操作
inline int query(int a,int b)
{
	int ret = -inf;
	while (top[a] != top[b])
	{
		if (dep[top[a]] < dep[top[b]]) swap(a,b);
		ret = max(ret,ask(1,1,N,dfn[top[a]],dfn[a]));
		a = father[top[a]];
	}
	if (a == b) return ret;
	if (dep[a] < dep[b]) swap(a,b);
	ret = max(ret,ask(1,1,N,dfn[b]+1,dfn[a]));
	return ret;
}

int main()
{
	freopen("qtree.in","r",stdin);
	for (int T = gi();T--;)
	{
		N = gi(); init();
		for (int i = 1,a,b,c;i < N;++i)
			a = gi(),b = gi(),c = gi(),ins(a,b,c);
		predfs(1),decompose(1,1);
		len[0] = -inf;
		build(1,1,N);
		while (true)
		{
			char s[10];
			scanf("%s",s);
			if (s[0] == 'D') break;
			else if (s[0] == 'Q')
				printf("%d\n",query(gi(),gi()));
			else
			{
				int a = gi(),b = gi();
				modify(dfn[redgeid[a]],b);
			}
		}
	}
	return 0;
}
