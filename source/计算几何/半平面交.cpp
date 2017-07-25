//半平面交
inline int half_plane_intersection()
{
    sort(lines+1,lines+tot+1);  //直线按斜率排序
    int head,tail;
    qq[head = tail = 1] = lines[1];
    for (int i = 2;i <= tot;++i)
    {
        while (head < tail&&!ol(lines[i],pp[tail-1])) --tail;
        while (head < tail&&!ol(lines[i],pp[head])) ++head;
        qq[++tail] = lines[i];
        if (para(qq[tail],qq[tail-1]))
        {
            tail--;
            if (ol(qq[tail],lines[i].p)) qq[tail] = lines[i];
        }
        if (head < tail) pp[tail-1] = cp(qq[tail],qq[tail-1]);
    }
    while (head < tail && !ol(qq[head],pp[tail-1])) --tail;
    if (tail-head <= 0) return 0;
    pp[tail] = cp(qq[tail],qq[head]);
    for (int i = head;i <= tail;++i) pol[++m] = pp[i];  //半平面交点
    pol[0] = pol[m];
    return m;
}
