#include <bits/stdc++.h>

using namespace std;
const int MOD = 1e9+7;
const int N = 100010;
int _w;

inline void add_mod( int &a, int b ) {
	a += b;
	a -= a >= MOD ? MOD : 0;
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

int n, p, np, a[N];

void read_p() {
	int x, y;
	_w = scanf( "%d%d", &x, &y );
	p = int(1LL * x * inv(y) % MOD);
	np = (1 - p + MOD) % MOD;
}

int calc( int num, int b1, int b2 ) {
	return ((num >> b1) & 1) | (((num >> b2) & 1) << 1);
}

void trans( int q[4], int x ) {
	int tmp[4] = {0};
	for( int i = 0; i < 4; ++i ) {
		add_mod( tmp[i], int(1LL * q[i] * np % MOD) );
		add_mod( tmp[i^x], int(1LL * q[i] * p % MOD) );
	}
	for( int i = 0; i < 4; ++i ) q[i] = tmp[i];
}

int table[4][N][4];

void init() {
	for( int x = 0; x < 4; ++x ) {
		table[x][0][0] = 1;
		for( int i = 1; i < N; ++i ) {
			for( int j = 0; j < 4; ++j )
				table[x][i][j] = table[x][i-1][j];
			trans( table[x][i], x );
		}
	}
}

void fwt( int A[4], int B[4], int C[4] ) {
	int tmp[4] = {0};
	for( int i = 0; i < 4; ++i )
		for( int j = 0; j < 4; ++j )
			add_mod( tmp[i^j], int(1LL * A[i] * B[j] % MOD) );
	for( int i = 0; i < 4; ++i )
		C[i] = tmp[i];
}

int solve( int b1, int b2 ) {
	int cnt[4] = {0};
	for( int i = 1; i <= n; ++i ) {
		int x = calc( a[i], b1, b2 );
		++cnt[x];
	}
	int q[4] = {1, 0, 0, 0};
	for( int i = 0; i < 4; ++i )
		fwt(q, table[i][cnt[i]], q);
	return int(1LL * q[3] * (1 << b1) % MOD * (1 << b2) % MOD);
}

int main() {
	_w = scanf( "%d", &n );
	read_p();
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d", a+i );
	init();
	
	int ans = 0;
	for( int i = 0; i < 30; ++i )
		for( int j = i; j < 30; ++j ) {
			int now = solve(i, j);
			// printf( "i = %d, j = %d, now = %d\n", i, j, now );
			if( i != j ) now = (now * 2) % MOD;
			ans = (ans + now) % MOD;
		}
	printf( "%d\n", ans );
	return 0;
}
