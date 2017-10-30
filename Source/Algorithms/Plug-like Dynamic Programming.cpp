// ural 1519
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;
const int maxn = 14,maxs = 300010;
int mp[maxn][maxn],N,M,cur,last,total[2];
int size,ex,ey,head[maxs],nxt[maxs],Hash[maxs];
ll f[2][maxs],state[2][maxs];

inline void init()
{
	memset(mp,0,sizeof mp); ex = ey = 0;
	size = cur = 0; last = 1;
	total[cur] = 1;
	state[cur][1] = 0;
	f[cur][1] = 1;
}

inline void calc(ll s,ll inc)
{
	int pos = s%maxs;
	for (int i = head[pos];i;i = nxt[i])
		if (state[cur][Hash[i]] == s)
		{
			f[cur][Hash[i]] += inc;
			return;
		}
	++total[cur];
	state[cur][total[cur]] = s;
	f[cur][total[cur]] = inc;
	nxt[++size] = head[pos];
	head[pos] = size;
	Hash[size] = total[cur];
}

inline ll work()
{
	ll ret = 0;
	for (int i = 1;i <= N;++i)
	{
		for (int k = 1;k <= total[cur];++k) state[cur][k] <<= 2;
		for (int j = 1;j <= M;++j)
		{
			memset(head,0,sizeof head);
			size = 0; cur ^= 1,last ^= 1;
			total[cur] = 0;
			for (int k = 1;k <= total[last];++k)
			{
				ll s = state[last][k],num = f[last][k];
				int p = (s>>((j-1)<<1))%4,q = (s>>(j<<1))%4;
				if (!mp[i][j]) { if (!p&&!q) calc(s,num); }
				else if (!p&&!q)
				{
					if (mp[i+1][j]&&mp[i][j+1])
						calc(s+(1<<((j-1)<<1))+2*(1<<(j<<1)),num);
				}
				else if (!p&&q)
				{
					if (mp[i][j+1]) calc(s,num);
					if (mp[i+1][j]) calc(s-q*(1<<(j<<1))+q*(1<<((j-1)<<1)),num);
				}
				else if (p&&!q)
				{
					if (mp[i+1][j]) calc(s,num);
					if (mp[i][j+1]) calc(s-p*(1<<((j-1)<<1))+p*(1<<(j<<1)),num);
				}
				else if (p == 1&&q == 1)
				{
					int b = 1;
					for (int t = j+1;t <= M;++t)
					{
						int v = (s>>(t<<1))%4;
						if (v == 1) ++b; else if (v == 2) --b;
						if (b == 0)	{ s -= 1*(1<<(t<<1)); break; }
					}
					calc(s-(1<<((j-1)<<1))-(1<<(j<<1)),num);
				}
				else if (p == 2&&q == 2)
				{
					int b = 1;
					for (int t = j-2;t >= 0;--t)
					{
						int v = (s>>(t<<1))%4;
						if (v == 2) ++b; else if (v == 1) --b;
						if (b == 0)	{ s += 1*(1<<(t<<1)); break; }
					}
					calc(s-2*(1<<((j-1)<<1))-2*(1<<(j<<1)),num);
				}
				else if (p == 1&&q == 2) { if (i == ex&&j == ey) ret += num; }
				else if (p == 2&&q == 1)
					calc(s-2*(1<<((j-1)<<1))-(1<<(j<<1)),num);
			}
		}
	}
	return ret;
}

int main()
{
	freopen("1519.in","r",stdin);
	while (scanf("%d%d",&N,&M) != EOF)
	{
		init();
		for (int i = 1;i <= N;++i)
			for (int j = 1;j <= M;++j)
			{
				char ch; do ch = getchar(); while (ch != '.'&&ch != '*');
				if (ch == '.') ex = i,ey = j,mp[i][j] = 1;
			}
		cout << work() << endl;
	}
	return 0;
}
