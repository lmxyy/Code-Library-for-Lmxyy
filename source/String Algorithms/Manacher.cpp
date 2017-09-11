inline void ready()
{
    for (int i = 1;i <= 2*l1+1;++i)
		{ if (i & 1) bac[i] = '#'; else bac[i] = s[i>>1]; }
    bin[0] = 1;
    for (int i = 1;i <= l1;++i)
		hash[i] = hash[i-1]*37+s[i]-'A'+1,bin[i] = 37*bin[i-1];
}

inline void manacher()
{
    rad[1] = 1;int best = 1;
    for (int i = 2;i <= 2*l1+1;++i)
    {
        int j;
        if (best+rad[best]-1<i) j = 1;
        else j = min(rad[2*best-i],best+rad[best]-i)+1;
        while (i-j+1&&i+j-1<=2*l1+1&&bac[i-j+1]==bac[i+j-1])
        {
            if (bac[i+j-1] != '#')
            {
                ull h = (hash[(i+j-1)>>1]-hash[((i-j+1)>>1)-1]*bin[j]);
                if (!exist1[h%rhl1]||!exist2[h%rhl2]||!exist3[h%rhl3])
                {
                    exist1[h%rhl1]=exist2[h%rhl2]=exist3[h%rhl3] = true;
                    ++tot,have[tot][0] = (i-j+1)>>1;
					have[tot][1] = (i+j-1)>>1;
                }
            }
            ++j;
        }
        rad[i] = j-1;
        if (i+rad[i]>best+rad[best]) best = i;
    }
}
