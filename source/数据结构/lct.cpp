//lct
inline bool isroot(int a)
{ return ch[fa[a]][0] != a&&ch[fa[a]][1] != a; }
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
