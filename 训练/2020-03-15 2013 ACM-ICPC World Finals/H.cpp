#include <bits/stdc++.h>

using namespace std;
const int N = 510;
const int INF = 0x3f3f3f3f;
int _w;

int n, a[N], fuck[N][N];

int diff[N][N], cons[N][N], cnt[N], minv[N][N];

void prelude() {
	for( int l = 1; l <= n; ++l )
		for( int r = l; r <= n; ++r ) {
			for( int i = l; i <= r; ++i )
				++cnt[a[i]];
			
			diff[l][r] = true;
			for( int i = 1; i <= 500; ++i )
				if( cnt[i] >= 2 )
					diff[l][r] = false;
			
			minv[l][r] = a[l];
			for( int i = l; i <= r; ++i )
				minv[l][r] = min( minv[l][r], a[i] );
			
			cons[l][r] = 1;
			while( cnt[minv[l][r] + cons[l][r]] )
				++cons[l][r];
			
			for( int i = l; i <= r; ++i )
				--cnt[a[i]];
		}
	for( int i = 1; i <= n; ++i )
		fuck[i][a[i]] = 1;
	for( int i = 1; i <= n; ++i )
		for( int j = 1; j <= 500; ++j )
			fuck[i][j] += fuck[i-1][j];
	for( int i = 1; i <= n; ++i )
		for( int j = 1; j <= 500; ++j )
			fuck[i][j] += fuck[i][j-1];
}

int dp[N][N];

int calc( int l1, int r1, int l2, int r2 ) {
	int tot_cnt = r2 - l2 + 1 + r1 - l1 + 1;
	if( minv[l1][r1] < minv[l2][r2] ) {
		int tmp = minv[l2][r2];
		tot_cnt -= fuck[r1][tmp] - fuck[l1-1][tmp];
	} else {
		int tmp = minv[l1][r1];
		tot_cnt -= fuck[r2][tmp] - fuck[l2-1][tmp];
	}
	return tot_cnt;
}

int DP( int l, int r ) {
	int &now = dp[l][r];
	if( now != -1 ) return now;
	if( l == r ) return int(now = 0);
	now = INF;
	for( int mid = l; mid < r; ++mid ) {
		now = min( now, DP(l, mid) + DP(mid+1, r) + calc(l, mid, mid+1, r) );
	}
	return now;
}

int f[N];

void solve() {
	memset(f, 0x3f, sizeof f);
	memset(dp, -1, sizeof dp);
	f[0] = 0;
	for( int i = 1; i <= n; ++i ) {
		for( int j = 1; j <= i; ++j ) {
			if( diff[j][i] && minv[j][i] == 1 && cons[j][i] == (i-j+1) ) {
				f[i] = min( f[i], f[j-1] + DP(j, i) );
				// printf( "f[%d] = %d\n", i, f[i] );
			}
		}
	}
	if( f[n] == INF ) puts("impossible");
	else printf( "%d\n", f[n] );
}

int main() {
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d", a+i );
	prelude();
	solve();
	return 0;
}
