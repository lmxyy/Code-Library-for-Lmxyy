//isap:有毒

inline void bfs()
{
    queue <int> team; memcpy(cur,side,4*(N+1));
    team.push(sink); d[sink] = 1; in[sink] = true;
    while (!team.empty())
    {
        int now = team.front(); team.pop(); nd[d[now]]++;
        for (int i = side[now];i;i = nxt[i])
            if (cap[i^1] && !in[toit[i]])
                in[toit[i]] = true,d[toit[i]] = d[now]+1,team.push(toit[i]);
    }
	for (int i = 1;i <= N;++i) if (!in[i]) nd[d[i] = N+1]++;
}
inline int isap()
{
    int res = 0,now = source,ca = inf;
	bfs(); 
    while (d[source] <= N)
    {
        if (now == sink)
        {
            while (now != source)
            {
                cap[pre[now]] -= ca; cap[pre[now]^1] += ca;
                now = toit[pre[now]^1];
            }
            res += ca; ca = inf;
        }
        bool flag = false; arr[now] = ca;
        for (int i = cur[now];i;i = nxt[i])
            if (cap[i]&&d[toit[i]]==d[now]-1)
            {
                cur[now] = pre[toit[i]] = i; ca = min(ca,cap[i]);
                now = toit[i]; flag = true; break;
            }
        if (flag) continue; if (!--nd[d[now]]) break; int arg = N;
        for (int i = side[now];i;i = nxt[i])
            if (cap[i]&&d[toit[i]] < arg) arg = d[toit[i]];
        ++nd[d[now]=arg+1]; cur[now] = side[now];
        if (now != source) ca = arr[now = toit[pre[now]^1]];
    }	
    return res;
}
