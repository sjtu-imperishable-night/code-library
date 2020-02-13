#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int N = 100010;
const int M = 200010;
int _w;

int n, m;

namespace G {
	int head[N], nxt[M], to[M], id[M], del[M], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v, int w ) {
		to[eid] = v, nxt[eid] = head[u], id[eid] = w, head[u] = eid++;
	}
}

int from[N];
pii first[N], second[N];
bool stk[N];

void inf_exit() {
	puts("Infinite");
	exit(0);
}

void dfs( int u, int e ) {
	using namespace G;
	stk[u] = true;
	for( int i = head[u]; ~i; i = nxt[i] ) {
		int v = to[i], w = id[i], ban = del[i];
		if( w == e ) continue;
		if( stk[v] ) inf_exit();
		if( ban ) continue;
		del[i] = true;
		if( from[v] == -1 || from[v] == w ) {
			;
		} else {
			dfs(v, w);
			if( from[v] == 0 ) from[v] = w;
			else from[v] = -1;
		}
		int len = 0;
		if( first[v].second != w )
			len = max( len, first[v].first + 1 );
		if( second[v].second != w )
			len = max( len, second[v].first + 1 );
		if( len > first[u].first ) {
			second[u] = first[u];
			first[u] = pii(len, w);
		} else if( len > second[u].first ) {
			second[u] = pii(len, w);
		}
	}
	stk[u] = false;
}

int main() {
	_w = scanf( "%d%d", &n, &m );
	G::init();
	for( int i = 1; i <= m; ++i ) {
		int u, v, type;
		_w = scanf( "%d%d%d", &u, &v, &type );
		if( type == 1 ) {
			G::link(u, v, i);
		} else {
			G::link(u, v, i);
			G::link(v, u, i);
		}
	}
	int ans = 0;
	for( int i = 1; i <= n; ++i ) {
		if( from[i] == -1 ) continue;
		dfs(i, 0);
		from[i] = -1;
		ans = max( ans, first[i].first );
	}
	printf( "%d\n", ans );
	return 0;
}
