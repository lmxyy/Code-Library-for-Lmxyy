// r单调右移，l只会在sqrt(N)中移动，保证每次undo的复杂度可行即可。
#include<vector>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 1000010,len = 200,inf = 1<<29;
int N,M,pre[maxn],A[maxn],ans[maxn];

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline void upd(int &a,int b) { if (a < b) a = b; }

struct Trie
{
	int nxt[maxn][2],val[maxn],root,cnt; vector < pair<int,int> > vec;
	inline int newnode() { val[++cnt] = inf; memset(nxt[cnt],0,8); return cnt; }
	inline void init() { val[0] = inf; cnt = 0; root = newnode(); }

	inline int query(int key,int num)
	{
		int now = root,ret = 0; 
		for (int i = 19;i >= 0;--i)
		{
			int dir = !(num&(1<<i));
			if (val[nxt[now][dir]] <= key)
				ret |= (1<<i),now = nxt[now][dir];
			else now = nxt[now][dir^1];
		}
		return ret;
	}

	inline void insert(int key,int num,int mode) { insert(root,19,key,num,mode); }
	inline void insert(int &now,int dep,int key,int num,int mode)
	{
		if (!now) now = newnode();
		if (dep < 0)
		{
			if (mode) vec.push_back(make_pair(num,val[now]));
			val[now] = min(val[now],key); return;
		}
		insert(nxt[now][(num&(1<<dep)) > 0],dep-1,key,num,mode);
		val[now] = min(val[nxt[now][0]],val[nxt[now][1]]);
	}

	inline void change(int now,int dep,int num,int v)
	{
		if (dep < 0) { val[now] = v; return; }
		change(nxt[now][(num&(1<<dep)) > 0],dep-1,num,v);
		val[now] = min(val[nxt[now][0]],val[nxt[now][1]]);
	}
	
	inline void undo()
	{
		reverse(vec.begin(),vec.end());
		for (auto x:vec) change(root,19,x.first,x.second);
		vec.clear();
	}
}tree1,tree2;

struct Query
{
	int l,r,id;
	inline void read(int i) { l = gi(),r = gi(),id = i; }
	friend inline bool operator <(const Query &a,const Query &b) { return a.l < b.l; }
}query[maxn];
inline bool cmp(const Query &a,const Query &b) { return a.r < b.r; }

inline void work(int l,int r)
{
	int lim = query[r].l;
	sort(query+l,query+r+1,cmp);
	tree1.init(); tree2.init();
	for (int i = l;i <= r;++i)
	{
		if (query[i].r <= lim)
		{
			for (int j = query[i].l;j <= query[i].r;++j)
			{
				tree1.insert(A[j],pre[A[j]-1],false);
				tree2.insert(-A[j],pre[A[j]],false);
				upd(ans[query[i].id],tree1.query(A[j],pre[A[j]]));
				upd(ans[query[i].id],tree2.query(-A[j],pre[A[j]-1]));
			}
			tree1.init(),tree2.init();
		}
		else
		{
			int pos = lim,mx = 0;
			for (;i <= r;++i)
			{
				while (pos < query[i].r)
				{
					++pos;
					tree1.insert(A[pos],pre[A[pos]-1],false);
					tree2.insert(-A[pos],pre[A[pos]],false);
					upd(mx,tree1.query(A[pos],pre[A[pos]]));
					upd(mx,tree2.query(-A[pos],pre[A[pos]-1]));
				}
				upd(ans[query[i].id],mx);
				for (int j = lim;j >= query[i].l;--j)
				{
					tree1.insert(A[j],pre[A[j]-1],true);
					tree2.insert(-A[j],pre[A[j]],true);
					upd(ans[query[i].id],tree1.query(A[j],pre[A[j]]));
					upd(ans[query[i].id],tree2.query(-A[j],pre[A[j]-1]));
				}
				tree1.undo(); tree2.undo();
			}
			break;
		}
	}
}

int main()
{
	// freopen("A.in","r",stdin);
	for (int i = 1;i <= 1000000;++i) pre[i] = pre[i-1]^i;
	N = gi(); M = gi();
	for (int i = 1;i <= N;++i) A[i] = gi();
	for (int i = 1;i <= M;++i) query[i].read(i);
	sort(query+1,query+M+1);
	for (int i = 1,j;i <= M;i = j)
	{
		for (j = i;j <= M&&query[j].l-query[i].l <= len;++j);
		work(i,j-1);
	}
	for (int i = 1;i <= M;++i) printf("%d\n",ans[i]);
	return 0;
}
