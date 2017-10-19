// isap:有毒
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

int source;         // 源点
int sink;           // 汇点
int p[max_nodes];   // 可增广路上的上一条弧的编号
int num[max_nodes]; // 和 t 的最短距离等于 i 的节点数量
int cur[max_nodes]; // 当前弧下标
int d[max_nodes];   // 残量网络中节点 i 到汇点 t 的最短距离
bool visited[max_nodes];

// 预处理, 反向 BFS 构造 d 数组
bool bfs()
{
    memset(visited, 0, sizeof(visited));
    queue<int> Q;
    Q.push(sink);
    visited[sink] = 1;
    d[sink] = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (iterator_t ix = G[u].begin(); ix != G[u].end(); ++ix) {
            Edge &e = edges[(*ix)^1];
            if (!visited[e.from] && e.capacity > e.flow) {
                visited[e.from] = true;
                d[e.from] = d[u] + 1;
                Q.push(e.from);
            }
        }
    }
    return visited[source];
}

// 增广
int augment()
{
    int u = sink, df = __inf;
    // 从汇点到源点通过 p 追踪增广路径, df 为一路上最小的残量
    while (u != source) {
        Edge &e = edges[p[u]];
        df = min(df, e.capacity - e.flow);
        u = edges[p[u]].from;
    }
    u = sink;
    // 从汇点到源点更新流量
    while (u != source) {
        edges[p[u]].flow += df;
        edges[p[u]^1].flow -= df;
        u = edges[p[u]].from;
    }
    return df;
}

int max_flow()
{
    int flow = 0;
    bfs();
    memset(num, 0, sizeof(num));
    for (int i = 0; i < num_nodes; i++) num[d[i]]++;
    int u = source;
    memset(cur, 0, sizeof(cur));
    while (d[source] < num_nodes) {
        if (u == sink) {
            flow += augment();
            u = source;
        }
        bool advanced = false;
        for (int i = cur[u]; i < G[u].size(); i++) { 
            Edge& e = edges[G[u][i]];
            if (e.capacity > e.flow && d[u] == d[e.to] + 1) {
                advanced = true;
                p[e.to] = G[u][i];
                cur[u] = i;
                u = e.to;
                break;
            }
        }
        if (!advanced) { // retreat
            int m = num_nodes - 1;
            for (iterator_t ix = G[u].begin(); ix != G[u].end(); ++ix)
                if (edges[*ix].capacity > edges[*ix].flow)
                    m = min(m, d[edges[*ix].to]);
            if (--num[d[u]] == 0) break; // gap 优化
            num[d[u] = m+1]++;
            cur[u] = 0;
            if (u != source)
                u = edges[p[u]].from;
        }
    }
    return flow;
}
//By mxh
#define maxn 1010
const int INF=1<<30;
int n,m;
int S,T;
struct Edge
{
	int v,flow,next;
}	e[510010];
int g[maxn],tot=1;//tot初值必须赋为1 
void addedge(int x,int y,int flow)
{
	e[++tot].v=y;e[tot].flow=flow;e[tot].next=g[x];g[x]=tot;
	e[++tot].v=x;e[tot].flow=0;e[tot].next=g[y];g[y]=tot;
}
int w[maxn],hash[maxn],d[maxn];
int que[maxn],pre1[maxn],pre2[maxn],p[maxn];
bool vis[maxn];
int maxflow()
{
	for (int i=1;i<=n;i++)	hash[i]=0,d[i]=0,vis[i]=false;
	for (int i=1;i<=n;i++)	p[i]=g[i];
	//hash[0]=n;
	int l,r;
	l=r=1;
	que[1]=T;hash[0]=1;vis[T]=true;
	while (l<=r)
	{
		int u=que[l++];
		for (int i=g[u];i;i=e[i].next)
		if ((i&1) && !vis[e[i].v])
		{
			que[++r]=e[i].v;
			vis[e[i].v]=true;
			d[e[i].v]=d[u]+1;
			hash[d[e[i].v]]++;
		}
	}
	for (int i=1;i<=n;i++)
	if (!vis[i])	d[i]=n,hash[n]++;
	int flow=INF;
	int ans=0;
	int u=S;
	while (d[S]<n)
	{
		w[u]=flow;
		bool bo=true;
		for (int i=p[u];i;i=e[i].next)
		if (e[i].flow && d[e[i].v]==d[u]-1)
		{
			flow=min(flow,e[i].flow);
			p[u]=i;
			pre1[e[i].v]=u;
			pre2[e[i].v]=i;
			u=e[i].v;
			bo=false;
			if (u==T)
			{
				ans+=flow;
				while (u!=S)
				{
					e[pre2[u]].flow-=flow;
					e[pre2[u]^1].flow+=flow;
					u=pre1[u];
				}
				flow=INF;
			}
			break;
		}
		if (!bo)	continue;
		int minx=n,pos=0;
		for (int i=g[u];i;i=e[i].next)
		if (e[i].flow && d[e[i].v]<minx)	minx=d[e[i].v],pos=i;
		p[u]=pos;
		hash[d[u]]--;
		if (hash[d[u]]==0)	break;
		d[u]=minx+1;
		hash[d[u]]++;
		if (u!=S)	u=pre1[u],flow=w[u];
	}
	return ans;
}
