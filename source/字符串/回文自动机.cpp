struct pat
{
	int next[maxn][26],fail[maxn],cnt[maxn],len[maxn],s[maxn],last,n,p;
	inline int newnode(int l) { cnt[p] = 0; len[p] = 1; return p++; }
	inline void init() { last = n = p = 0; newnode(0); newnode(-1); s[0] = -1; fail[0] = 1; }
	inline int getfail(int x) { while (s[n-len[x]-1] != s[n]) x = fail[x]; return x; }
	inline void add(int c)
	{
		c -= 'a'; s[++n] = c; int cur = getfail(last);
		if (!next[cur][c])
		{
			int now = newnode(len[cur]+2);
			fail[now] = next[getfail(fail[cur])][c];
			next[cur][c] = now;
		}
		last = next[cur][c]; cnt[last]++;
	}
}
