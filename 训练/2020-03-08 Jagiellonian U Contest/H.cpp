#include <bits/stdc++.h>

using namespace std;
const int N = 200010;
int _w;

int n, s, m, deg[N];

namespace G {
	int head[N], nxt[N*2], to[N*2], eid;
	void init() {
		eid = 0;
		for( int i = 1; i <= n; ++i )
			head[i] = -1;
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
		to[eid] = u, nxt[eid] = head[v], head[v] = eid++;
	}
}

int dep[N], pa[N];
bool mark[N];

void init( int u, int fa, int d ) {
	using namespace G;
	pa[u] = fa, dep[u] = d;
	for( int i = head[u]; ~i; i = nxt[i] ) {
		int v = to[i];
		if( v == fa ) continue;
		init(v, u, d+1);
	}
}

int init_mark() {
	int now = 0;
	for( int u = s; u != m; u = pa[u] ) {
		mark[u] = true;
		++now;
	}
	return now;
}

int nod[N], nn;

bool cmp_dep( int u, int v ) {
	return dep[u] > dep[v];
}

int insert( int u ) {
	int now = 0;
	for( ; !mark[u]; u = pa[u] ) {
		mark[u] = true;
		++now, ++now;
	}
	return now;
}

void solve() {
	int ans = 1e9;
	init(m, 0, 0);
	for( int i = 1; i <= n; ++i )
		mark[i] = false;
	mark[m] = true;
	int now = init_mark();
	nn = 0;
	for( int i = 1; i <= n; ++i )
		if( deg[i] == 1 && i != m && i != s )
			nod[nn++] = i;
	nod[nn++] = 0;
	sort(nod, nod+nn, cmp_dep);
	for( int i = 0; i < nn; ++i ) {
		ans = min( ans, now + dep[nod[i]] );
		now += insert( nod[i] );
	}
	printf( "%d\n", ans );
}

int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		_w = scanf( "%d%d%d", &n, &s, &m );
		G::init();
		for( int i = 1; i <= n; ++i )
			deg[i] = 0;
		for( int i = 0; i < n-1; ++i ) {
			int u, v;
			_w = scanf( "%d%d", &u, &v );
			G::link(u, v);
			++deg[u];
			++deg[v];
		}
		solve();
	}
	return 0;
}
