#include <bits/stdc++.h>

using namespace std;
const int N = 100010;
const int MOD = 1e9+7;
int _w;

int n, a[N], sum, ans = 1;

int main() {
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i ) {
		_w = scanf( "%d", a+i );
		sum += a[i] - 1;
	}
	for( int i = 1; i <= sum; ++i )
		ans = int(1LL * ans * i % MOD);
	for( int i = 1; i <= n; ++i ) {
		if( a[i] == 3 ) {
			ans = int(1LL * ans * (MOD+1)/2 % MOD);
		}
	}
	if( sum != n-2 ) {
		puts("0");
	} else {
		cout << ans << endl;
	}
	return 0;
}
