#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2000010;
int _w;

struct pll {
	ll first, second;
	int type;
	
	pll() {
		;
	}
	pll( ll first_, ll second_, int type_ ) {
		first = first_;
		second = second_;
		type = type_;
	}
	
	bool operator<( const pll &rhs ) const {
		return first < rhs.first;
	}
};

int n, a[N];

namespace G {
	int head[N], nxt[N*2], to[N*2], eid;
	void init() {
		eid = 0;
		for( int i = 1; i <= n; ++i )
			head[i] = -1;
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
		to[eid] = u, nxt[eid] = head[v], head[v] = eid++;
	}
}

ll ans;

bool vis[N];

namespace Centroid {
	int f[N], sz[N], totsz, opt, g;
	
	int dfs_sz( int u, int fa ) {
		using namespace G;
		sz[u] = 1;
		for( int i = head[u]; ~i; i = nxt[i] ) {
			int v = to[i];
			if( vis[v] || v == fa ) continue;
			sz[u] += dfs_sz(v, u);
		}
		return sz[u];
	}
	void dfs_dp( int u, int fa ) {
		using namespace G;
		f[u] = totsz - sz[u];
		for( int i = head[u]; ~i; i = nxt[i] ) {
			int v = to[i];
			if( vis[v] || v == fa ) continue;
			dfs_dp(v, u);
			f[u] = max( f[u], sz[v] );
		}
		if( f[u] < opt )
			opt = f[u], g = u;
	}
	int centroid( int u ) {
		dfs_sz(u, 0);
		totsz = sz[u];
		g = u;
		opt = 1e9;
		dfs_dp(u, 0);
		return g;
	}
}

pll vec[N];
int vecn;

ll sum[N], mx[N];

ll val[N];
int vn;

struct BIT {
	int c[N];
	
	inline int lb( int x ) const {
		return x & (-x);
	}

	void init() {
		for( int i = 1; i <= vn; ++i )
			c[i] = 0;
	}
	void inc( int p ) {
		for( ; p <= vn; p += lb(p) )
			++c[p];
	}
	int sum( int p ) {
		int s = 0;
		for( ; p; p -= lb(p) )
			s += c[p];
		return s;
	}
	int sum( int l, int r ) {
		return sum(r) - sum(l-1);
	}
};
BIT bit[2];

ll stat() {
	sort(vec, vec + vecn);
	vn = 0;
	for( int i = 0; i < vecn; ++i ) {
		pll pr = vec[i];
		val[vn++] = pr.second;
	}
	sort(val, val+vn);
	vn = int(unique(val, val+vn) - val);
	for( int i = vn; i >= 1; --i )
		val[i] = val[i-1];
	bit[0].init();
	bit[1].init();
	
	ll now = 0;
	for( int i = 0; i < vecn; ++i ) {
		pll pr = vec[i];
		ll tmp = pr.first + pr.first - pr.second;
		int pos = int(upper_bound(val+1, val+vn+1, tmp) - val);
		now += bit[pr.type ^ 1].sum(pos, vn);
		bit[pr.type].inc( int(lower_bound(val+1, val+vn+1, pr.second) - val) );
	}
	return now;
}

void dfs_stat( int u, int fa, int type ) {
	using namespace G;
	sum[u] = sum[fa] + a[u];
	mx[u] = max( mx[fa], (ll)a[u] );
	vec[vecn++] = pll( mx[u], sum[u], type );
	for( int i = head[u]; ~i; i = nxt[i] ) {
		int v = to[i];
		if( v == fa || vis[v] ) continue;
		dfs_stat(v, u, type);
	}
}

void dfs_final( int u, int fa ) {
	using namespace G;
	sum[u] = sum[fa] + a[u];
	mx[u] = max( mx[fa], (ll)a[u] );
	ans += sum[u] - mx[u] > mx[u];
	for( int i = head[u]; ~i; i = nxt[i] ) {
		int v = to[i];
		if( v == fa || vis[v] ) continue;
		dfs_final(v, u);
	}
}

int dfs_extra( int u, int fa, ll rt_val ) {
	using namespace G;
	sum[u] = sum[fa] + a[u];
	mx[u] = max( mx[fa], (ll)a[u] );
	ll s = sum[u] + sum[u] + rt_val;
	ll x = max( mx[u], rt_val );
	int now = s - x > x;
	for( int i = head[u]; ~i; i = nxt[i] ) {
		int v = to[i];
		if( v == fa || vis[v] ) continue;
		now += dfs_extra(v, u, rt_val);
	}
	return now;
}

void solve( int u ) {
	using namespace G;
	u = Centroid::centroid(u);
	vis[u] = true;
	
	ll now = 0;
	
	vecn = 0;
	for( int i = head[u]; ~i; i = nxt[i] ) {
		int v = to[i];
		if( vis[v] ) continue;
		sum[u] = a[u];
		mx[u] = a[u];
		dfs_stat(v, u, 1);
		sum[u] = 0;
		mx[u] = 0;
		dfs_stat(v, u, 0);
	}
	now += stat();
	
	for( int i = head[u]; ~i; i = nxt[i] ) {
		int v = to[i];
		if( vis[v] ) continue;
		
		ll tmp = 0;
		
		vecn = 0;
		sum[u] = a[u];
		mx[u] = a[u];
		dfs_stat(v, u, 1);
		sum[u] = 0;
		mx[u] = 0;
		dfs_stat(v, u, 0);
		tmp += stat();
		// printf( "u = %d, v = %d, tmp = %lld\n", u, v, tmp );
		
		now -= tmp;
		// printf( "u = %d, v = %d, tmp = %lld\n", u, v, tmp );
	}

	// printf( "u = %d, now = %lld\n", u, now );
	ans += now / 2;
	
	for( int i = head[u]; ~i; i = nxt[i] ) {
		int v = to[i];
		if( vis[v] ) continue;
		sum[u] = a[u];
		mx[u] = a[u];
		dfs_final(v, u);
	}
	
	for( int i = head[u]; ~i; i = nxt[i] )
		if( !vis[to[i]] )
			solve( to[i] );
}

int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		_w = scanf( "%d", &n );
		for( int i = 1; i <= n; ++i )
			_w = scanf( "%d", a+i );
		G::init();
		for( int i = 0; i < n-1; ++i ) {
			int u, v;
			_w = scanf( "%d%d", &u, &v );
			G::link(u, v);
		}
		ans = 0;
		for( int i = 1; i <= n; ++i )
			vis[i] = false;
		solve(1);
		printf( "%lld\n", ans );
	}
	return 0;
}
