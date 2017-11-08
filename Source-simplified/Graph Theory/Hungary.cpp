inline int find(int x)
{
    for (int i = 1;i <= n;++i)
        if (w[x][i]&&!used[i])
        {
            used[i] = true;
            if (!from[i]||match(from[i])) { from[i] = x; return true; }
        }
    return false;
}

inline int hungry()
{
    int ret = 0; memset(from,-1,sizeof from);
    for (int i = 1;i <= n;++i)
    {
        memset(used,false,sizeof(used));
        if (match(i)) ret++;
    }
    return ret;
}
