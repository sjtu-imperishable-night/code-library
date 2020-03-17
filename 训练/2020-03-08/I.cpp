#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000010;
const ll INFLL = 1e18;
int _w;

int n, a[N];

int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		_w = scanf( "%d", &n );
		for( int i = 1; i <= n; ++i )
			_w = scanf( "%d", a+i );
		ll ans = -INFLL;
		ll odd_sum = INFLL;
		ll even_sum = 0;
		ll sum = 0;
		for( int i = 1; i <= n; ++i ) {
			sum += a[i];
			if( i & 1 ) {
				ans = max( ans, sum - even_sum );
				odd_sum = min( odd_sum, sum );
			} else {
				ans = max( ans, sum - odd_sum );
				even_sum = min( even_sum, sum );
			}
		}
		printf( "%lld\n", ans );
	}
	return 0;
}
