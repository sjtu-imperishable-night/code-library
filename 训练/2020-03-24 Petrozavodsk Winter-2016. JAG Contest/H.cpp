#include <bits/stdc++.h>

using namespace std;
const int N = 200010;
int _w;

int n, k;

namespace SGT {
	bool erased[N*4];
	int maxv[N*4], minv[N*4], addv[N*4];
	int ql, qr, qx;
	
	void init() {
		memset(erased, false, sizeof erased);
		memset(maxv, 0, sizeof maxv);
		memset(minv, 0, sizeof minv);
		memset(addv, 0, sizeof addv);
	}
	
	void pushdown( int o ) {
		int lc = o<<1, rc = lc|1;
		if( addv[o] ) {
			addv[lc] += addv[o];
			minv[lc] += addv[o];
			maxv[lc] += addv[o];
			addv[rc] += addv[o];
			minv[rc] += addv[o];
			maxv[rc] += addv[o];
			addv[o] = 0;
		}
	}
	
	void maintain( int o ) {
		int lc = o<<1, rc = lc|1;
		minv[o] = 1e9;
		maxv[o] = -1e9;
		erased[o] = true;
		if( !erased[lc] ) {
			erased[o] = false;
			minv[o] = min( minv[o], minv[lc] );
			maxv[o] = max( maxv[o], maxv[lc] );
		}
		if( !erased[rc] ) {
			erased[o] = false;
			minv[o] = min( minv[o], minv[rc] );
			maxv[o] = max( maxv[o], maxv[rc] );
		}
		minv[o] += addv[o];
		maxv[o] += addv[o];
	}
	
	void _op( int o, int L, int R ) {
		if( erased[o] ) return;
		if( L >= ql && R <= qr ) {
			if( maxv[o] == qx-1 && minv[o] == qx-1 ) {
				++addv[o];
				++maxv[o];
				++minv[o];
			} else {
				if( L == R ) {
					erased[o] = true;
				} else {
					int M = (L+R)/2, lc = o<<1, rc = lc|1;
					pushdown(o);
					_op(lc, L, M);
					_op(rc, M+1, R);
					maintain(o);
				}
			}
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			pushdown(o);
			if( ql <= M ) _op(lc, L, M);
			if( qr > M ) _op(rc, M+1, R);
			maintain(o);
		}
	}
	void op( int l, int r, int x ) {
		ql = l, qr = r, qx = x;
		_op(1, 1, n);
	}
	
	void _answer( int o, int L, int R ) {
		if( L == R ) {
			if( !erased[o] && minv[o] == k ) {
				assert( maxv[o] == k );
				++qx;
			}
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			pushdown(o);
			_answer(lc, L, M);
			_answer(rc, M+1, R);
		}
	}
	int answer() {
		qx = 0;
		_answer(1, 1, n);
		return qx;
	}
}

int main() {
	_w = scanf( "%d%d", &n, &k );
	SGT::init();
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		int l, r, x;
		_w = scanf( "%d%d%d", &l, &r, &x );
		SGT::op(l, r, x);
	}
	printf( "%d\n", SGT::answer() );
	return 0;
}
