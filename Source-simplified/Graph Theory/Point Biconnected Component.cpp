// Source: HackerRank - bonnie-and-clyde
inline void tj(int now,int fa)
{
	dfn[now] = low[now] = ++cnt; int child = 0;
	for (int i = side[now];i;i = nxt[i])
	{
		if (toit[i] == fa) continue;
		if (!dfn[toit[i]])
		{
			S.push(i>>1); tj(toit[i],now); ++child;
			low[now] = min(low[now],low[toit[i]]);
			if (low[toit[i]] >= dfn[now])
			{
				cut[now] = true; ++tot;
				while (true)
				{
					int t = S.top(); S.pop();
					bel[toit[t<<1]].push_back(tot);	bel[toit[t<<1|1]].push_back(tot);
					bcc[tot].push_back(toit[t<<1]); bcc[tot].push_back(toit[t<<1|1]);
					if (t == (i>>1)) break;
				}
			}
		}
		else low[now] = min(low[now],dfn[toit[i]]);
	}
	if (!fa&&child == 1) cut[now] = false;
}

inline void build()
{
	vector <int> cuts; cnt = 1;
	for (int i = 1;i <= tot;++i)
	{
		sort(bcc[i].begin(),bcc[i].end());
		bcc[i].erase(unique(bcc[i].begin(),bcc[i].end()),bcc[i].end());
	}
	for (int i = 1;i <= N;++i) if (cut[i]) cuts.push_back(i);
	for (auto x:cuts)
	{
		sort(bel[x].begin(),bel[x].end());
		bel[x].erase(unique(bel[x].begin(),bel[x].end()),bel[x].end());
		++tot; for (auto y:bel[x]) nins(tot,y);
		bel[x].clear(); bel[x].push_back(tot); bcc[tot].push_back(x);
	}
}
