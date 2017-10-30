int side[maxv],nxt[maxe],toit[maxe],cost[maxe],pre[maxv];
int cap[maxv],arr[maxv],dis[maxv]; bool in[maxv];
int source,sink;

inline void add(int a,int b,int c,int d) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; cap[cnt] = c; cost[cnt] = d; }
inline void ins(int a,int b,int c,int d) { add(a,b,c,d); add(b,a,0,-d); }

inline bool spfa(int &Flow,int &Cost)
{
    queue <int> team; team.push(source);
    memset(dis,0x7,4*(sink+5));
    dis[source] = 0; in[source] = true;
	arr[source] = inf; arr[sink] = 0;
    while (!team.empty())
    {
        int now = team.front(); team.pop();
        for (int i = side[now];i;i = nxt[i])
        {
            if (!cap[i]) continue;
            if (dis[toit[i]] > dis[now]+cost[i])
            {
                arr[toit[i]] = min(cap[i],arr[now]); pre[toit[i]] = i;
                dis[toit[i]] = dis[now]+cost[i];
                if (!in[toit[i]]) in[toit[i]] = true,team.push(toit[i]);
            }
        }
        in[now] = false;
    }
    if (!arr[sink]) return false;
    Flow += arr[sink];
    for (int now = sink,i;now != source;now = toit[i^1])
    {
        i = pre[now]; Cost += cost[pre[now]]*arr[sink];
        cap[i] -= arr[sink]; cap[i^1] += arr[sink];
    }
    return true;
}
