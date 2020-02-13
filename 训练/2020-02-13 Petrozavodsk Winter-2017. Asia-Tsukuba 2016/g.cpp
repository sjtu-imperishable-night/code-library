#include <bits/stdc++.h>

using namespace std;
const int N = 1e9+1;
int _w;

struct Node {
	Node *lc, *rc;
	bool all, none;
	int tag;
	
	Node() {
		lc = rc = NULL;
		all = false, none = true;
		tag = -1;
	}
	
	void pushdown() {
		if( lc == NULL ) lc = new Node;
		if( rc == NULL ) rc = new Node;
		if( tag != -1 ) {
			lc->tag = rc->tag = tag;
			if( tag ) {
				lc->all = rc->all = true;
				lc->none = rc->none = false;
			} else {
				lc->all = rc->all = false;
				lc->none = rc->none = true;
			}
			tag = -1;
		}
	}
};

Node *rt;
bool one = false;

void init() {
	rt = new Node;
}

int _check( Node *o, int L, int R, int x ) {
	if( o->all ) return -1;
	if( L == R ) return L;
	int M = (L+R)/2;
	o->pushdown();
	if( x > M ) {
		int ans = _check(o->rc, M+1, R, x);
		if( ans != -1 ) return ans;
	}
	return _check(o->lc, L, M, x);
}

int check( int x ) {
	return _check(rt, 0, N, x);
}

int _checkr( Node *o, int L, int R, int x ) {
	if( o->none ) return -1;
	if( L == R ) return L;
	int M = (L+R)/2;
	o->pushdown();
	if( x <= M ) {
		int ans = _checkr(o->lc, L, M, x);
		if( ans != -1 ) return ans;
	}
	return _checkr(o->rc, M+1, R, x);
}

int checkr( int x ) {
	return _checkr(rt, 0, N, x);
}

void _modify( Node *o, int L, int R, int ql, int qr, int qv ) {
	if( L >= ql && R <= qr ) {
		o->tag = qv;
		if( qv == 1 ) {
			o->all = true;
			o->none = false;
		} else {
			o->all = false;
			o->none = true;
		}
	} else {
		o->pushdown();
		int M = (L+R)/2;
		if( ql <= M ) _modify(o->lc, L, M, ql, qr, qv);
		if( qr > M ) _modify(o->rc, M+1, R, ql, qr, qv);
		o->all = o->lc->all && o->rc->all;
		o->none = o->lc->none && o->rc->none;
	}
}

void modify( int l, int r, int v ) {
	_modify(rt, 0, N, l, r, v);
}

bool solve( int x ) {
	int pos = check(x);
	if( pos == 0 ) {
		int rp = checkr(x+1);
		// printf( "rp = %d\n", rp );
		if( rp == N ) {
			one = true;
			return true;
		} else {
			return false;
		}
	} else if( pos == x ) {
		modify(x, x, 1);
		return true;
	} else {
		modify(pos+1, x, 0);
		modify(pos, pos, 1);
		return true;
	}
}

int main() {
	init();
	modify(N, N, 1);
	int n;
	_w = scanf( "%d", &n );
	while( n-- ) {
		int x;
		_w = scanf( "%d", &x );
		if( one ) {
			puts("No");
		} else {
			if( solve(x) ) {
				puts("Yes");
			} else {
				puts("No");
			}
		}
	}
	return 0;
}
