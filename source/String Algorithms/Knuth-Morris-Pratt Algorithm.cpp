// To Be Verified
void cal_next(char *str, int *next, int len)
{
	int i,j;
	next[0] = -1;
	for (int i = 1; i < len; i++)
	{
		j = next[i - 1];
		while (str[j+1] != str[i]&&(j >= 0)) j = next[j];
		if (str[i] == str[j+1]) next[i] = j + 1;
		else next[i] = -1;
	}
}

int KMP(char *str,int slen, char *ptr,int plen,int *next)
{
	int s_i = 0,p_i = 0;
	while (s_i < slen&&p_i < plen)
	{
		if (str[s_i] == ptr[p_i]) s_i++,p_i++;
		else
		{
			if (!p_i) s_i++;
			else p_i = next[p_i-1] + 1;
		}
	}
	return (p_i == plen)?(s_i - plen):-1;
}
