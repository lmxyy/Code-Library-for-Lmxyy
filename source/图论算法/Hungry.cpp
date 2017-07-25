//匈牙利算法
//Version1
inline bool find(int x)
{
	if (cor[x]) return false;
	for (int i = side[x];i;i = next[i]) if (!used[toit[i]])
	{
		used[toit[i]] = true;
		if (!cho[toit[i]]||find(cho[toit[i]]))
		{
			cho[toit[i]] = x; map[x] = toit[i];
 			return true;
		}
	}
	return false;
}

inline void hungry()
{
	for (int i = 1;i <= p;++i)
		memset(used,false,sizeof(used)),find(i);
	for (int i = 1;i <= m;++i)
	{
		memset(used,false,sizeof(used)),cho[map[i]] = 0;
		find(i),cor[i] = true;
	}
}
//Version2
inline int find(int x)
{
    for (int i = 1;i <= n;++i)
        if (f[x][i]&&!used[i])
        {
            used[i] = true;
            if (!cho[i]||find(cho[i])) { cho[i] = x; return true; }
        }
    return false;
}

inline int hungry()
{
    int ret = 0;
    for (int i = 1;i <= n;++i)
    {
        memset(used,false,sizeof(used));
        if (find(i)) ret++;
    }
    return ret;
}
