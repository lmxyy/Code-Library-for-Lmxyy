//0-2^n-1的格雷码,相邻两个二进制位中，恰好只有一位不同
inline vector <int> GrayCreat(int n)
{
	vector <int> res;
	for (int i = 0;i < (1<<n);++i) res.push_back(i^(i>>1));
	return res;
}
