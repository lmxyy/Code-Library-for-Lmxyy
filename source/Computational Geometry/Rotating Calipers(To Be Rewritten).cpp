inline void jam()  //凸包上最大四边形面积
{
    for (int i = 1;i <= m;++i) ch[i+m] = ch[i];  //凸包倍长
    for (int p1 = 1,p2,p3,p4;p1 <= m;++p1)
    {
        p2 = p1 + 1;
        p3 = p2 + 1;
        p4 = p3 + 1;
        for (;p3 < p1 + m - 1;++p3)
        {
            Line l = ((SEG) { ch[p1],ch[p3] }).extend();//枚举对角线,线段变成直线
            while (p2 < p3 && l.dis(ch[p2]) < l.dis(ch[p2 + 1])) ++p2;//点到直线距离
            while (p4 < p1 + m && l.dis(ch[p4]) < l.dis(ch[p4 + 1])) ++p4;  
            ans = max(ans,(l.dis(ch[p2])+l.dis(ch[p4]))*(ch[p1] - ch[p3]).len()/2);//更新答案
        }
    }
}
