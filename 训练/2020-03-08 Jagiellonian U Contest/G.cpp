#include <bits/stdc++.h>

using namespace std;
const int N = 100010;
int _w;

namespace NTT {
	const int LOGN = 18;
	const int MOD = 998244353;
	const int g = 3;
	
	int a1[1<<LOGN], a2[1<<LOGN], a3[1<<LOGN];
	int y1[1<<LOGN], y2[1<<LOGN], y3[1<<LOGN];
	
	int fpow( int a, int b ) {
		int c = 1;
		while(b) {
			if( b & 1 ) c = int(1LL * c * a % MOD);
			a = int(1LL * a * a % MOD);
			b >>= 1;
		}
		return c;
	}
	int inv( int x ) {
		return fpow(x, MOD-2);
	}
	int revb( int x, int n ) {
		int ans = 0;
		n >>= 1;
		while(n) {
			ans = (ans << 1) | (x & 1);
			n >>= 1, x >>= 1;
		}
		return ans;
	}
	void ntt( int *a, int n, int *y, int rev ) {
		for( int i = 0; i < n; ++i )
			y[revb(i, n)] = a[i];
		for( int m = 1; m <= n; m <<= 1 ) {
			int wm = fpow(g, (MOD-1)/m);
			if( rev ) wm = inv(wm);
			for( int i = 0; i < n; i += m ) {
				int w = 1;
				for( int j = 0; j < m/2; ++j ) {
					int t1 = y[i+j];
					int t2 = int(1LL * y[i+j+m/2] * w % MOD);
					y[i+j] = (t1 + t2) % MOD;
					y[i+j+m/2] = (t1 - t2 + MOD) % MOD;
					w = int(1LL * w * wm % MOD);
				}
			}
		}
		if( rev ) {
			int invn = inv(n);
			for( int i = 0; i < n; ++i )
				y[i] = int(1LL * y[i] * invn % MOD);
		}
	}
	void solve( const vector<int> &a, const vector<int> &b, vector<int> &c ) {
		int n = (int)a.size();
		int m = (int)b.size();
		int len = 1;
		while( len < n+m-1 ) len <<= 1;
		for( int i = 0; i < len; ++i ) {
			a1[i] = i < n ? a[i] : 0;
			a2[i] = i < m ? b[i] : 0;
		}
		ntt(a1, len, y1, 0);
		ntt(a2, len, y2, 0);
		for( int i = 0; i < len; ++i )
			y3[i] = int(1LL * y1[i] * y2[i] % MOD);
		ntt(y3, len, a3, 1);
		c.resize(n+m-1);
		for( int i = 0; i < n+m-1; ++i )
			c[i] = a3[i];
	}
}

int n, m, t, pos[N];

vector<int> mul( const vector<int> &a, const vector<int> &b ) {
	vector<int> c;
	NTT::solve(a, b, c);
	int sz = (int)c.size();
	for( int i = 0; i < sz; ++i )
		c[i] %= m;
	for( int i = n; i < sz; ++i )
		c[i%n] += c[i];
	for( int i = 0; i < n; ++i )
		c[i] %= m;
	c.resize(n);
	return c;
}

vector<int> fpow( vector<int> a, int b ) {
	vector<int> c(n);
	c[0] = 1;
	while(b) {
		if( b & 1 ) c = mul(c, a);
		a = mul(a, a);
		b >>= 1;
	}
	return c;
}

vector<int> poly, a;

int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		_w = scanf( "%d%d%d", &n, &m, &t );
		for( int i = 0; i < n; ++i ) {
			_w = scanf( "%d", pos+i );
			--pos[i];
		}
		poly.resize(n);
		for( int i = 0; i < n; ++i )
			poly[i] = 0;
		poly[0] = m-1;
		poly[n-1] = 2;
		poly = fpow(poly, t);
		a.resize(n);
		for( int i = 0; i < n; ++i )
			a[i] = pos[i];
		a = mul(a, poly);
		for( int i = 0; i < n; ++i ) {
			if( i ) putchar(' ');
			printf( "%d", a[i]+1 );
		}
		puts("");
	}
	return 0;
}
