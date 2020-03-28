#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int N = 100010;
int _w;

struct Edge {
	int u, v, w;
	Edge() {}
	Edge( int uu, int vv, int ww ) {
		u = uu, v = vv, w = ww;
	}
	bool operator<( const Edge &rhs ) const {
		return w > rhs.w;
	}
};

int n, px[N], py[N];
vector<Edge> edge;

int arr[N], val[N], fuck[N], yx[N];

bool cmp( int i, int j ) {
	if( px[i] == px[j] ) {
		return py[i] < py[j];
	} else {
		return px[i] < px[j];
	}
}

namespace Discrete {
	int *p[N], pn;
	
	void init() {
		pn = 0;
	}
	void ins( int *x ) {
		p[pn++] = x;
	}
	bool cmpp( int *i, int *j ) {
		return *i < *j;
	}
	void solve() {
		sort(p, p+pn, cmpp);
		int last = *p[0], id = 1;
		for( int i = 0; i < pn; ++i )
			if( *p[i] == last ) *p[i] = id;
			else last = *p[i], *p[i] = ++id;
	}
}

/*
struct SGT {
	struct Node {
		Node *lc, *rc;
		int mn, id;
		
		Node() {
			lc = rc = NULL;
			mn = 2e9, id = -1;
		}
	};
	
	Node *rt;
	
	SGT() {
		rt = NULL;
	}
	
	void _clear( Node *o ) {
		if( o == NULL ) return;
		_clear(o->lc);
		_clear(o->rc);
		delete o;
	}
	void clear() {
		_clear(rt);
		rt = NULL;
	}
	
	void _ins( Node *o, int L, int R, int x, int v, int idx ) {
		if( L == R ) {
			if( v < o->mn ) {
				o->mn = v;
				o->id = idx;
			}
		} else {
			int M = (L+R)/2;
			if( x <= M ) {
				if( !o->lc ) o->lc = new Node;
				_ins(o->lc, L, M, x, v, idx);
			} else {
				if( !o->rc ) o->rc = new Node;
				_ins(o->rc, M+1, R, x, v, idx);
			}
			if( v < o->mn ) {
				o->mn = v;
				o->id = idx;
			}
		}
	}
	void ins( int x, int v, int id ) {
		if( rt == NULL ) rt = new Node;
		_ins(rt, 1, n, x, v, id);
	}
	
	pii _query( Node *o, int L, int R, int ql, int qr ) {
		if( !o ) return pii(2e9, -1);
		if( L >= ql && R <= qr ) {
			return pii(o->mn, o->id);
		} else {
			int M = (L+R)/2;
			pii rtn(2e9, -1);
			if( ql <= M ) {
				pii tmp = _query(o->lc, L, M, ql, qr);
				if( tmp.first < rtn.first )
					rtn = tmp;
			}
			if( qr > M ) {
				pii tmp = _query(o->rc, M+1, R, ql, qr);
				if( tmp.first < rtn.first )
					rtn = tmp;
			}
			return rtn;
		}
	}
	void update( int x, pair<pii,pii> &shit ) {
		pii L = _query(rt, 1, n, 1, x);
		pii R = x == n ? pii(2e9, -1) : _query(rt, 1, n, x+1, n);
		if( L.first < shit.first.first ) {
			shit.first = L;
		}
		if( R.first < shit.second.first ) {
			shit.second = R;
		}
	}
};

namespace BIT {
	inline int lb( int x ) {
		return x & (-x);
	}
    
	SGT sgt[N];
	
	void init() {
		for( int i = 1; i <= n; ++i )
			sgt[i].clear();
	}
	void ins( int x, int y, int v, int id ) {
		for( ; x <= n; x += lb(x) )
			sgt[x].ins(y, v, id);
	}
	void query( int x, int y, int v, int id ) {
		pair<pii,pii> shit(pii(2e9, -1), pii(2e9, -1));
		for( ; x; x -= lb(x) )
			sgt[x].update(y, shit);
		if( shit.first.second != -1 ) {
			edge.push_back( Edge(id, shit.first.second, v - shit.first.first) );
		}
		if( shit.second.second != -1 ) {
			edge.push_back( Edge(id, shit.second.second, v - shit.second.first) );
		}
	}
}
*/

namespace BIT {
	inline int lb( int x ) {
		return x & (-x);
	}
	
	int c[N], id[N];
	
	void init() {
		memset(c, 0x7f, sizeof c);
		memset(id, -1, sizeof id);
	}
	void ins( int x, int v, int idx ) {
		for( ; x <= n; x += lb(x) )
			if( v < c[x] ) {
				c[x] = v;
				id[x] = idx;
			}
	}
	void query( int x, int v, int idx ) {
		int mn = 2e9, nod = -1;
		for( ; x; x -= lb(x) )
			if( c[x] < mn ) {
				mn = c[x];
				nod = id[x];
			}
		if( nod != -1 ) {
			edge.push_back( Edge(idx, nod, v-mn) );
		}
	}
}

void _prelude( int type ) {
	for( int i = 1; i <= n; ++i )
		arr[i] = i;
	sort(arr+1, arr+n+1, cmp);
	for( int i = 1; i <= n; ++i )
		if( type == 1 ) {
			val[i] = px[i] + py[i] + px[i];
		} else {
			val[i] = px[i] + py[i] + py[i];
		}
	Discrete::init();
	for( int i = 1; i <= n; ++i ) {
		fuck[i] = py[i];
		Discrete::ins(fuck+i);
	}
	Discrete::solve();
	/*
	Discrete::init();
	for( int i = 1; i <= n; ++i ) {
		yx[i] = py[i] - px[i];
		Discrete::ins(yx+i);
	}
	Discrete::solve();
	*/
	// puts("discrete ok");
	BIT::init();
	for( int i = 1; i <= n; ++i ) {
		int fck = fuck[arr[i]];
		// int xy = yx[arr[i]];
		int v = val[arr[i]];
		BIT::query(fck-1, v, arr[i]);
		BIT::ins(fck, v, arr[i]);
	}
}

void prelude() {
	for( int i = 1; i <= n; ++i )
		py[i] -= px[i];
	_prelude(1);
	for( int i = 1; i <= n; ++i ) {
		py[i] += px[i];
		px[i] -= py[i];
	}
	_prelude(2);
	for( int i = 1; i <= n; ++i )
		px[i] += py[i];
}

void rotate() {
	for( int i = 1; i <= n; ++i ) {
		swap( px[i], py[i] );
		py[i] = -py[i];
	}
}

namespace DSU {
	int pa[N];
	
	void init() {
		for( int i = 1; i <= n; ++i )
			pa[i] = i;
	}
	int find( int u ) {
		return u == pa[u] ? u : pa[u] = find( pa[u] );
	}
	bool link( int u, int v ) {
		u = find(u), v = find(v);
		if( u == v ) return false;
		else return pa[u] = v, true;
	}
}

void solve() {
	sort(edge.begin(), edge.end());
	int ans = 2e9;
	DSU::init();
	for( Edge e : edge ) {
		if( DSU::link(e.u, e.v) ) {
			ans = min( ans, e.w );
		}
	}
	cout << ans << endl;
}

int main() {
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d%d", px+i, py+i );
	// puts("here");
	prelude();
	// puts("here");
	rotate();
	prelude();
	rotate();
	prelude();
	rotate();
	prelude();
	// puts("here");
	solve();
	return 0;
}
