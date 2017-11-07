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
