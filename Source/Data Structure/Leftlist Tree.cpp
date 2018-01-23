// Checked by bzoj 1455
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 1000010;
int N,score[maxn],father[maxn]; bool killed[maxn];

int find(int a) { if (father[a] != a) return father[a] = find(father[a]); return a; }

template < typename Type,class Compare = std::less<Type> >
struct LeftlistTree
{
	Compare cmp; int tot;
	int dep[maxn],size[maxn]; Type v[maxn]; int lc[maxn],rc[maxn];

	inline void init() { tot = 0; }
	inline int merge(int x,int y)
	{
		if (!x||!y) return x+y;
		if (cmp(v[y],v[x])) swap(x,y);
		rc[x] = merge(rc[x],y);
		if (dep[lc[x]] < dep[rc[x]]) swap(lc[x],rc[x]);
		dep[x] = dep[rc[x]]+1;
		return x;
	}
	inline int newnode(const Type &x) { ++tot; v[tot] = x; lc[tot] = rc[tot] = dep[tot] = 0; return tot; }
	inline int insert(int x,const Type &y) { return merge(x,newnode(y)); }
	inline int pop(int x) { return merge(lc[x],rc[x]); }
};
LeftlistTree <int> heap;

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
	freopen("1455.in","r",stdin);
	N = gi(); heap.init();
	for (int i = 1;i <= N;++i) father[i] = i,heap.newnode(gi());
	for (int M = gi();M--;)
	{
		char c; do c = getchar(); while (c != 'M'&&c != 'K');
		if (c == 'M')
		{
			int x = gi(),y = gi();
			if (killed[x]||killed[y]) continue;
			x = find(x); y = find(y);
			if (x == y) continue;
			int t = heap.merge(x,y);
			father[x] = father[y] = t; 
		}
		else
		{
			int x = gi();
			if (killed[x]) puts("0");
			else
			{
				x = find(x); killed[x] = true;
				printf("%d\n",heap.v[x]);
				int t = heap.pop(x);
				father[t] = t; father[x] = t;
			}
		}
	}
	return 0;
}
