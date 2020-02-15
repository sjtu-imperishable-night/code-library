#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 100010;
int _w;

int n, m, a[N];

namespace G {
	int head[N], nxt[N*2], to[N*2], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
		to[eid] = u, nxt[eid] = head[v], head[v] = eid++;
	}
}

ll ans = 0;
bool vis[N];
priority_queue<int, vector<int>, greater<int> > pq;

void bfs( int s ) {
	using namespace G;
	
	queue<int> q;
	vector<pii> tmp;
	
	vis[s] = true, q.push(s);
	while( !q.empty() ) {
		int u = q.front(); q.pop();
		tmp.push_back( pii( a[u], u ) );
		for( int i = head[u]; ~i; i = nxt[i] ) {
			int v = to[i];
			if( !vis[v] ) {
				vis[v] = true, q.push(v);
			}
		}
	}
	sort( tmp.begin(), tmp.end() );
	ans += tmp[0].first;
	for( int i = 1; i < (int)tmp.size(); ++i )
		pq.push( tmp[i].first );
}

void solve() {
	int cnt = 0;
	for( int i = 0; i < n; ++i )
		if( !vis[i] ) {
			bfs(i);
			++cnt;
		}
	if( cnt == 1 ) {
		puts("0");
	} else {
		for( int i = 0; i < cnt-2; ++i ) {
			if( pq.empty() ) {
				puts("Impossible");
				return;
			}
			ans += pq.top(), pq.pop();
		}
		printf( "%lld\n", ans );
	}
}

int main() {
	_w = scanf( "%d%d", &n, &m );
	for( int i = 0; i < n; ++i )
		_w = scanf( "%d", a+i );
	G::init();
	for( int i = 0; i < m; ++i ) {
		int u, v;
		_w = scanf( "%d%d", &u, &v );
		G::link(u, v);
	}
	solve();
	return 0;
}
