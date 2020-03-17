#include <bits/stdc++.h>

using namespace std;
const int N = 75;
int _w;

int n;
bitset<N> g[N], all;

int ans[N], an;
int depth;

bool dfs( int dep, bitset<N> now, int last ) {
	if( dep == depth ) {
		if( now == all ) {
			return true;
		} else {
			return false;
		}
	} else {
		for( int i = last+1; i < n; ++i ) {
			ans[an++] = i;
			if( dfs(dep+1, now | g[i], i) )
				return true;
			--an;
		}
		return false;
	}
}

void solve() {
	an = 0;
	for( depth = 1; depth <= 6; ++depth ) {
		if( dfs(0, bitset<N>(), -1) ) break;
		if( depth == 6 ) assert(0);
	}
	printf( " %d", an );
	for( int i = 0; i < an; ++i )
		printf( " %d", ans[i]+1 );
	puts("");
}

int main() {
	int kase = 0;
	while( scanf( "%d", &n ) != -1 ) {
		for( int i = 0; i < n; ++i ) {
			g[i].reset();
			char tmp[N+1];
			_w = scanf( "%s", tmp );
			for( int j = 0; j < n; ++j )
				g[i].set(j, tmp[j] - '0');
			g[i].set(i, 1);
		}
		all.reset();
		for( int i = 0; i < n; ++i )
			all.set(i, 1);
		printf( "Case %d:", ++kase );
		solve();
	}
	return 0;
}
