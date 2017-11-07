//splay
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
