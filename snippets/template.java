// lstlistings skips the first [this] line
import java.io.*;
import java.util.*;
import java.math.*;
public class Main { // Check what this should be called
	public static void main(String[] args) {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);
		Solver s = new Solver();
		s.solve(in, out);
		out.close();
	}
	static class Solver {
		public void solve(InputReader in, PrintWriter out) {
			int n = in.nextInt();
			BigInteger ans = BigInteger.ONE;
			for (int k = 1; k <= n; k += 1)
				ans = ans
					.multiply(new BigInteger(Integer.toString(n + k)))
					.divide(new BigInteger(Integer.toString(k)));
			ans = ans.divide(new BigInteger(Integer.toString(n + 1)));	
			out.println(String.format("c_%d = %s", n, ans.toString()));
		}
	}
	static class InputReader {
		public BufferedReader reader;
		public StringTokenizer tokenizer;
		public InputReader(InputStream st) {
			reader = new BufferedReader(new InputStreamReader(st), 32768);
			tokenizer = null;
		}
		public String nextString() {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					tokenizer = new StringTokenizer(reader.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
			return tokenizer.nextToken();
		}
		public int nextInt() { return Integer.parseInt(nextString()); }
		public long nextLong() { return Long.parseLong(nextString()); }
		public double nextDouble() {
			return Double.parseDouble(nextString());
		}	}	}
