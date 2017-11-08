// mcs用于求完美消除序列
// 弦图判定：先求完美消除序列。再vi,vi+1...vn导出子图中找到与vi相邻标号最小的点，设vj，检查vj是否与每个vi的邻接点相邻。
struct Node
{
	int key,ord;
	friend inline bool operator < (const Node &a,const Node &b) { return a.key > b.key; }
};
multiset <Node> S;

inline void mcs()
{
	int i,u;
	for (i = 1;i <= n;++i) S.insert((Node){0,i});
	while (all < n)
	{
		u = (*S.begin()).ord; S.erase(S.begin()); if (in[u]) continue;
		in[u] = true; per[++all] = u;
		for (i = side[u];i;i = next[i])
			if (!in[toit[i]])
			{
				label[toit[i]]++;
				S.insert((Node){label[toit[i]],toit[i]});
			}
	}
}
