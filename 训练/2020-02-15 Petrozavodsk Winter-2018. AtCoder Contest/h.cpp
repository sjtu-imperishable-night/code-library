#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int N = 2010;
int _w;

int n, pa[N], a[N];
vector<int> ans;

namespace G {
	int head[N], nxt[N], to[N], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
	}
}

namespace HLD {
	int sz[N], son[N], top[N], depth[N];
	
	void dfs1( int u, int d ) {
		using namespace G;
		sz[u] = 1, depth[u] = d;
		for( int i = head[u]; ~i; i = nxt[i] ) {
			int v = to[i];
			dfs1(v, d+1);
			sz[u] += sz[v];
			if( son[u] == -1 || sz[v] > sz[son[u]] )
				son[u] = v;
		}
	}
	void dfs2( int u, int tp ) {
		using namespace G;
		top[u] = tp;
		if( son[u] != -1 ) dfs2( son[u], tp );
		for( int i = head[u]; ~i; i = nxt[i] ) {
			int v = to[i];
			if( v == son[u] ) continue;
			dfs2(v, v);
		}
	}
	void init() {
		memset(son, -1, sizeof son);
		dfs1(0, 1);
		dfs2(0, 0);
	}
}
using HLD::son;
using HLD::top;
using HLD::depth;

namespace HLDT {
	int head[N], nxt[N], to[N], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
	}
}

vector<int> chain[N];
int maxd;

void init_chain( int u, int dep ) {
	using namespace HLDT;
	maxd = max( maxd, dep );
	chain[dep].push_back(u);
	for( int i = head[u]; ~i; i = nxt[i] ) {
		int v = to[i];
		init_chain(v, dep+1);
	}
}

bool trash[N], need[N];
vector<int> nod[N];
int finish[N], fucked[N];

void load_chain( int tp ) {
	for( int u = tp; u != -1; u = son[u] )
		nod[tp].push_back(u);
}

bool check( int dep ) {
	for( int tp : chain[dep] )
		if( (int)nod[tp].size() != finish[tp] )
			return false;
	/*
	printf( "dep = %d\n", dep );
	for( int i = 0; i < n; ++i )
		printf( "a[%d] = %d\n", i, a[i] );
	*/
	for( int tp : chain[dep] )
		for( int u = tp; u != -1; u = son[u] )
			assert( a[u] == u );
	return true;
}

int find_trash( int dep ) {
	int u = -1, mxd = -1;
	for( int i = 0; i < n; ++i )
		if( trash[i] && depth[i] > mxd )
			u = i, mxd = depth[i];
	for( int tp : chain[dep] ) {
		if( fucked[tp] >= (int)nod[tp].size() )
			continue;
		int now = nod[tp][(int)nod[tp].size() - fucked[tp] - 1];
		if( depth[now] > mxd )
			u = now, mxd = depth[now];
	}
	return u;
}

void op( int u, int dep ) {
	ans.push_back(u);
	vector<pii> tmp;
	for( int now = u; now != -1; now = pa[now] )
		tmp.push_back( pii(now, a[now]) );
	int rt_val = a[0];
	for( int i = (int)tmp.size()-1; i >= 1; --i ) {
		int now = tmp[i].first;
		int last = tmp[i-1].first;
		a[now] = a[last];
	}
	a[u] = rt_val;
	if( trash[u] ) {
		trash[u] = false;
	} else {
		assert( need[u] );
		for( int tp : chain[dep] )
			for( int now : nod[tp] )
				if( now == u ) {
					++fucked[tp];
					break;
				}
	}
	/*
	printf( "op(%d)\n", u );
	for( int i = 0; i < n; ++i )
		printf( "a[%d] = %d\n", i, a[i] );
	*/
}

int id[N];

void home_helper( int tp, int u, int dep ) {
	for( int i = 0; i < (int)nod[tp].size(); ++i )
		id[nod[tp][i]] = i;
	for( int i = (int)nod[tp].size() - 1; i >= (int)nod[tp].size() - finish[tp]; --i ) {
		int vertex = nod[tp][i];
		int num = a[vertex];
		if( id[u] > id[num] ) {
			op(vertex, dep);
			++finish[tp];
			return;
		}
	}
	op( nod[tp][(int)nod[tp].size() - finish[tp] - 1], dep );
	++finish[tp];
}

void home( int u, int dep ) {
	for( int tp : chain[dep] )
		for( int now : nod[tp] )
			if( now == u ) {
				home_helper(tp, u, dep);
				return;
			}
}

void solve_chain( int dep ) {
	for( int tp : chain[dep] )
		load_chain(tp);
	
	memset(trash, false, sizeof trash);
	for( int i = 0; i < dep; ++i )
		for( int tp : chain[i] )
			for( int u = tp; u != -1; u = son[u] )
				trash[u] = true;
	
	memset(need, false, sizeof need);
	for( int tp : chain[dep] )
		for( int u = tp; u != -1; u = son[u] )
			need[u] = true;
	
	while( !check(dep) ) {
		int num = a[0];
		if( need[num] ) {
			home(num, dep);
		} else {
			int u = find_trash(dep);
			op(u, dep);
		}
	}
}

void solve() {
	HLD::init();
	HLDT::init();
	for( int i = 1; i < n; ++i ) {
		using namespace HLD;
		if( i == top[i] ) {
			HLDT::link( top[pa[i]], i );
		}
	}
	init_chain(0, 0), ++maxd;
	for( int i = maxd-1; i >= 0; --i )
		solve_chain(i);
}

int main() {
	_w = scanf( "%d", &n );
	G::init();
	for( int i = 1; i < n; ++i ) {
		_w = scanf( "%d", pa+i );
		G::link( pa[i], i );
	}
	pa[0] = -1;
	for( int i = 0; i < n; ++i )
		_w = scanf( "%d", a+i );
	solve();
	printf( "%d\n", (int)ans.size() );
	for( int x : ans )
		printf( "%d\n", x );
	return 0;
}
