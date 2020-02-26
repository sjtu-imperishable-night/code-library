#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll INFLL = 1e18;
int _w;

ll minv;
vector<ll> ans, now;

ll calc( int *begin, int *end ) {
	ll x = 0;
	while( begin != end ) {
		x = x * 10 + *begin;
		++begin;
	}
	return x;
}

void solve( ll n ) {
	if( n < minv ) {
		minv = n;
		ans = now;
	}
	
	int d[20], len = 0;
	while( n ) {
		d[len++] = int(n % 10);
		n /= 10;
	}
	reverse(d, d+len);
    
	for( int mid = 1; mid < len; ++mid ) {
		ll nxt = abs( calc(d, d+mid) - calc(d+mid, d+len) );
		if( nxt ) {
			now.push_back(nxt);
			solve(nxt);
			now.pop_back();
		}
		if( minv == 1 ) return;
	}
}

int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		ll n;
		_w = scanf( "%lld", &n );
		minv = INFLL;
		
		ans.clear();
		now.push_back(n);
		solve(n);
		now.pop_back();
		
		assert( ans.size() );
		printf( "%d ", (int)ans.size() );
		for( ll x : ans )
			printf( "%lld ", x );
		puts("");
	}
	return 0;
}
