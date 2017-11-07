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
	static void otherfuctions()
	{
		if (((BigInteger.valueOf(mid)).pow(mid)).compareTo(N) <= 0) l = mid+1;
		digit[i] = N.mod(_d).intValue();
		Arrays.fill(cho,false);
		for (int i = 1;i <= N;++i)
		{
			String S = cin.next();
			String[] str = S.split(":");
			BigDecimal a = new BigDecimal(str[0]),b = new BigDecimal(str[1]);
			ratio[i] = a.divide(a.add(b),30,BigDecimal.ROUND_HALF_EVEN);
		}
		Arrays.sort(ratio,1,N+1);
		d = temp.gcd(a[i]);
	}
}
