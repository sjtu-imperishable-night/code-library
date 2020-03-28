#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 100010;
const int M = 200010;
int _w;

int n, c[N];
vector<int> adj[N];

namespace G {
	int head[N], nxt[M*20], to[M*20], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
	}
}

namespace DSU {
	int pa[N];
	
	void init() {
		for( int i = 1; i <= n; ++i )
			pa[i] = i;
	}
	int find( int u ) {
		return pa[u] == u ? u : pa[u] = find( pa[u] );
	}
	void link( int u, int v ) {
		pa[find(u)] = find(v);
	}
}

bool cmpc( int i, int j ) {
	return c[i] < c[j];
}

int in[N], salary[N];
queue<int> q;

void toposort() {
	for( int i = 1; i <= n; ++i ) {
		using namespace G;
		for( int e = head[i]; ~e; e = nxt[e] ) {
			int v = to[e];
			++in[v];
		}
	}
	for( int i = 1; i <= n; ++i )
		if( in[i] == 0 ) {
			q.push(i);
			salary[i] = 1;
		}
	while( !q.empty() ) {
		int u = q.front(); q.pop();
		using namespace G;
		for( int i = head[u]; ~i; i = nxt[i] ) {
			int v = to[i];
			salary[v] = max( salary[v], salary[u] + 1 );
			--in[v];
			if( in[v] == 0 )
				q.push(v);
		}
	}
}

void solve() {
	DSU::init();
	for( int u = 1; u <= n; ++u ) {
		adj[u].push_back(u);
		sort( adj[u].begin(), adj[u].end(), cmpc );
		for( int i = 1; i < (int)adj[u].size(); ++i ) {
			int now = adj[u][i];
			int pre = adj[u][i-1];
			if( c[now] == c[pre] )
				DSU::link(now, pre);
		}
	}
	G::init();
	for( int u = 1; u <= n; ++u ) {
		for( int i = 1; i < (int)adj[u].size(); ++i ) {
			int now = DSU::find( adj[u][i] );
			int pre = DSU::find( adj[u][i-1] );
			if( now != pre )
				G::link(pre, now);
		}
	}
	toposort();
	ll sum = 0;
	for( int i = 1; i <= n; ++i )
		sum += salary[DSU::find(i)];
	cout << sum << endl;
}

int main() {
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d", c+i );
	int m;
	_w = scanf( "%d", &m );
	for( int i = 0; i < m; ++i ) {
		int u, v;
		_w = scanf( "%d%d", &u, &v );
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	solve();
	return 0;
}
