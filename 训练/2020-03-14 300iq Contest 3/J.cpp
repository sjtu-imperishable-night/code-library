#include <bits/stdc++.h>

using namespace std;
const int N = 300010;
const int MOD = 998244353;
typedef long long ll;
int _w;

int fpow( int a, int b ) {
	int c = 1;
	while(b) {
		if( b & 1 ) c = int(1LL * c * a % MOD);
		a = int(1LL * a * a % MOD);
		b >>= 1;
	}
	return c;
}

int n, m;

namespace G {
	int head[N], nxt[N*2], to[N*2], eid;
	void init() {
		for( int i = 1; i <= n; ++i )
			head[i] = -1;
		eid = 0;
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
		to[eid] = u, nxt[eid] = head[v], head[v] = eid++;
	}
}

bool vis[N];
int color[N];
queue<int> q;

ll solve( int s ) {
	using namespace G;
	int cnt_nod = 0;
	int cnt_edge = 0;
	bool bipartite = true;
	vis[s] = true, color[s] = 0, q.push(s), ++cnt_nod;
	while( !q.empty() ) {
		int u = q.front(); q.pop();
		for( int i = head[u]; ~i; i = nxt[i] ) {
			int v = to[i];
			++cnt_edge;
			if( !vis[v] ) {
				vis[v] = true, color[v] = color[u] ^ 1, q.push(v), ++cnt_nod;
			} else {
				if( color[u] == color[v] )
					bipartite = false;
			}
		}
	}
	cnt_edge /= 2;
	return fpow(5, cnt_edge - cnt_nod + bipartite);
}

void solve() {
	for( int i = 1; i <= n; ++i ) {
		vis[i] = false;
		color[i] = -1;
	}
	ll ans = 1;
	for( int i = 1; i <= n; ++i )
		if( !vis[i] ) {
			ans = ans * solve(i) % MOD;
		}
	printf( "%lld\n", ans );
}

int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		_w = scanf( "%d%d", &n, &m );
		G::init();
		for( int i = 0; i < m; ++i ) {
			int u, v;
			_w = scanf( "%d%d", &u, &v );
			G::link(u, v);
		}
		solve();
	}
	return 0;
}
