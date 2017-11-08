inline int SmallestRepresentation(int arr[])
{
	int i = 1,j = 2,k = 0;
	while (i <= N&&j <= N&&k < N)
	{
		int t = arr[(i+k) > N?i+k-N:i+k]-arr[(j+k) > N?j+k-N:j+k];
		if (!t) ++k;
		else
		{
			if (t > 0) i = i+k+1; else j = j+k+1;
			if (i == j) ++j; k = 0;
		}
	}
	return min(i,j);
}
