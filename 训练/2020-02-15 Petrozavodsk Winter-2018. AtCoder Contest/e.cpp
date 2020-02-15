#include <bits/stdc++.h>

using namespace std;
const int N = 100010;
const int K = 16;
int _w;

int n, a[N], cnt[K];

namespace G {
	int head[N], nxt[N*2], to[N*2], val[N*2], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v, int w ) {
		to[eid] = v, val[eid] = w, nxt[eid] = head[u], head[u] = eid++;
		to[eid] = u, val[eid] = w, nxt[eid] = head[v], head[v] = eid++;
	}
}

int f[1<<K], sum[1<<K];

void init_sum() {
	for( int s = 0; s < (1<<K); ++s ) {
		for( int i = 0; i < K; ++i )
			if( s & (1<<i) )
				sum[s] ^= i;
	}
}

void solve() {
	int ans = 0;
	cnt[0] = 0;
	for( int i = 1; i < K; ++i ) {
		ans += cnt[i] / 2;
		cnt[i] &= 1;
	}
	memset(f, 0x3f, sizeof f);
	int begin = 0;
	for( int i = 0; i < K; ++i )
		if( cnt[i] ) {
			// printf( "cnt[%d] = 1\n", i );
			begin |= 1<<i;
		}
	f[begin] = 0;
	init_sum();
	for( int s = begin; s; --s ) {
		for( int t = s; t; t = (t-1) & s ) {
			if( sum[t] == 0 ) {
				f[s^t] = min( f[s^t], f[s] + __builtin_popcount(t) - 1 );
			}
		}
	}
	ans += f[0];
	printf( "%d\n", ans );
}

int main() {
	_w = scanf( "%d", &n );
	G::init();
	for( int i = 0; i < n-1; ++i ) {
		int u, v, w;
		_w = scanf( "%d%d%d", &u, &v, &w );
		G::link(u, v, w);
	}
	for( int i = 0; i < n; ++i ) {
		using namespace G;
		for( int e = head[i]; ~e; e = nxt[e] ) {
			a[i] ^= val[e];
		}
		++cnt[a[i]];
		// printf( "a[%d] = %d\n", i, a[i] );
	}
	solve();
	return 0;
}
