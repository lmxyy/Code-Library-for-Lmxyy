// Correct but to Be Rewritten
struct SAM
{
    int tot,tail,cnt,p,np,q,nq,sz[maxn],arr[maxn],step[maxn],tran[maxn][26],parent[maxn];
    inline SAM() { tail = tot = 1; }
    inline void insert(int c)
    {
        p = tail; np = tail = ++tot; step[np] = step[p]+1;
        for (;!tran[p][c];p = parent[p]) tran[p][c] = np;
        if (!p) parent[np] = 1;
        else
        {
            q = tran[p][c];
            if (step[p]+1 == step[q]) parent[np] = q;
            else
            {
                nq = ++tot; step[nq] = step[p]+1;
                memcpy(tran[nq],tran[q],104);
                parent[nq] = parent[q]; parent[np] = parent[q] = nq;
                for (;tran[p][c] == q;p = parent[p]) tran[p][c] = nq;
            }
        }
        sz[np] = 1;
    }
 
    inline void dfs(int now)
    {
        if (vis[now]) return; vis[now] = true;
        for (int i = 0;i < 26;++i)
			if (tran[now][i]) dfs(tran[now][i]),arr[now] += arr[tran[now][i]];
        arr[now] += sz[now];
    }
     
    inline void build()
    {
        if (!mode) for (int i = 1;i <= tot;++i) sz[i] = 1;
        else
        {
            for (int i = 2;i <= tot;++i) ++d[parent[i]];
            queue <int> team; for (int i = 1;i <= tot;++i) if (!d[i]) team.push(i);
            while (!team.empty())
            {
                int now = team.front(); team.pop();
                sz[parent[now]] += sz[now];
                if (!--d[parent[now]]) team.push(parent[now]);
            }
        }
        sz[1] = 0; dfs(1);
    }
    inline void work()
    {
        int now = 1,l = 0,rank = 0; memset(s,0,N+1);
        if (K > arr[1]) puts("-1");
        else
        {
            while (true)
            {
                rank += sz[now]; if (rank >= K) break;
                for (int i = 0;i < 26;++i)
                {
                    if (rank+arr[tran[now][i]] < K) rank += arr[tran[now][i]];
                    else { s[++l] = 'a'+i; now = tran[now][i]; break; }
                }
            }
            printf("%s",s+1);
        }
    }
}sam;
