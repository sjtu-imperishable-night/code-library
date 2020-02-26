#include <bits/stdc++.h>

using namespace std;
const int N = 2048;
const int M = 512;
const int MOD = 998244353;
const int INV2 = (MOD+1)>>1;
int _w;

void add_mod( int &a, int b ) {
	a += b;
	a -= a >= MOD ? MOD : 0;
}

void sub_mod( int &a, int b ) {
	a -= b;
	a += a < 0 ? MOD : 0;
}

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

int a[N][M];

void input() {
	const int K = 100010;
	
	static int n, ta[K], tb[K];
	
	_w = scanf( "%d", &n );
	for( int i = 0; i < n; ++i )
		_w = scanf( "%d", ta+i );
	for( int i = 0; i < n; ++i )
		_w = scanf( "%d", tb+i );
	
    for( int i = 0; i < n; ++i )
		++a[ta[i]][tb[i]];
}

void fwt( int *p ) {
	for( int m = 2; m <= M; m <<= 1 )
		for( int i = 0; i < M; i += m )
			for( int j = 0; j < (m>>1); ++j ) {
				int x = p[i+j];
				int y = p[i+j+(m>>1)];
				p[i+j] = x;
				add_mod( p[i+j], y );
				p[i+j+(m>>1)] = x;
				sub_mod( p[i+j+(m>>1)], y );
			}
}

void ifwt( int *p ) {
	for( int m = 2; m <= M; m <<= 1 )
		for( int i = 0; i < M; i += m )
			for( int j = 0; j < (m>>1); ++j ) {
				int x = p[i+j];
				int y = p[i+j+(m>>1)];
				p[i+j] = x;
				add_mod( p[i+j], y );
				p[i+j] = int(1LL * p[i+j] * INV2 % MOD);
				p[i+j+(m>>1)] = x;
				sub_mod( p[i+j+(m>>1)], y );
				p[i+j+(m>>1)] = int(1LL * p[i+j+(m>>1)] * INV2 % MOD);
			}
}

void fwt_line( int line, int rev ) {
	if( rev == 1 ) {
		fwt( a[line] );
	} else {
		assert( rev == -1 );
		ifwt( a[line] );
	}
}

namespace NTT {
	const int g = 3;
	
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
				for( int j = 0; j < (m>>1); ++j ) {
					int t1 = y[i+j];
					int t2 = int(1LL * y[i+j+(m>>1)] * w % MOD);
					y[i+j] = t1;
					add_mod( y[i+j], t2 );
					y[i+j+(m>>1)] = t1;
					sub_mod( y[i+j+(m>>1)], t2 );
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
}

void fft_col( int col, int rev ) {
	static int ta[N], ty[N];
	
	for( int i = 0; i < N; ++i )
		ta[i] = a[i][col];

	NTT::ntt(ta, N, ty, rev == -1);
	
	for( int i = 0; i < N; ++i )
		a[i][col] = ty[i];
}

void solve() {
	for( int j = 0; j < M; ++j )
		fft_col(j, 1);
	for( int i = 0; i < N; ++i )
		fwt_line(i, 1);

	for( int i = 0; i < N; ++i )
		for( int j = 0; j < M; ++j )
			a[i][j] = fpow( a[i][j], 4 );
	
	for( int i = 0; i < N; ++i )
		fwt_line(i, -1);
	for( int j = 0; j < M; ++j )
		fft_col(j, -1);
}

int main() {
	input();
	solve();
	int ans = 0;
	for( int i = 0; i < N; ++i )
		for( int j = 0; j < M; ++j )
			add_mod( ans, int(1LL * a[i][j] * fpow(i, j) % MOD) );
	printf( "%d\n", ans );
	return 0;
}
