// BZOJ - 3524
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 500010;
int N,M,tot,root[maxn];
struct Node { int lc,rc; int v; }tree[maxn*30];

void build(int &now,int l,int r)
{
	now = ++tot; if (l == r) { tree[now].v = 0; return; }
	int mid = (l+r)>>1;
	build(tree[now].lc,l,mid);
	build(tree[now].rc,mid+1,r);
}

void ins(int &now,int ref,int l,int r,int pos)
{
	now = ++tot; tree[now] = tree[ref];
	if (l == r) { tree[now].v++; return; }
	int mid = (l+r)>>1;
	if (pos <= mid) ins(tree[now].lc,tree[ref].lc,l,mid,pos);
	else ins(tree[now].rc,tree[ref].rc,mid+1,r,pos);
	tree[now].v = tree[tree[now].lc].v+tree[tree[now].rc].v;
}

inline int query(int ql,int qr)
{
	int lim = (qr-ql+1)>>1;
	int l = 1,r = N;
	int x = root[ql-1],y = root[qr];
	for (;l != r;)
	{
		int mid = (l+r)>>1;
		if (tree[tree[y].lc].v-tree[tree[x].lc].v > lim)
			y = tree[y].lc,x = tree[x].lc,r = mid;
		else y = tree[y].rc,x = tree[x].rc,l = mid+1;
	}
	if (tree[y].v-tree[x].v > lim) return l;
	else return 0;
}

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

int main()
{
	freopen("3524.in","r",stdin);
	N = gi(); M = gi(); tot = 0;
	build(root[0],1,N);
	for (int i = 1;i <= N;++i)
		ins(root[i],root[i-1],1,N,gi());
	for (int i = 1;i <= M;++i)
	{
		int l = gi(),r = gi();
		printf("%d\n",query(l,r));
	}
	return 0;
}
