int N,cnt,timestamp,dfn[maxn],f[maxn][25],side[maxn],H[maxn];
int dep[maxn],toit[maxn],nxt[maxn],last[maxn],cost[maxn],stk[maxn];
ll best[maxn],g[maxn];

inline void add(int a,int b,int c) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; cost[cnt] = c; }
inline void ins(int a,int b,int c) { add(a,b,c); add(b,a,c); }

inline void nadd(int a,int b,int idc)
{
	if (a == b) return;
	if (last[a] != idc) side[a] = 0,last[a] = idc;
	if (last[b] != idc) side[b] = 0,last[b] = idc;
	nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b;
}

inline bool cmp(int a,int b) { return dfn[a] < dfn[b]; }

inline void dfs(int now)
{
	dfn[now] = ++timestamp;
	for (int i = 1;(1<<i) <= dep[now];++i)
		f[now][i] = f[f[now][i-1]][i-1];
	for (int i = side[now];i;i = nxt[i])
		if (toit[i] != f[now][0])
		{
			best[toit[i]] = min(best[now],(ll)cost[i]);
			dep[toit[i]] = dep[now]+1;
			f[toit[i]][0] = now; dfs(toit[i]);
		}
}

inline int jump(int a,int step) { for (int i = 0;step;step >>= 1,++i) if (step&1) a = f[a][i]; return a; }
inline int lca(int a,int b)
{
	if (dep[a] < dep[b]) swap(a,b);
	a = jump(a,dep[a]-dep[b]);
	if (a == b) return a;
	for (int i = 0;i >= 0;)
	{
		if (f[a][i] != f[b][i])
			a = f[a][i],b = f[b][i],++i;
		else --i;
	}
	return f[a][0];
}

inline void work(int idc)
{
	cnt = 0; int K = gi(),tot,top;
	for (int i = 1;i <= K;++i) H[i] = gi();
	sort(H+1,H+K+1,cmp); H[tot = 1] = H[1];
	for (int i = 2;i <= K;++i) if (lca(H[tot],H[i]) != H[tot]) H[++tot] = H[i];
	stk[top = 1] = 1;
	for (int i = 1;i <= tot;++i)
	{
		int ans = lca(H[i],stk[top]);
		while (true)
		{
			if (dep[ans] >= dep[stk[top-1]]) { nadd(ans,stk[top--],idc); break; }
			nadd(stk[top-1],stk[top],idc); --top;
		}
		if (stk[top] != ans) stk[++top] = ans;
		if (stk[top] != H[i]) stk[++top] = H[i];
	}
	while (--top) nadd(stk[top],stk[top+1],idc);
	// dp(1); printf("%lld\n",g[1]);
}
