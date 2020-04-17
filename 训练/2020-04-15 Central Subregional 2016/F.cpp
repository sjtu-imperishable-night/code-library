#include <bits/stdc++.h>

using namespace std;
const int N = 1010;
int _w;

int n, m;
int pu[N];
char rela[N];
int pv[N];

namespace DSU {
	int pa[N];
	
	void init() {
		for( int i = 0; i < N; ++i )
			pa[i] = i;
	}
	int find( int u ) {
		return pa[u] == u ? u : pa[u] = find( pa[u] );
	}
	void link( int u, int v ) {
		pa[find(u)] = find(v);
	}
}

namespace G {
	int head[N], nxt[N*N], to[N*N], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
	}
}

namespace R {
	int head[N], nxt[N*N], to[N*N], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
	}
}

char ans[N];

int checkg( int s ) {
	using namespace G;
	if( head[s] == -1 ) return 0;
	for( int i = head[s]; ~i; i = nxt[i] ) {
		int v = to[i];
		// printf( "s = %d, v = %d\n", s, v );
		if( head[v] != -1 ) return 2;
	}
	return 1;
}

int checkr( int s ) {
	using namespace R;
	if( head[s] == -1 ) return 0;
	for( int i = head[s]; ~i; i = nxt[i] ) {
		int v = to[i];
		if( head[v] != -1 ) return 2;
	}
	return 1;
}

int main() {
	_w = scanf( "%d%d", &n, &m );
	for( int i = 1; i <= m; ++i )
		_w = scanf( "%d%c%d", pu+i, rela+i, pv+i );
	DSU::init();
	for( int i = 1; i <= m; ++i )
		if( rela[i] == '=' )
			DSU::link( pu[i], pv[i] );
	for( int i = 1; i <= n; ++i ) {
		pu[i] = DSU::find( pu[i] );
		pv[i] = DSU::find( pv[i] );
	}
	G::init();
	R::init();
	for( int i = 1; i <= m; ++i )
		if( rela[i] == '<' ) {
			G::link( pu[i], pv[i] );
			R::link( pv[i], pu[i] );
		} else if( rela[i] == '>' ) {
			G::link( pv[i], pu[i] );
			R::link( pu[i], pv[i] );
		}
	for( int i = 1; i <= n; ++i )
		ans[i] = '?';
	for( int i = 1; i <= n; ++i ) {
		int g = checkg(i);
		int r = checkr(i);
		// printf( "g = %d, r = %d\n", g, r );
		if( g == 2 ) {
			ans[i] = 'B';
		} else if( g == 1 && r == 1 ) {
			ans[i] = 'R';
		} else if( r == 2 ) {
			ans[i] = 'W';
		}
	}
	for( int i = 1; i <= n; ++i )
		ans[i] = ans[DSU::find(i)];
	ans[n+1] = 0;
	puts(ans+1);
	return 0;
}
