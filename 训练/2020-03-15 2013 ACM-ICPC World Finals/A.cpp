#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int N = 50010;
int _w;

set<pii> edge_set;

namespace G {
	int head[N], nxt[N*20], to[N*20], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		if( edge_set.count( pii(u, v) ) ) return;
		edge_set.insert( pii(u, v) );
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
	}
}

int n;
int posi[26], nega[26], nid = 0, indeg[N];
queue<int> q;

bool cycle() {
	using namespace G;
	for( pii e : edge_set )
		++indeg[e.second];
	for( int i = 1; i <= nid; ++i )
		if( indeg[i] == 0 )
			q.push(i);
	while( !q.empty() ) {
		int u = q.front(); q.pop();
		for( int i = head[u]; ~i; i = nxt[i] ) {
			int v = to[i];
			--indeg[v];
			if( indeg[v] == 0 )
				q.push(v);
		}
	}
	for( int i = 1; i <= nid; ++i )
		if( indeg[i] )
			return true;
	return false;
}

int main() {
	G::init();
	for( int i = 0; i < 26; ++i )
		posi[i] = ++nid;
	for( int i = 0; i < 26; ++i )
		nega[i] = ++nid;
	
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i ) {
		char tmp[20];
		_w = scanf( "%s", tmp );
		for( int j = 0; j < 8; j += 2 ) {
			for( int k = 0; k < 8; k += 2 ) {
				if( j == k ) continue;
				if( tmp[j] == '0' ) continue;
				if( tmp[k] == '0' ) continue;
				int chj = tmp[j] - 'A';
				int chk = tmp[k] - 'A';
				int *aj = tmp[j+1] == '+' ? nega : posi;
				int *ak = tmp[k+1] == '+' ? posi : nega;
				G::link( aj[chj], ak[chk] );
			}
		}
	}
	
	puts( cycle() ? "unbounded" : "bounded" );
	return 0;
}
