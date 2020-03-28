#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e6+10;
const int LOGN = 21;
int _w;

int read() {
	int x = 0, ch;
	while( isspace(ch = getchar()) );
	do x = x * 10 + ch - '0';
	while( isdigit(ch = getchar()) );
	return x;
}

int n, k, a[N], b[N];
ll f[N][LOGN];
int rightmost[N*2];

void prelude() {
	for( int i = 1; i <= k; ++i ) {
		if( a[i] <= b[i] ) {
			rightmost[a[i]] = max( rightmost[a[i]], b[i] );
		} else {
			b[i] += n;
			rightmost[a[i]] = max( rightmost[a[i]], b[i] );
		}
	}
	for( int i = 2; i <= n+n; ++i )
		rightmost[i] = max( rightmost[i-1], rightmost[i] );
	for( int i = 1; i <= n; ++i ) {
		f[i][0] = max<ll>( f[i][0], rightmost[i] - i + 1 );
		f[i][0] = max<ll>( f[i][0], rightmost[i+n] - (i+n) + 1 );
		if( !f[i][0] ) {
			puts("impossible");
			exit(0);
		}
	}
	for( int i = 0; i < LOGN-1; ++i )
		for( int j = 1; j <= n; ++j ) {
			int jj = (j - 1 + f[j][i]) % n + 1;
			f[j][i+1] = f[j][i] + f[jj][i];
		}
}

void solve() {
	prelude();
	int ans = 1e9;
	for( int s = 1; s <= n; ++s ) {
		int dis = 0, cnt = 0, u = s;
		for( int i = LOGN-1; i >= 0; --i ) {
			if( dis + f[u][i] < n ) {
				dis += f[u][i];
				cnt += 1<<i;
				u = (u - 1 + f[u][i]) % n + 1;
			}
		}
		ans = min( ans, cnt+1 );
	}
	printf( "%d\n", ans );
}

int main() {
	n = read(), k = read();
	for( int i = 1; i <= k; ++i )
		a[i] = read(), b[i] = read();
	solve();
	return 0;
}
