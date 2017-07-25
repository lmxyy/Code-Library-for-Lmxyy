inline void build(int &now,int l,int r)
{
	now = ++cnt; if (l == r) return;
	int mid = (l+r)>>1;
	build(tree[now].ch[0],l,mid); build(tree[now].ch[1],mid+1,r);
}

inline void ins(int &now,int ref,int l,int r,int key)
{
	now = ++cnt; tree[now] = tree[ref];
	if (l == r) { ++tree[now].sum; return; }
	int mid = (l+r) >> 1;
	if (key <= mid) ins(tree[now].ch[0],tree[ref].ch[0],l,mid,key);
	else ins(tree[now].ch[1],tree[ref].ch[1],mid+1,r,key);
	tree[now].sum = tree[tree[now].ch[0]].sum+tree[tree[now].ch[1]].sum;
}
