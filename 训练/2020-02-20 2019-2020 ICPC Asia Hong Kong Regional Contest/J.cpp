#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 5010;
const int M = 62;
const int MOD = 1e9+7;
int _w;

void add_mod( int &a, int b ) {
	a += b;
	a -= a >= MOD ? MOD : 0;
}

void sub_mod( int &a, int b ) {
	a -= b;
	a += a < 0 ? MOD : 0;
}

int n, m;
int num[N];

void read_num( char *str ) {
	n = (int)strlen(str+1);
	for( int i = 1; i <= n; ++i )
		num[i] = str[i] - '0';
}

int pw[N];

void init_pw() {
	pw[0] = 1;
	for( int i = 1; i <= n; ++i )
		pw[i] = pw[i-1] * 10 % m;
}

int f[N][M][M][2];

void solve() {
	for( int i = 1; i <= n+1; ++i )
		for( int j = 0; j < m; ++j )
			for( int k = 0; k < m; ++k )
				f[i][j][k][0] = f[i][j][k][1] = 0;
	f[1][0][0][1] = 1;
	for( int i = 1; i <= n; ++i ) {
		for( int j = 0; j < m; ++j ) {
			for( int k = 0; k < m; ++k ) {
				for( int up = 0; up < 2; ++up ) {
					// printf( "f[%d][%d][%d][%d] = %d\n", i, j, k, up, f[i][j][k][up] );
					if( f[i][j][k][up] ) {
						const int &now = f[i][j][k][up];
						for( int d = 0; d < 10; ++d ) {
							if( up && d > num[i] ) break;
							int ni = i + 1;
							int nj = (j + d) % m;
							int nk = (k + j * d) % m;
							nk = (nk - d * pw[n-i] % m + m) % m;
							int nup = up && d == num[i];
							add_mod( f[ni][nj][nk][nup], now );
						}
					}
				}
			}
		}
	}
}

int solve_L() {
	solve();
	int ans = 0;
	for( int j = 0; j < m; ++j )
		add_mod( ans, f[n+1][j][0][0] );
	// printf( "solve_L = %d\n", ans );
	return ans;
}

int solve_R() {
	solve();
	int ans = 0;
	for( int j = 0; j < m; ++j ) {
		add_mod( ans, f[n+1][j][0][0] );
		add_mod( ans, f[n+1][j][0][1] );
	}
	// printf( "solve_R = %d\n", ans );
	return ans;
}

char str_L[N], str_R[N];

int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		_w = scanf( "%s", str_L+1 );
		_w = scanf( "%s", str_R+1 );
		_w = scanf( "%d", &m );
		
		int ans = 0;
		read_num( str_L );
		init_pw();
		sub_mod( ans, solve_L() );
		read_num( str_R );
		init_pw();
		add_mod( ans, solve_R() );
		printf( "%d\n", ans );
	}
	return 0;
}
