// ac自动机
inline int newnode()
{
	memset(nxt[L],-1,sizeof(nxt[L]));
	return ++L-1;
}
inline void init() { L = 0; root = newnode(); }
inline void insert()
{
	int len = strlen(buf),now = root;
	for (int i = 0;i < len;++i)
	{
		if (nxt[now][buf[i]-'0'] == -1)
			nxt[now][buf[i]-'0'] = newnode();
		now = nxt[now][buf[i]-'0'];
	}
	end[now] = true;
}
inline void build()
{
	int now = root; queue <int> team;
	fail[root] = root;
	for (int i = 0;i < 10;++i)
	{
		if (nxt[now][i] == -1) nxt[now][i] = root;
		else fail[nxt[now][i]] = root,team.push(nxt[now][i]);
	}
	while (!team.empty())
	{
		now = team.front(); team.pop();
		for (int i = 0;i < 10;++i)
		{
			if (nxt[now][i] == -1)
				nxt[now][i] = nxt[fail[now]][i];
			else
			{
				fail[nxt[now][i]] = nxt[fail[now]][i];
				team.push(nxt[now][i]);
			}
		}
	}
}
