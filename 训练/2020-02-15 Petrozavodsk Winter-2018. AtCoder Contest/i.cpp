#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 200010;
const int INF = 1e9;
int _w;

int n, q, a[N];

namespace SGT {
	int maxv[N*4];
	int tb[N*4], tc[N*4], td[N*4];
	int ql, qr, qv;
	
	void calc( int o, int L, int R ) {
		if( L == R ) return;
		int lc = o<<1, rc = lc|1;
		maxv[o] = max( maxv[lc], maxv[rc] );
		maxv[o] = int( (maxv[o] + tb[o]) / tc[o] + td[o] );
	}
	
	void _init( int o, int L, int R ) {
		if( L == R ) {
			maxv[o] = a[L];
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			_init(lc, L, M);
			_init(rc, M+1, R);
			tb[o] = 0;
			tc[o] = 1;
			td[o] = 0;
			calc(o, L, R);
		}
	}
	void init() {
		_init(1, 0, n-1);
	}
	
	void add_tag( int o, int L, int R, int v ) {
		if( L == R ) {
			maxv[o] += v;
		} else {
			td[o] += v;
			calc(o, L, R);
		}
	}
	void div_tag( int o, int L, int R, int v ) {
		if( L == R ) {
			maxv[o] /= v;
		} else {
			if( tc[o] == INF ) {
				if( td[o] % v == v-1 ) {
					td[o] /= v;
				} else {
					td[o] /= v;
					tb[o] = 0;
					tc[o] = INF;
				}
			} else {
				ll up = tb[o] + 1LL * tc[o] * td[o];
				ll down = 1LL * tc[o] * v;
				td[o] = int(up / down);
				up %= down;
				if( down <= INF ) {
					tb[o] = int(up);
					tc[o] = int(down);
				} else {
					tc[o] = INF;
					tb[o] = (int)max( 0LL, up - (down - INF) );
				}
			}
			calc(o, L, R);
		}
	}
	void pushdown( int o, int L, int R ) {
		if( L == R ) return;
		int M = (L+R)/2, lc = o<<1, rc = lc|1;
		add_tag(lc, L, M, tb[o]);
		add_tag(rc, M+1, R, tb[o]);
		div_tag(lc, L, M, tc[o]);
		div_tag(rc, M+1, R, tc[o]);
		add_tag(lc, L, M, td[o]);
		add_tag(rc, M+1, R, td[o]);
		tb[o] = 0;
		tc[o] = 1;
		td[o] = 0;
	}
	
	void _add( int o, int L, int R ) {
		if( L >= ql && R <= qr ) {
			add_tag(o, L, R, qv);
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			pushdown(o, L, R);
			if( ql <= M ) _add(lc, L, M);
			if( qr > M ) _add(rc, M+1, R);
			calc(o, L, R);
		}
	}
	void add( int l, int r, int v ) {
		ql = l, qr = r, qv = v;
		_add(1, 0, n-1);
	}
	
	void _div( int o, int L, int R ) {
		if( L >= ql && R <= qr ) {
			div_tag(o, L, R, qv);
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			pushdown(o, L, R);
			if( ql <= M ) _div(lc, L, M);
			if( qr > M ) _div(rc, M+1, R);
			calc(o, L, R);
		}
	}
	void div( int l, int r, int v ) {
		if( v == 1 ) return;
		ql = l, qr = r, qv = v;
		_div(1, 0, n-1);
	}

	void _query( int o, int L, int R ) {
		if( L >= ql && R <= qr ) {
			qv = max( qv, maxv[o] );
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			pushdown(o, L, R);
			if( ql <= M ) _query(lc, L, M);
			if( qr > M ) _query(rc, M+1, R);
		}
	}
	int query( int l, int r ) {
		ql = l, qr = r, qv = 0;
		_query(1, 0, n-1);
		return qv;
	}
}

int main() {
	_w = scanf( "%d%d", &n, &q );
	for( int i = 0; i < n; ++i )
		_w = scanf( "%d", a+i );
	SGT::init();
	while( q-- ) {
		int t, l, r, x;
		_w = scanf( "%d%d%d%d", &t, &l, &r, &x );
		if( t == 0 ) {
			SGT::add(l, r, x);
		} else if( t == 1 ) {
			SGT::div(l, r, x);
		} else {
			printf( "%d\n", SGT::query(l, r) );
		}
	}
	return 0;
}
