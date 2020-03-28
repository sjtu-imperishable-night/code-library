#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef long double ldouble;
const int N = 1010;
int _w;

int w, n, px[N], py[N];

bool done[N][2];
ldouble dis[N][2];
pii from[N][2];

struct Node {
	int u, st;
	ldouble d;
	Node() {}
	Node( int uu, int stst, ldouble dd ) {
		u = uu, st = stst, d = dd;
	}
	bool operator<( const Node &rhs ) const {
		return d > rhs.d;
	}
};

priority_queue<Node> pq;

ldouble calc( int u, int v ) {
	if( u > v ) swap(u, v);
	if( u == 0 && v == n+1 ) {
		return w;
	} else if( u == 0 ) {
		return px[v];
	} else if( v == n+1 ) {
		return w - px[u];
	} else {
		int dx = abs(px[u] - px[v]);
		int dy = abs(py[u] - py[v]);
		return sqrt((ldouble)dx * dx + (ldouble)dy * dy);
	}
}

void print_ans( int u, int v ) {
	if( u > v ) swap(u, v);
	if( u == 0 && v == n+1 ) {
		printf( "%.2lf 0.00\n", w/2.0 );
	} else if( u == 0 ) {
		printf( "%.2lf %.2lf\n", px[v]/2.0, (double)py[v] );
	} else if( v == n+1 ) {
		printf( "%.2lf %.2lf\n", (w + px[u])/2.0, (double)py[u] );
	} else {
		printf( "%.2lf %.2lf\n", (px[u] + px[v])/2.0, (py[u] + py[v])/2.0 );
	}
}

void solve() {
	for( int i = 0; i < N; ++i )
		dis[i][0] = dis[i][1] = 1e100;
	dis[0][0] = 0;
	pq.push( Node(0, 0, 0) );
	while( !pq.empty() ) {
		Node o = pq.top(); pq.pop();
		int u = o.u, st = o.st;
		if( done[u][st] ) continue;
		done[u][st] = true;
		for( int i = 0; i <= n+1; ++i ) {
			if( i == u ) continue;
			ldouble len = calc(u, i);
			if( max( dis[u][st], len ) < dis[i][st] ) {
				dis[i][st] = max( dis[u][st], len );
				from[i][st] = pii(u, st);
				pq.push( Node(i, st, dis[i][st]) );
			}
			if( st == 0 ) {
				if( max( dis[u][0], len/2 ) < dis[i][1] ) {
					dis[i][1] = max( dis[u][0], len/2 );
					from[i][1] = pii(u, 0);
					pq.push( Node(i, 1, dis[i][1]) );
				}
			}
		}
	}
	pii now(n+1, 1);
	while(1) {
		pii nxt = from[now.first][now.second];
		if( nxt.second == 0 ) {
			print_ans(now.first, nxt.first);
			return;
		}
		now = nxt;
	}
}

int main() {
	freopen("froggy.in", "r", stdin);
	freopen("froggy.out", "w", stdout);
	_w = scanf( "%d%d", &w, &n );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d%d", px+i, py+i );
	solve();
	return 0;
}
