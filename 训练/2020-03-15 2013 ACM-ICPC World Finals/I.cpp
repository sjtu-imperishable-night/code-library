#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 510;
int _w;

int a, b, n, m, d[N][N];
ll ans;

int h[N];
int lc[N], rc[N], lb[N], rb[N], stk[N], top, rt;

void build() {
	top = 0;
	memset(lc, 0, sizeof lc);
	memset(rc, 0, sizeof rc);
	stk[top++] = 1;
	for( int i = 2; i <= m; ++i ) {
		while( top && h[i] < h[stk[top-1]] ) {
			lc[i] = stk[top-1];
			--top;
		}
		if( top ) rc[stk[top-1]] = i;
		stk[top++] = i;
	}
	rt = stk[0];
}

void update( int x, int y, int dep ) {
	// printf( "update(%d, %d, %d)\n", x, y, dep );
	int area = x * y;
	int pond = n * m;
	ll height = 1LL * dep * pond / (pond - area);
	if( 1LL * dep * pond % (pond - area) == 0 )
		--height;
	ans = max( ans, height * area );
}

void dfs( int u, int len ) {
	lb[u] = rb[u] = u;
	if( lc[u] ) {
		dfs( lc[u], len );
		lb[u] = lb[lc[u]];
	}
	if( rc[u] ) {
		dfs( rc[u], len );
		rb[u] = rb[rc[u]];
	}
	int width = rb[u] - lb[u] + 1;
	if( len <= a ) width = min(width, b);
	else width = min(width, a);
	int dep = h[u];
	update(len, width, dep);
}

void _solve( int len ) {
	build();
	dfs(rt, len);
}

void solve() {
	for( int up = 1; up <= n; ++up ) {
		for( int j = 1; j <= m; ++j )
			h[j] = d[up][j];
		for( int down = up; down <= n; ++down ) {
			int len = down - up + 1;
			if( len > b ) break;
			for( int j = 1; j <= m; ++j ) {
				h[j] = min( h[j], d[down][j] );
			}
			_solve(len);
		}
	}
}

int main() {
	_w = scanf( "%d%d%d%d", &a, &b, &n, &m );
	if( a > b ) swap(a, b);
	for( int i = 1; i <= n; ++i )
		for( int j = 1; j <= m; ++j )
			_w = scanf( "%d", &d[i][j] );
	solve();
	printf( "%lld\n", ans );
	return 0;
}
