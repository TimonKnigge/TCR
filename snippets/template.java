// lstlistings skips the first [this] line
import java.io.OutputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.io.IOException;

import java.util.Arrays;
import java.math.BigInteger;

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
			// solve
		}
	}
	
	static class InputReader {
		public BufferedReader reader;
		public StringTokenizer tokenizer;
		public InputReader(InputStream st) {
			reader = new BufferedReader(new InputStreamReader(st), 32768);
			tokenizer = null;
		}
		public String next() {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					String s = reader.readLine();
					if (s == null) {
						tokenizer = null; break; }
					if (s.isEmpty()) continue;
					tokenizer = new StringTokenizer(s);
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
			return (tokenizer != null && tokenizer.hasMoreTokens()
				? tokenizer.nextToken() : null);
		}
		public int nextInt() {
			String s = next();
			if (s != null) return Integer.parseInt(s);
			else return -1; // handle appropriately
		}
	}
}
