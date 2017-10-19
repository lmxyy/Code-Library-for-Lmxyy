// Code 1
import java.io.*;
import java.math.*;
import java.util.*;

public class Main
{
	final static int lhh = 998244353,maxn = 1655;
	static long jc[] = new long [maxn];
	
	static int calc(BigInteger N)
	{
		if (N.compareTo(BigInteger.ONE) <= 0) return 0;
		// System.out.println(N);
		int l = 2,r = 1650,mid;
		while (l <= r)
		{
			mid = (l+r)>>1;
			if (((BigInteger.valueOf(mid)).pow(mid)).compareTo(N) <= 0) l = mid+1;
			else r = mid-1;
		}
		// System.out.println(l+" "+r);
 		int ret = (int)jc[r]-1,d = l; if (ret < 0) ret += lhh;
		int digit[] = new int[d]; BigInteger _d = BigInteger.valueOf(l);
		for (int i = 0;i < d;++i)
		{
			digit[i] = N.mod(_d).intValue();
			N = N.divide(_d);
		}
		// for (int i = d-1;i >= 0;--i) System.out.print(digit[i]);
		// System.out.println();
		boolean cho[] = new boolean[d],safe = false,exist = true;
		Arrays.fill(cho,false);
		int per[] = new int [d];
		for (int i = d-1;i >= 0;--i)
		{
			int cur = -1;
			if (safe)
			{
				int down = i == d-1?1:0;
				for (int j = d-1;j >= down;--j)
				{
					if (cho[j] == true) continue;
					cur = j; break;
				}
				if (cur == -1) { exist = false; break; }
				cho[cur] = true; per[i] = cur;
			}
			else
			{
				if (cho[digit[i]] == true)
				{
					// System.out.println(i+":"+digit[i]);
					while (i < d)
					{
						cur = -1;
						int down = i == d-1?1:0;
						for (int j = digit[i]-1;j >= down;--j)
						{
							if (cho[j] == true) continue;
							cur = j; break;
						}
						// System.out.println(cur+":"+i);
						if (cur == -1) { ++i; if (i < d) cho[per[i]] = false; }
						else { cho[cur] = true; per[i] = cur; break; }
					}
					
					if (cur == -1) { exist = false; break; }
					safe = true;
				}
				else
				{
					if (digit[i] == 0&&i == d-1) { exist = false; break; }
					per[i] = digit[i];
					cho[digit[i]] = true;
				}
			}
		}
		// for (int i = d-1;i >= 0;--i) System.out.print(per[i]);
		// System.out.println();
		if (!exist) return ret;
		for (int i = d-1;i >= 0;--i)
		{
			int tmp = per[i];
			for (int j = d-1;j > i;--j)
				if (per[j] < per[i]) --tmp;
			ret += jc[i]*tmp%lhh;
			if (ret >= lhh) ret -= lhh;
		}
		ret++; if (ret >= lhh) ret -= lhh;
		ret -= jc[d-1]; if (ret < 0) ret += lhh;
		// System.out.println(ret);
		return ret;
	}

	public static void main(String args[])
	{
		jc[0] = 1;
		for (int i = 1;i <= 1650;++i)
			jc[i] = jc[i-1]*(long)i%lhh; 
		Scanner cin = new Scanner(System.in);
		int T = cin.nextInt();
		
		while (T-- > 0)
		{
			BigInteger l = cin.nextBigInteger(),r = cin.nextBigInteger();
			int ans = calc(r)-calc(l.subtract(BigInteger.ONE));
			if (ans < 0) ans += lhh; System.out.println(ans);
		}
		// calc(BigInteger.valueOf(123455));
	}
}

//Code 2
import java.io.*;
import java.util.*;
import java.math.*;
public class Main
{
	static BigDecimal ratio[] = new BigDecimal[110];
	public static void main(String[] args)
	{
		Scanner cin = new Scanner(System.in);
		int T = cin.nextInt();
		for (int Case = 1;Case <= T;++Case)
		{
			int N = cin.nextInt();
			for (int i = 1;i <= N;++i)
			{
				String S = cin.next();
				String[] str = S.split(":");
				BigDecimal a = new BigDecimal(str[0]),b = new BigDecimal(str[1]);
				ratio[i] = a.divide(a.add(b),30,BigDecimal.ROUND_HALF_EVEN);
			}
			Arrays.sort(ratio,1,N+1);
			BigDecimal res = new BigDecimal(0),_1 = new BigDecimal(1); int ans = 0;
			for (int i = 1;i <= N;++i)
			{
				res = res.add(ratio[i]);
				if (res.compareTo(_1) < 0) ans = i;
				else break;
			}
			System.out.println("Case #"+Case+": "+ans);
		}
	}
}

// Code 3
import java.math.*;
import java.util.*;
public class Main
{
	static BigInteger d,ret,temp,yy;
	static int n,dd;
	static boolean mark = true;
	static BigInteger[] a = new BigInteger[20];
	public static void main(String[] args)
	{
		Scanner in = new Scanner (System.in);
		n = in.nextInt();
		temp = BigInteger.ONE;
		ret = BigInteger.ZERO;
		for (int i = 0;i < n;++i)
		{
			int k = in.nextInt();
			a[i] = BigInteger.valueOf(k);
			d = temp.gcd(a[i]);
			temp = temp.multiply(a[i]).divide(d);
		}
		for (int i = 1;i < (1<<n);++i)
		{
			mark = false; yy = BigInteger.ONE;
			for (int j = 0;j < n;++j) if (((1 << j) & i) > 0) { mark = !mark; d = a[j].gcd(yy); yy = yy.multiply(a[j]).divide(d); }
			if (mark) ret = ret.add(temp.divide(yy));
			else ret = ret.subtract(temp.divide(yy));
		}
		d = ret.gcd(temp);
		System.out.println(ret.divide(d));
		System.out.println(temp.divide(d));
	}
}

// Code 4
import java.io.*;
import java.math.*;
import java.util.*;

public class Main
{
	public static String reverse(String str) { return new StringBuffer(str).reverse().toString(); }

	public static void main(String args[])
	{
		Scanner cin = new Scanner(System.in);
		int T = cin.nextInt(); BigInteger zero = BigInteger.valueOf(0);
		while (T-- > 0)
		{
			int base1 = cin.nextInt(),base2 = cin.nextInt();
			String S = cin.next(); int len = S.length();
			System.out.println(base1+" "+S);
			BigInteger res = BigInteger.valueOf(0),b1 = BigInteger.valueOf(base1),b2 = BigInteger.valueOf(base2);
			for (int i = 0;i < len;++i)
			{
				res = res.multiply(b1);
				int rep = 0;
				if (S.charAt(i) >= '0'&&S.charAt(i) <= '9') rep = S.charAt(i)-'0';
				else if (S.charAt(i) >= 'A'&&S.charAt(i) <= 'Z') rep = 10+S.charAt(i)-'A';
				else rep = 36+S.charAt(i)-'a';
				res = res.add(BigInteger.valueOf(rep));
			}
			String ret = new String();
			// System.out.println(res);
			if (res.compareTo(zero) == 0) ret += '0';
			else
				while (res.compareTo(zero) > 0)
				{
					long val = res.remainder(b2).longValue();
					// System.out.println(val);
					if (val < 10) ret += (char)(val+'0');
					else if (val < 36) ret += (char)(val+'A'-10);
					else ret += (char)(val+'a'-36);
					res = res.divide(b2);
				}
			System.out.println(base2+" "+reverse(ret)+"\n");
		}
	}
}
