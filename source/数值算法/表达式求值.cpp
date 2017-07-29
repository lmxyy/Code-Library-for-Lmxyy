#include<bitset>
#include<stack>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn = 200010;
int T,N,M,pri[256],match[maxn]; bitset <maxn> A,B; char s[maxn];

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline bitset <maxn> calc(int l,int r)
{
	if (l > r) return bitset <maxn>();
	while (match[l] == r) ++l,r--;
	if (l == r) { if (s[l] == 'A') return A; else return B; }
	int cur = 0; pair <int,int> mn(1<<30,0);
	for (int i = l;i <= r;++i)
	{
		if (s[i] == '(') cur += 10;
		else if (s[i] == ')') cur -= 10;
		else if (pri[s[i]])
			if (make_pair(cur+pri[s[i]],i) < mn)
				mn = make_pair(cur+pri[s[i]],i);
	}
	int pos = mn.second; auto L = calc(l,pos-1),R = calc(pos+1,r);
	if (s[pos] == '+') return L|R;
	else if (s[pos] == '*') return L&R;
	else return ~R;
}

int main()
{
	freopen("H.in","r",stdin);
	freopen("H.out","w",stdout);
	pri['+'] = 1; pri['*'] = 2; pri['-'] = 3;
	while (++T)
	{
		N = gi(),M = gi(); if (!N) break;
		A.reset(); B.reset(); printf("Case %d: ",T);
		for (int K = gi();K--;) A[gi()] = 1;
		for (int K = gi();K--;) B[gi()] = 1;
		scanf("%s",s+1); stack <int> S;
		for (int i = 1;i <= M;++i) match[i] = -1;
		for (int i = 1;i <= M;++i)
		{
			if (s[i] == '(') S.push(i);
			else if (s[i] == ')')
			{
				int t = S.top(); S.pop();
				match[match[t] = i] = t;
			}
		}
		int tot = 0; auto ans = calc(1,M);
		for (int i = 1;i <= N;++i) tot += ans[i]; printf("%d",tot);
		for (int i = 1;i <= N;++i) if (ans[i]) printf(" %d",i); putchar('\n');
	}
	return 0;
}
