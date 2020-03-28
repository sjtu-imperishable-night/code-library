#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int N = 3010;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int _w;

int n, px[N], py[N], pd[N], xid[N], yid[N];

vector<int> xt[N], yt[N];

struct DSU {
	vector<int> pa;
	
	void init( int m ) {
		pa.resize(m);
		for( int i = 0; i < m; ++i )
			pa[i] = i;
	}
	int find( int u ) {
		return pa[u] == u ? u : pa[u] = find( pa[u] );
	}
	void link( int u, int v ) {
		pa[find(u)] = find(v);
	}
};

struct {
	DSU dsu[N];
	
	void init() {
		for( int i = 0; i < N; ++i )
			dsu[i].init( (int)xt[i].size() );
	}
	
	int find( int u ) {
		int x = px[u], id = xid[u];
		int tmp = dsu[x].find(id);
		--tmp;
		if( tmp == -1 ) return -1;
		else return xt[x][tmp];
	}
	
	void erase( int u ) {
		int x = px[u], id = xid[u];
		if( id != (int)xt[x].size() - 1 )
			dsu[x].link(id+1, id);
	}
}xl;

struct {
	DSU dsu[N];
	
	void init() {
		for( int i = 0; i < N; ++i )
			dsu[i].init( (int)xt[i].size() );
	}
	
	int find( int u ) {
		int x = px[u], id = xid[u];
		int tmp = dsu[x].find(id);
		++tmp;
		if( tmp == (int)xt[x].size() ) return -1;
		else return xt[x][tmp];
	}
	
	void erase( int u ) {
		int x = px[u], id = xid[u];
		if( id != 0 )
			dsu[x].link(id-1, id);
	}
}xr;

struct {
	DSU dsu[N];
	
	void init() {
		for( int i = 0; i < N; ++i )
			dsu[i].init( (int)yt[i].size() );
	}
	
	int find( int u ) {
		int y = py[u], id = yid[u];
		int tmp = dsu[y].find(id);
		--tmp;
		if( tmp == -1 ) return -1;
		else return yt[y][tmp];
	}
	
	void erase( int u ) {
		int y = py[u], id = yid[u];
		if( id != (int)yt[y].size() - 1 )
			dsu[y].link(id+1, id);
	}
}yl;

struct {
	DSU dsu[N];
	
	void init() {
		for( int i = 0; i < N; ++i )
			dsu[i].init( (int)yt[i].size() );
	}
	
	int find( int u ) {
		int y = py[u], id = yid[u];
		int tmp = dsu[y].find(id);
		++tmp;
		if( tmp == (int)yt[y].size() ) return -1;
		else return yt[y][tmp];
	}
	
	void erase( int u ) {
		int y = py[u], id = yid[u];
		if( id != 0 )
			dsu[y].link(id-1, id);
	}
}yr;

int solve( int s ) {
	xl.init(), xr.init();
	yl.init(), yr.init();
	int ans = 1, x = px[s], y = py[s], d = pd[s];
	// printf( "sx = %d, sy = %d, sd = %d\n", x, y, d );
	xl.erase(s), xr.erase(s);
	yl.erase(s), yr.erase(s);
	while(1) {
		bool flag = false;
		if( d == 2 ) {
			int nxt = xl.find(s);
			if( nxt == -1 ) {
				;
			} else {
				flag = true;
				s = nxt;
				x = px[s], y = py[s], d = pd[s];
			}
		} else if( d == 3 ) {
			int nxt = xr.find(s);
			if( nxt == -1 ) {
				;
			} else {
				flag = true;
				s = nxt;
				x = px[s], y = py[s], d = pd[s];
			}
		} else if( d == 0 ) {
			int nxt = yl.find(s);
			if( nxt == -1 ) {
				;
			} else {
				flag = true;
				s = nxt;
				x = px[s], y = py[s], d = pd[s];
			}
		} else {
			assert( d == 1 );
			int nxt = yr.find(s);
			if( nxt == -1 ) {
				;
			} else {
				flag = true;
				s = nxt;
				x = px[s], y = py[s], d = pd[s];
			}
		}
		if( !flag ) break;
		else {
			++ans;
			xl.erase(s), xr.erase(s);
			yl.erase(s), yr.erase(s);
			// printf( "x = %d, y = %d, d = %d\n", x, y, d );
		}
	}
	return ans;
}

bool cmpx( int i, int j ) {
	return px[i] < px[j];
}

bool cmpy( int i, int j ) {
	return py[i] < py[j];
}

namespace Disc {
	int *p[N], pn;
	void init() {
		pn = 0;
	}
	void insert( int *x ) {
		p[pn++] = x;
	}
	bool cmp( int *i, int *j ) {
		return *i < *j;
	}
	void solve() {
		sort(p, p+pn, cmp);
		int last = *p[0], id = 0;
		for( int i = 0; i < pn; ++i )
			if( *p[i] == last ) *p[i] = id;
			else last = *p[i], *p[i] = ++id;
	}
}

int main() {
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i ) {
		char dir;
		_w = scanf( "%d%d %c", px+i, py+i, &dir );
		if( dir == '^' ) {
			pd[i] = 2;
		} else if( dir == 'v' ) {
			pd[i] = 3;
		} else if( dir == '<' ) {
			pd[i] = 0;
		} else {
			assert( dir == '>' );
			pd[i] = 1;
		}
	}
	Disc::init();
	for( int i = 1; i <= n; ++i )
		Disc::insert(px+i);
	Disc::solve();
	Disc::init();
	for( int i = 1; i <= n; ++i )
		Disc::insert(py+i);
	Disc::solve();
	for( int i = 1; i <= n; ++i ) {
		xt[px[i]].push_back(i);
		yt[py[i]].push_back(i);
	}
	for( int i = 0; i < N; ++i )
		sort( xt[i].begin(), xt[i].end(), cmpy );
	for( int i = 0; i < N; ++i )
		sort( yt[i].begin(), yt[i].end(), cmpx );
	for( int it = 0; it < N; ++it ) {
		const vector<int> &vec = xt[it];
		for( int i = 0; i < (int)vec.size(); ++i )
			xid[vec[i]] = i;
	}
	for( int it = 0; it < N; ++it ) {
		const vector<int> &vec = yt[it];
		for( int i = 0; i < (int)vec.size(); ++i )
			yid[vec[i]] = i;
	}
	int ans = 0;
	for( int i = 1; i <= n; ++i )
		ans = max( ans, solve(i) );
	cout << ans << endl;
	return 0;
}
