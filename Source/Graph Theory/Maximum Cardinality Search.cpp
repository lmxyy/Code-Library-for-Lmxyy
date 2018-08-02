// BZOJ 1006
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<queue>
using namespace std;

const int maxn = 100010,maxm = 2000010,maxc = 510;
int N,M;
int side[maxn],toit[maxm],nxt[maxm],cnt = 1;
int seq[maxn],label[maxn],color[maxn];
bool vis[maxn],exist[maxc];

inline void add(int a,int b) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; }
inline void ins(int a,int b) { add(a,b); add(b,a); }

struct Node
{
    int key,id;
    inline Node() = default;
    inline Node(int _key,int _id):key(_key),id(_id) {}
    friend inline bool operator <(const Node &a,const Node &b) { return a.key < b.key; }
};

void mcs()
{
    priority_queue <Node> heap;
    for (int i = 1;i <= N;++i) heap.push(Node(0,i));
    int all = 0;
    while (all < N)
    {
	int now = heap.top().id; heap.pop();
	if (vis[now]) continue;
	seq[++all] = now; vis[now] = true;
	for (int i = side[now];i;i = nxt[i])
	    if (!vis[toit[i]])
		heap.push(Node(++label[toit[i]],toit[i]));
    }
}

int work()
{
    mcs();
    int ret = 0;
    for (int i = 1;i <= N;++i)
    {
	int now = seq[i];
	for (int j = 1;j <= ret;++j) exist[j] = false;
	for (int j = side[now];j;j = nxt[j])
	    if (color[toit[j]] != 0)
		exist[color[toit[j]]] = true;
	int c = 1;
	for (;c <= ret&&exist[c];++c);
	if (c > ret) ret = c;
	color[now] = c;
    }
    return ret;
}

int main()
{
    scanf("%d %d",&N,&M);
    for (int i = 1;i <= M;++i)
    {
	int a,b; 
	scanf("%d %d",&a,&b);
	ins(a,b);
    }
    printf("%d\n",work());
    return 0;
}
