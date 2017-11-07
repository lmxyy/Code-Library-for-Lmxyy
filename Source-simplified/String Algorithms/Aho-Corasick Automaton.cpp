// ac自动机
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
