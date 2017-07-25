inline void convex()
{
    sort(pp + 1,pp + n + 1);  //x第一关键字，y第二关键字从小到大排序
    for (int i = 1;i <= n;++i)
    {
        while (m > 1&&(ch[m]-ch[m-1])/(pp[i]-ch[m-1]) <= 0) --m;
        ch[++m] = pp[i];
    }
    int k = m;
    for (int i = n - 1;i;--i)
    {
        while (m > k&&(ch[m]-ch[m-1])/(pp[i] - ch[m - 1]) <= 0) --m;
        ch[++m] = pp[i];
    }
    if (n > 1) m--;
}
