#include <bits/stdc++.h>

using namespace std;
const int N = 10010;
const int M = 500010;
int _w;

int n, A, B, C, belong[N];
vector<int> va, vb, vc;

namespace G {
	int head[N], nxt[M*2], to[M*2], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
		to[eid] = u, nxt[eid] = head[v], head[v] = eid++;
	}
}

namespace Steiner {
	const int INF = 0x3f3f3f3f;

	struct Node {
		int u, d;
		Node() {}
		Node( int uu, int dd ) {
			u = uu, d = dd;
		}
		bool operator<( const Node &rhs ) const {
			return d > rhs.d;
		}
	};
	
	int f[N][8];
	priority_queue<Node> pq;
	bool done[N];
	
	void spfa( int s ) {
		using namespace G;
		for( int i = 1; i <= n+3; ++i )
			if( f[i][s] != INF )
				pq.push( Node(i, f[i][s]) );
		memset(done, false, sizeof done);
		while( !pq.empty() ) {
			Node o = pq.top(); pq.pop();
			int u = o.u;
			if( done[u] ) continue;
			done[u] = true;
			for( int i = head[u]; ~i; i = nxt[i] ) {
				int v = to[i];
				if( f[u][s] + 1 < f[v][s] ) {
					f[v][s] = f[u][s] + 1;
					pq.push( Node(v, f[v][s]) );
				}
			}
		}
	}
	
	void solve() {
		for( int s = 0; s < (1<<3); ++s ) {
			for( int i = 1; i <= n+3; ++i )
				for( int t = s; t; t = (t-1)&s )
					f[i][s] = min( f[i][s], f[i][t] + f[i][s^t] );
			spfa(s);
		}
	}
}

void solve() {
	using Steiner::f;
	using Steiner::INF;
	memset(f, 0x3f, sizeof f);
	for( int i = 1; i <= n+3; ++i )
		f[i][0] = 0;
	f[n+1][1] = 0;
	f[n+2][2] = 0;
	f[n+3][4] = 0;
	Steiner::solve();
	int ans = INF;
	for( int i = 1; i <= n+3; ++i )
		ans = min( ans, f[i][7] );
	int nod = INF;
	for( int i = 1; i <= n+3; ++i )
		if( f[i][7] == ans ) {
			nod = min( nod, i );
			if( i == n+1 ) {
				nod = min( nod, *min_element(va.begin(), va.end()) );
			} else if( i == n+2 ) {
				nod = min( nod, *min_element(vb.begin(), vb.end()) );
			} else if( i == n+3 ) {
				nod = min( nod, *min_element(vc.begin(), vc.end()) );
			}
		}
	printf( "%d %d\n", ans, nod );
}

int main() {
	_w = scanf( "%d%d%d%d", &n, &A, &B, &C );
	for( int i = 0; i < A; ++i ) {
		int x;
		_w = scanf( "%d", &x );
		va.push_back(x);
		belong[x] = 1;
	}
	for( int i = 0; i < B; ++i ) {
		int x;
		_w = scanf( "%d", &x );
		vb.push_back(x);
		belong[x] = 2;
	}
	for( int i = 0; i < C; ++i ) {
		int x;
		_w = scanf( "%d", &x );
		vc.push_back(x);
		belong[x] = 3;
	}
	int m;
	_w = scanf( "%d", &m );
	G::init();
	while( m-- ) {
		int u, v;
		_w = scanf( "%d%d", &u, &v );
		if( belong[u] ) u = n + belong[u];
		if( belong[v] ) v = n + belong[v];
		G::link(u, v);
	}
	solve();
	return 0;
}
