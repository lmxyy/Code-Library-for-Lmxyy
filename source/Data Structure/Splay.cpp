//splay

inline int find(int rk)
{
	for (int now = root;;)
	{
		if (rk == size[ch[now][0]]+1) return now;
		else if (rk > size[ch[now][0]]+1)
			rk -= size[ch[now][1]]+1,now = ch[now][1];
		else now = ch[now][0];
	}
	return 0;
}

inline int upperbound(int x)
{
	int ret = 0;
	for (int now = root;now;)
	{
		if (key[now] > x) ret = now,now = ch[now][0];
		else now = ch[now][1];
	}
	return ret;
}
inline int lowerbound(int x)
{
	int ret = 0;
	for (int now = root;now;)
	{
		if (key[now] >= x) ret = now,now = ch[now][0];
		else now = ch[now][1];
	}
	return ret;
}

inline void rotate(int x)
{
	int y = fa[x],z = fa[y],l = ch[y][0] != x,r = l^1;
	if (z) ch[z][ch[z][0] != y] = x; fa[x] = z;
	if (ch[x][r]) fa[ch[x][r]] = y;
	ch[y][l] = ch[x][r]; fa[y] = x; ch[x][r] = y;
	update(y); update(x);
}
inline void splay(int x,int aim) //aim is x's father.
{
	int top = 0;
	for (int i = x;i;i = fa[i]) stack[++top] = i;
	while (top) pushdown(stack[top--]);
	while (fa[x] != aim)
	{
		int y = fa[x],z = fa[y];
		if (z != aim)
		{
			if ((ch[y][0] == x)^(ch[z][0] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if (!aim) root = x;
}

// 维修数列
#include<cassert>
#include<queue>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 500010,inf = 1<<29;
int N,M,root,cnt,arr[maxn],tag[maxn],key[maxn],fa[maxn],ch[maxn][2],lb[maxn],rb[maxn];
int wb[maxn],sum[maxn],size[maxn],stk[maxn]; bool rev[maxn]; char cmd[20]; queue <int> team;

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline int newnode(int x = 0)
{
	int ret;
	if (!team.empty())
		ret = team.front(),team.pop();
	else ret = ++cnt;
	key[ret] = sum[ret] = lb[ret] = rb[ret] = wb[ret] = x;
	rev[ret] = false; tag[ret] = inf; size[ret] = 1;
	return ret;
}

inline void pushdown(int now)
{
	int lc = ch[now][0],rc = ch[now][1];
	if (rev[now])
	{
		if (lc)
		{
			swap(ch[lc][0],ch[lc][1]);
			swap(lb[lc],rb[lc]); rev[lc] ^= 1;
		}
		if (rc)
		{
			swap(ch[rc][0],ch[rc][1]);
			swap(lb[rc],rb[rc]); rev[rc] ^= 1;
		}
		rev[now] = false;
	}
	if (tag[now] != inf)
	{
		if (lc)
		{
			key[lc] = tag[lc] = tag[now]; sum[lc] = tag[lc]*size[lc];
			if (tag[lc] > 0) lb[lc] = rb[lc] = wb[lc] = sum[lc];
			else lb[lc] = rb[lc] = wb[lc] = tag[lc];
		}
		if (rc)
		{
			key[rc] = tag[rc] = tag[now]; sum[rc] = tag[rc]*size[rc];
			if (tag[rc] > 0) lb[rc] = rb[rc] = wb[rc] = sum[rc];
			else lb[rc] = rb[rc] = wb[rc] = tag[rc];
		}
		tag[now] = inf;
	}
}

inline void update(int now)
{
	// pushdown(now);
	int lc = ch[now][0],rc = ch[now][1];
	size[now] = size[lc]+size[rc]+1;
	sum[now] = sum[lc]+sum[rc]+key[now];
	if (lc&&rc)
	{
		lb[now] = max(lb[lc],max(sum[lc]+key[now],sum[lc]+key[now]+lb[rc]));
		rb[now] = max(rb[rc],max(sum[rc]+key[now],sum[rc]+key[now]+rb[lc]));
		wb[now] = max(wb[lc],wb[rc]); wb[now] = max(wb[now],key[now]);
		wb[now] = max(wb[now],rb[lc]+key[now]); wb[now] = max(wb[now],lb[rc]+key[now]);
		wb[now] = max(wb[now],rb[lc]+key[now]+lb[rc]);
	}
	else if (lc)
	{
		lb[now] = max(lb[lc],sum[lc]+key[now]);
		rb[now] = max(key[now],key[now]+rb[lc]);
		wb[now] = max(wb[lc],key[now]);
		wb[now] = max(wb[now],rb[lc]+key[now]);
	}
	else if (rc)
	{
		rb[now] = max(rb[rc],sum[rc]+key[now]);
		lb[now] = max(key[now],key[now]+lb[rc]);
		wb[now] = max(wb[rc],key[now]);
		wb[now] = max(wb[now],lb[rc]+key[now]);
	}
	else sum[now] = lb[now] = rb[now] = wb[now] = key[now];
}

inline int build(int l,int r)
{
	int mid = (l+r) >> 1,ret = newnode(arr[mid]);
	if (l < mid) ch[ret][0] = build(l,mid-1),fa[ch[ret][0]] = ret;
	if (r > mid) ch[ret][1] = build(mid+1,r),fa[ch[ret][1]] = ret;
	update(ret); return ret;
}

inline void init()
{
	root = newnode(); ch[root][1] = newnode(); fa[2] = 1;
	for (int i = 1;i <= N;++i) arr[i] = gi();
	ch[2][0] = build(1,N); fa[ch[2][0]] = 2;
	update(2); update(1);
}

inline int find(int rk)
{
	for (int now = root;;)
	{
		pushdown(now);
		if (rk == size[ch[now][0]]+1) return now;
		else if (rk > size[ch[now][0]]+1)
			rk -= size[ch[now][0]]+1,now = ch[now][1];
		else now = ch[now][0];
	}
	return 0;
}

inline void rotate(int x)
{
	int y = fa[x],z = fa[y],l = ch[y][0] != x,r = l^1;
	if (z) ch[z][ch[z][0] != y] = x;
	fa[x] = z; fa[y] = x; fa[ch[x][r]] = y;
	ch[y][l] = ch[x][r]; ch[x][r] = y;
	update(y); update(x);
}
inline void splay(int x,int aim)
{
	int top = 0;
	for (int i = x;i;i = fa[i]) stk[++top] = i;
	while (top) pushdown(stk[top--]);
	while (fa[x] != aim)
	{
		int y = fa[x],z = fa[y];
		if (z != aim)
		{
			if ((ch[y][0] == x)^(ch[z][0] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if (!aim) root = x;
}

inline void Delete(int &now)
{
	if (!now) return;
	Delete(ch[now][0]);
	Delete(ch[now][1]);
	team.push(now); now = 0;
}

inline void print()
{
	for (int i = 1;i <= cnt;++i)
		printf("%d:%d %d\n",i,ch[i][0],ch[i][1]);
	for (int i = 1;i <= cnt;++i)
		printf("%d:%d\n",i,fa[i]);
	
}

inline void laydown(int now)
{
	if (!now) return;
	pushdown(now);
	laydown(ch[now][0]);
	printf("%d ",key[now]);
	laydown(ch[now][1]);
	update(now);
}

int main()
{
	//freopen("C.in","r",stdin);
	N = gi(); M = gi(); init();
	while (M--)
	{
		scanf("%s",cmd);
		if (cmd[0] == 'I')
		{
			int pos = gi(),a = find(pos+1),b = find(pos+2); N = gi();
			for (int i = 1;i <= N;++i) arr[i] = gi();
			splay(a,0); splay(b,a);
			ch[b][0] = build(1,N); fa[ch[b][0]] = b;
			update(b); update(a);
		}
		else if (cmd[0] == 'D')
		{
			int pos = gi(); N = gi();
			int a = find(pos),b = find(pos+N+1);
			splay(a,0); splay(b,a);
			Delete(ch[b][0]); update(b); update(a);
		}
		else if (cmd[0] == 'M'&&cmd[2] == 'K')
		{
			int pos = gi(); N = gi();
			int a = find(pos),b = find(pos+N+1);
			splay(a,0); splay(b,a);
			key[ch[b][0]] = tag[ch[b][0]] = gi(); sum[ch[b][0]] = tag[ch[b][0]]*size[ch[b][0]];
			if (tag[ch[b][0]] > 0) lb[ch[b][0]] = rb[ch[b][0]] = wb[ch[b][0]] = sum[ch[b][0]];
			else lb[ch[b][0]] = rb[ch[b][0]] = wb[ch[b][0]] = tag[ch[b][0]];			
			update(b); update(a);
		}
		else if (cmd[0] == 'R')
		{
			int pos = gi(); N = gi();
			int a = find(pos),b = find(pos+N+1);
			splay(a,0); splay(b,a);
			rev[ch[b][0]] ^= 1;
			swap(ch[ch[b][0]][0],ch[ch[b][0]][1]);
			swap(lb[ch[b][0]],rb[ch[b][0]]);
			update(b); update(a);
		}
		else if (cmd[0] == 'G')
		{
			int pos = gi(); N = gi();
			int a = find(pos),b = find(pos+N+1);
			splay(a,0); splay(b,a);
			printf("%d\n",sum[ch[b][0]]);
		}
		else
		{
			splay(1,0); splay(2,1);
			printf("%d\n",wb[ch[2][0]]);
		}
	}
	return 0;
}
