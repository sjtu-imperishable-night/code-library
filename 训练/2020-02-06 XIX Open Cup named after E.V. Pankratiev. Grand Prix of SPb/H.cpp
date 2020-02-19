#include <bits/stdc++.h>

using namespace std;
typedef __int128 ll;
const int N = 18;
const int K = 10;
int _w;

int n, k, C;

struct Cube {
	int a[K], b[K];
	
	ll area() const {
		ll ans = 1;
		for( int i = 0; i < k; ++i ) {
			if( b[i] <= a[i] ) return 0;
			ans *= b[i] - a[i];
		}
		return ans;
	}
};

Cube Inter( Cube A, Cube B ) {
	Cube ans;
	for( int i = 0; i < k; ++i ) {
		ans.a[i] = max( A.a[i], B.a[i] );
		ans.b[i] = min( A.b[i], B.b[i] );
	}
	return ans;
}

Cube cube[N], intersect[1<<N], now;

void init() {
	for( int s = 0; s < (1<<n); ++s ) {
		for( int i = 0; i < k; ++i ) {
			intersect[s].a[i] = 0;
			intersect[s].b[i] = C;
		}
		for( int i = 0; i < n; ++i )
			if( s & (1<<i) )
				intersect[s] = Inter( intersect[s], cube[i] );
	}
}

bool check() {
	ll tot = 0;
	for( int s = 1; s < (1<<n); ++s ) {
		ll area = Inter( intersect[s], now ).area();
		if( __builtin_popcount(s) & 1 ) tot += area;
		else tot -= area;
	}
	return tot < now.area();
}

void solve() {
	for( int i = 0; i < k; ++i ) {
		now.a[i] = 0;
		now.b[i] = C;
	}
	for( int dim = 0; dim < k; ++dim ) {
		int low = 1, high = C+1;
		while( low < high ) {
			int mid = (low + high)/2;
			now.b[dim] = mid;
			if( check() ) high = mid;
			else low = mid+1;
		}
		if( low == C+1 ) {
			puts("NO"); 
			exit(0);
		}
		now.b[dim] = low;
	}
	puts("YES");
	for( int i = 0; i < k; ++i )
		printf( "%d ", now.b[i] - 1 );
	puts("");
}

int main() {
	_w = scanf( "%d%d%d", &n, &k, &C );
	for( int i = 0; i < n; ++i ) {
		for( int j = 0; j < k; ++j )
			_w = scanf( "%d", &cube[i].a[j] );
		for( int j = 0; j < k; ++j )
			_w = scanf( "%d", &cube[i].b[j] );
	}
	init();
	solve();
	return 0;
}
