#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define maxn (600010)
int N,M,root[maxn],size[maxn],v[maxn],dep[maxn],l[maxn],r[maxn],tot;

inline int Merge(int x,int y)
{
	if (!x||!y) return x+y;
	if (v[x]>v[y]) swap(x,y);
	r[x] = Merge(r[x],y);
	if (dep[l[x]] < dep[r[x]]) swap(l[x],r[x]);
	dep[x] = dep[r[x]]+1;
	return x;
}
inline int Init(int x) { v[++tot] = x; l[tot] = r[tot] = dep[tot] = 0; return tot;}
inline int Insert(int x,int y) { return Merge(x,Init(y)); }
inline int pop(int x) { return Merge(l[x],r[x]); }

inline int read()
{
	char ch; int f = 1,ret = 0;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

int main()
{
	freopen("1050.in","r",stdin);
	freopen("1050.out","w",stdout);
	scanf("%d %d",&N,&M);
	for (int i = 1;i <= N;++i) root[i] = Init(read()),size[i] = 1;
	while (M--)
	{
		int opt = read();
		if (!opt)
		{
			int a = read()+1,b = read()+1;
			if (size[b]) root[a] = Merge(root[a],root[b]);
			size[a] += size[b]; size[b] = 0;
		}
		else if (opt == 1)
		{
			int a = read()+1;
			if (!size[a]) puts("-1");
			else printf("%d\n",v[root[a]]),root[a] = pop(root[a]),--size[a];
		}
		else
		{
			int a = read()+1; ++size[a];
			root[a] = Insert(root[a],read());
		}
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
