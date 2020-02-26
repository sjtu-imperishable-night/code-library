#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000010;
int _w;

struct Graph {
	int head[N], nxt[N*2], to[N*2], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
		to[eid] = u, nxt[eid] = head[v], head[v] = eid++;
	}
};

int n, m;
Graph origin, cjk;
bool cyc[N], stk[N], vis[N];
int pa[N], sz[N], cyc_cnt;

void build_cjk( int u, int fa ) {
	
	sz[u] = 1, pa[u] = fa, stk[u] = vis[u] = true;
	
	for( int i = origin.head[u]; ~i; i = origin.nxt[i] ) {
		int v = origin.to[i];
		if( v == fa ) continue;
		if( stk[v] ) {
			
			++cyc_cnt;
			for( int o = u; o != v; o = pa[o] ) {
				cyc[o] = true;
				cjk.link( n + cyc_cnt, o );
			}
			cjk.link( n + cyc_cnt, v );
			
		} else if( !vis[v] ) {
			build_cjk(v, u);
			sz[u] += sz[v];
		}
	}
	
	stk[u] = false;
}

void dfs_sz( int u, int fa ) {
	
	sz[u] = u <= n, pa[u] = fa;

	for( int i = cjk.head[u]; ~i; i = cjk.nxt[i] ) {
		int v = cjk.to[i];
		if( v == fa ) continue;
		dfs_sz(v, u);
		sz[u] += sz[v];
	}
}

int calc_sz( int nod, int center ) {
	if( pa[nod] == center ) {
		return sz[nod];
	} else {
		assert( pa[center] == nod );
		return n - sz[center];
	}
}

ll ans = 0;

void solve_cyc( int u ) {
	vector<int> vec, pf;
	
	u += n;
	for( int i = cjk.head[u]; ~i; i = cjk.nxt[i] ) {
		int v = cjk.to[i];
		vec.push_back( calc_sz(v, u) );
	}
	
	int len = (int)vec.size();
	for( int i = 0; i < len; ++i )
		vec.push_back( vec[i] );
	for( int i = 0; i < len; ++i )
		vec.push_back( vec[i] );
	
	for( int i = 0; i < len+len+len; ++i ) {
		if( i == 0 ) pf.push_back( vec[i] );
		else pf.push_back( pf.back() + vec[i] );
	}
	
	int range = len/2;
	ll now = 0;
	for( int i = 0; i < range; ++i ) {
		int begin = len - i;
		int mid = len + 1;
		int end = begin + range;
		now += 1LL * vec[begin] * (pf[end] - pf[mid-1]);
	}
	// printf( "now = %lld\n", now );
	for( int i = len; i < len+len; ++i ) {
		ans += now;
		now -= 1LL * vec[i+1] * (pf[i] - pf[i-range]);
		now += 1LL * vec[i+1] * (pf[i+1+range] - pf[i+1]);
		// printf( "now = %lld\n", now );
	}
	
	if( len % 2 == 0 ) {
		for( int i = len; i < len + len/2; ++i ) {
			ans -= 1LL * vec[i] * vec[i+len/2] * range;
		}
	}
}

void solve() {
	cyc_cnt = 0;
	cjk.init();
	build_cjk(1, 0);
	for( int i = 2; i <= n; ++i )
		if( !cyc[i] ) {
			ans += 1LL * sz[i] * (n - sz[i]);
			cjk.link( i, pa[i] );
			// printf( "i = %d\n", i );
		}
	
	memset(sz, 0, sizeof sz);
	memset(pa, 0, sizeof pa);
	dfs_sz(1, 0);
	
	for( int i = 1; i <= cyc_cnt; ++i )
		solve_cyc(i);
}

int main() {
	_w = scanf( "%d%d", &n, &m );
	origin.init();
	for( int i = 0; i < m; ++i ) {
		int u, v;
		_w = scanf( "%d%d", &u, &v );
		origin.link(u, v);
	}
	solve();
	printf( "%lld\n", ans );
	return 0;
}
