#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 100010;
int _w;

int n, a[N];

int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		_w = scanf( "%d", &n );
		for( int i = 0; i < n; ++i )
			_w = scanf( "%d", a+i );
		sort(a, a+n, greater<int>());
		ll ans = 0;
		for( int i = 0; i < n; ++i )
			ans += max(0, a[i] - i);
		printf( "%lld\n", ans );
	}
	return 0;
}
