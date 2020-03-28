#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 100010;
int _w;

int w;
ll n, h[N];

namespace SGT {
	ll sumv[N*4], addv[N*4], maxv[N*4], qv;
	int ql, qr;
	
	void _add( int o, int L, int R ) {
		if( L >= ql && R <= qr ) {
			addv[o] += qv;
			sumv[o] += qv * (R-L+1);
			maxv[o] += qv;
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			if( ql <= M ) _add(lc, L, M);
			if( qr > M ) _add(rc, M+1, R);
			sumv[o] = sumv[lc] + sumv[rc];
			sumv[o] += addv[o] * (R-L+1);
			maxv[o] = max( maxv[lc], maxv[rc] );
			maxv[o] += addv[o];
		}
	}
	void add( int l, int r, ll v ) {
		ql = l, qr = r, qv = v;
		_add(1, 1, w);
	}
	
	void init() {
		for( int i = 1; i <= w; ++i )
			SGT::add(i, i, h[i]);
	}
	
	void _query( int o, int L, int R, ll adv ) {
		if( L >= ql && R <= qr ) {
			qv += sumv[o];
			qv += adv * (R-L+1);
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			adv += addv[o];
			if( ql <= M ) _query(lc, L, M, adv);
			if( qr > M ) _query(rc, M+1, R, adv);
		}
	}
	ll query( int l, int r ) {
		ql = l, qr = r, qv = 0;
		_query(1, 1, w, 0);
		return qv;
	}
	
	void _qmax( int o, int L, int R, ll adv ) {
		if( L >= ql && R <= qr ) {
			qv = max( qv, maxv[o] + adv );
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			adv += addv[o];
			if( ql <= M ) _qmax(lc, L, M, adv);
			if( qr > M ) _qmax(rc, M+1, R, adv);
		}
	}
	ll qmax( int l, int r ) {
		ql = l, qr = r, qv = 0;
		_qmax(1, 1, w, 0);
		return qv;
	}
	
	int _bs_left( int o, int L, int R, ll adv ) {
		if( maxv[o] + adv < qv ) return 0;
		if( L == R ) return L;
		int M = (L+R)/2, lc = o<<1, rc = lc|1;
		adv += addv[o];
		if( qr > M ) {
			int tmp = _bs_left(rc, M+1, R, adv);
			if( tmp ) return tmp;
		}
		if( ql <= M ) {
			int tmp = _bs_left(lc, L, M, adv);
			if( tmp ) return tmp;
		}
		return 0;
	}
	int bs_left( int l, int r, ll v ) {
		ql = l, qr = r, qv = v;
		return _bs_left(1, 1, w, 0);
	}
	
	int _bs_right( int o, int L, int R, ll adv ) {
		if( maxv[o] + adv < qv ) return 0;
		if( L == R ) return L;
		int M = (L+R)/2, lc = o<<1, rc = lc|1;
		adv += addv[o];
		if( ql <= M ) {
			int tmp = _bs_right(lc, L, M, adv);
			if( tmp ) return tmp;
		}
		if( qr > M ) {
			int tmp = _bs_right(rc, M+1, R, adv);
			if( tmp ) return tmp;
		}
		return 0;
	}
	int bs_right( int l, int r, ll v ) {
		ql = l, qr = r, qv = v;
		return _bs_right(1, 1, w, 0);
	}
}

bool check( ll height, int pos ) {
	ll lmax = SGT::qmax(1, pos);
	ll rmax = SGT::qmax(pos, w);
	if( height > min(lmax, rmax) )
		return false;
	int L = SGT::bs_left(1, pos, height);
    int R = SGT::bs_right(pos, w, height);
	return n >= height * (R-L+1) - SGT::query(L, R);
}

ll query( int pos ) {
	ll low = h[pos], high = 2e9;
	while( low < high ) {
		ll mid = (low + high + 1)/2;
		if( check(mid, pos) ) low = mid;
		else high = mid-1;
	}
	return low;
}

void solve() {
	SGT::init();
	for( int i = 2; i <= w; ++i )
		SGT::add(i, i, i-1);
	ll ans = *max_element(h+1, h+w+1);
	for( int i = 1; i < w; ++i ) {
		if( i == 1 ) {
			SGT::add(2, w, -1);
			SGT::add(1, 1, 1);
		} else {
			ans = max( ans, query(i) );
			SGT::add(i+1, w, -1);
			SGT::add(1, i, 1);
		}
	}
	printf( "%lld\n", ans );
}

int main() {
	freopen("landscape.in", "r", stdin);
	freopen("landscape.out", "w", stdout);
	_w = scanf( "%d%lld", &w, &n );
	for( int i = 1; i <= w; ++i )
		_w = scanf( "%lld", h+i );
	solve();
	return 0;
}
