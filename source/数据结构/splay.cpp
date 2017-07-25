//splay

inline int find(int rk)
{
	for (int now = root;;)
	{
		if (rk == size[ch[now][0]]+1) return now;
		else if (rk > size[ch[now][0]]+1)
			rk -= size[ch[now][1]]+1,now = ch[now][1];
		else now = ch[now][0];
	}
	return 0;
}

inline void rotate(int x)
{
	int y = fa[x],z = fa[y],l = ch[y][0] != x,r = l ^ 1;
	if (z) ch[z][ch[z][0] != y] = x;
	fa[x] = z; fa[y] = x; fa[ch[x][r]] = y;
	ch[y][l] = ch[x][r]; ch[x][r] = y;
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
			if ((ch[y][0] == x)^(ch[z][0]) == y) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if (!aim) root = x;
}
