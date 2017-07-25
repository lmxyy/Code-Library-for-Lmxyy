//ac自动机
inline int newnode()
{
	memset(next[L],-1,sizeof(next[L]));
	return ++L-1;
}
inline void init() { L = 0; root = newnode(); }
inline void insert()
{
	int len = strlen(buf),now = root,i;
	for (int i = 0;i < len;++i)
	{
		if (next[now][buf[i]-'0'] == -1)
			next[now][buf[i]-'0'] = newnode();
		now = next[now][buf[i]-'0'];
	}
	end[now] = true;
}
inline void build()
{
	int now = root; queue <int> team;
	fail[root] = root;
	for (int i = 0;i < 10;++i)
	{
		if (next[now][i] == -1) next[now][i] = root;
		else fail[next[now][i]] = root,team.push(next[now][i]);
	}
	while (!team.empty())
	{
		now = team.front(); team.pop();
		for (int i = 0;i < 10;++i)
		{
			if (next[now][i] == -1)
				next[now][i] = next[fail[now]][i];
			else
			{
				fail[next[now][i]] = next[fail[now]][i];
				team.push(next[now][i]);
			}
		}
	}
}
