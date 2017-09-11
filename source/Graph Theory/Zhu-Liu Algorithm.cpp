
struct Directed_MT
{
	struct Edge
	{
		int u,v,w;
		inline Edge() = default;
		inline Edge(int _u,int _v,int _w):u(_u),v(_v),w(_w) {}
	};
	int nn,mm,n,m,vis[maxn],pre[maxn],id[maxn],in[maxn]; Edge edges[maxn],bac[maxn];

	inline void init(int _n) { n = _n; m = 0; }
	inline void AddEdge(int u,int v,int w) { edges[m++] = Edge(u,v,w); }
	inline int work(int root)
	{
		int ret = 0;
		while (true)
		{
			// 初始化
			for (int i = 0;i < n;++i) in[i] = inf+1;
			for (int i = 0;i < m;++i)
			{
				int u = edges[i].u,v = edges[i].v;
				// 找寻最小入边，删除自环
				if (edges[i].w < in[v]&&u != v)
					in[v] = edges[i].w,pre[v] = u;
			}
			// 如果没有最小入边，表示该点不连通，则最小树形图形成失败
			for (int i = 0;i < n;++i)
			{
				if (i == root) continue;
				if (in[i] == inf+1) return inf;
			}
			int cnt = 0; // 记录缩点
			memset(id,-1,sizeof id); memset(vis,-1,sizeof vis);
			in[root] = 0;
			for (int i = 0;i < n;++i)
			{
				ret += in[i]; int v = i;
				// 找寻自环
				while (vis[v] != i&&id[v] == -1&&v != root)
					vis[v] = i,v = pre[v];
				if (v != root&&id[v] == -1)
				{
					// 这里不能从i开始找，因为i有可能不在自环内
					for (int u = pre[v];u != v;u = pre[u]) id[u] = cnt;
					id[v] = cnt++;
				}
			}
			// 如果没有自环了，表示最小树形图成功了
			if (!cnt) break;
			// 找到那些不是自环的，重新给那些点进行标记
			for (int i = 0;i < n;++i)
				if (id[i] == -1) id[i] = cnt++;
			for (int i = 0;i < m;++i)
			{
				int u = edges[i].u,v = edges[i].v;
				edges[i].v = id[v]; edges[i].u = id[u];
				if (id[u] != id[v]) edges[i].w -= in[v];
			}
			// 缩点完后，点的数量就变了
			n = cnt; root = id[root];
		}
		return ret;
	}
}MT;
