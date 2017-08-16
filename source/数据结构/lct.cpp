//lct
inline bool isroot(int a)
{ return ch[fa[a]][0] != a&&ch[fa[a]][1] != a; }

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
	int t;
	for (t = 0;x;t = x,x = fa[x]) splay(x),ch[x][1] = t,update(x);
	return t;
}
inline void evert(int x) { x = access(x); rev[x] ^= 1; }
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
	ch[y][0] = fa[x] = 0; update(x);
}
inline void link(int x,int y)
{
	if (find(x) == find(y)) return;
	evert(x); fa[x] = y;
}
