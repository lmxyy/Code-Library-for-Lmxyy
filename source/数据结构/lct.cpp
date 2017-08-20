
inline bool isroot(int a) { return ch[fa[a]][0] != a&&ch[fa[a]][1] != a; }

inline void update(int x) { val[x] = (val[ch[x][0]]+val[ch[x][1]]).merge(x); }
inline void pushdown(int x)
{
	if (rev[x])
	{
		int &lc = ch[x][0],&rc = ch[x][1];
		swap(lc,rc);
		if (lc) rev[lc] ^= 1;
		if (rc) rev[rc] ^= 1;
		rev[x] = false;
	}
}

inline void rotate(int x)
{
	int y = fa[x],z = fa[y],l = ch[y][1] == x,r = l^1;
	if (!isroot(y)) ch[z][ch[z][1] == y] = x; fa[x] = z;
	if (ch[x][r]) fa[ch[x][r]] = y; ch[y][l] = ch[x][r];
	fa[y] = x; ch[x][r] = y; update(y); update(x);
}
inline void splay(int x)
{
	int top = 0,i;
	for (i = x;!isroot(i);i = fa[i]) stk[++top] = i; stk[++top] = i;
	while (top) pushdown(stk[top--]);
	while (!isroot(x))
	{
		int y = fa[x],z = fa[y];
		if (!isroot(y))
		{
			if ((ch[y][0] == x)^(ch[z][0] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}

inline int access(int x)
{
	int t = 0;
	for (t = 0;x;t = x,x = fa[x])
		splay(x),ch[x][1] = t,update(x);
	return t;
}
inline int evert(int x) { int t; rev[t = access(x)] ^= 1; return t; }
inline int find(int x)
{
	x = access(x);
	while (pushdown(x),ch[x][0]) x = ch[x][0];
	return x;
}
inline void cut(int x,int y)
{
	evert(x); access(y); splay(y);
	if (ch[y][0] != x||ch[x][1] != 0) return;
	ch[y][0] = fa[x] = 0; update(x); update(y);
}
inline void link(int x,int y) { fa[evert(x)] = y; }
