int D,root,loc[maxn]; ll len,f[maxn];

inline ll qua(ll a) { return a*a; }
struct P
{
    ll d[2],mn[2],mx[2],key,ma; ll l,r,fa,id;
    inline ll& operator[](ll x) { return d[x]; }
    inline P(ll x = 0,ll y = 0)
	{ l = 0,r = 0,d[0] = x,d[1] = y; key = ma = -inf; }
    friend inline bool operator <(P a,P b) { return a[D] < b[D]; }
}p[maxn],bac[maxn];

inline ll dis(P a,P b)
{
    ll x = a[0]-b[0],y = a[1]-b[1];
    return qua(x)+qua(y);
}
inline int jud(P a,P b)
{
    P pp1,pp2,pp3,pp4;
    pp1 = P(a.mn[0],a.mn[1]); pp2 = P(a.mn[0],a.mx[1]);
    pp3 = P(a.mx[0],a.mn[1]); pp4 = P(a.mx[0],a.mx[1]);
    if (dis(pp1,b)<=len&&dis(pp2,b)<=len&&dis(pp3,b)<=len&&dis(pp4,b)<=len)
		return 2;
    ll x = 0,y = 0;
    if (b[0] <= a.mn[0]) x = a.mn[0]-b[0];
    if (b[0] >= a.mx[0]) x = b[0]-a.mx[0];
    if (b[1] <= a.mn[1]) y = a.mn[1]-b[1];
    if (b[1] >= a.mx[1]) y = b[1]-a.mx[1];
    if (x*x+y*y<=len) return 1;
    return 0;
}

struct kdtree
{
    P t[maxn*2],T; ll ans;
    inline void updata(int k)
    {
        P l = t[t[k].l],r = t[t[k].r];
        for (int i = 0;i < 2;++i)
        {
            if (t[k].l)
				t[k].mn[i] = min(t[k].mn[i],l.mn[i]),t[k].mx[i] = max(t[k].mx[i],l.mx[i]);
            if (t[k].r)
				t[k].mn[i] = min(t[k].mn[i],r.mn[i]),t[k].mx[i] = max(t[k].mx[i],r.mx[i]);
        }
        t[k].ma = t[k].key;
        if (t[k].l) t[k].ma = max(l.ma,t[k].ma);
        if (t[k].r) t[k].ma = max(r.ma,t[k].ma);
    }

    inline int build(int l,int r,int now)
    {
        D = now; int mid = (l + r) >> 1;
        nth_element(p+l,p+mid,p+r+1);
        t[mid] = p[mid]; loc[p[mid].id] = mid;
        for (int i = 0;i < 2;++i)
            t[mid].mn[i] = t[mid].mx[i] = t[mid][i];
        if (l < mid) t[mid].l = build(l,mid-1,now^1),t[t[mid].l].fa = mid;
        if (r > mid) t[mid].r = build(mid+1,r,now^1),t[t[mid].r].fa = mid;
        updata(mid); return mid;
    }

    inline void change(int now,ll w)
    {
        t[now].key = max(t[now].key,w);
        for (;now;now = t[now].fa) updata(now);
    }

    inline void ask(int k)
    {
        if (dis(t[k],T) <= len) ans = max(ans,t[k].key);
        if (t[k].l&&ans<t[t[k].l].ma)
        {
            int sign = jud(t[t[k].l],T);
            if (sign)
            {
                if (sign == 1) ask(t[k].l);
                else ans = max(ans,t[t[k].l].ma);
            }
        }
        if (t[k].r&&ans<t[t[k].r].ma)
        {
            int sign = jud(t[t[k].r],T);
            if (sign)
            {
                if (sign == 1) ask(t[k].r);
                else ans = max(ans,t[t[k].r].ma);
            }
        }
    }
    
    inline ll query(const P &a)
    {
        ans = -inf; T = a; ask(root);
        return ans;
    }
}kd;
