bool spfa()
{
    memset(mark,0,sizeof(mark));
    memset(d,0x7,sizeof(d));
    d[T] = 0; mark[T] = 1;
    queue <int> team;
    team.push(T);
    while (!team.empty())
    {
        int now = team.front();
        team.pop();
        for (int i = head[now];i;i = e[i].next)
            if (e[i^1].v&&d[e[i].to] > d[now]-e[i].c)
            {
                d[e[i].to] = d[now]-e[i].c;
                if (!mark[e[i].to])
                {
                    mark[e[i].to] = true;
                    team.push(e[i].to);
                }
            }
        mark[now] = false;
    }
    if (d[0] > 10000000) return false; 
    return true;
}
 
int dfs(int x,int f)
{
    if (x == T)
    {
        mark[T] = 1;
        return f;
    }
    int used = 0,w;
    mark[x] = true;
    for (int i = head[x];i;i = e[i].next)
        if (!mark[e[i].to]&&e[i].v&&d[x]-e[i].c==d[e[i].to])
        {
            w = f - used;
            w = dfs(e[i].to,small(e[i].v,w));
            ans += w*e[i].c;
            e[i].v -= w;
            e[i^1].v += w;
            used += w;
            if (used == f) return f;
        }
    return used;
}
 
void zkw()
{
    while (spfa())
    {
        mark[T] = 1;
        while (mark[T])
        {
            memset(mark,0,sizeof(mark));
            dfs(0,inf);
        }
    }
}
