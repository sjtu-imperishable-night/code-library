#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int _w;

void solve( int k, int x ) {
	ll cnt[30];
	cnt[0] = 1;
	for( int i = 1; i < 30; ++i )
		cnt[i] = cnt[i-1] * k;
	int digit = 1;
	while( cnt[digit] < x ) {
		x -= (int)cnt[digit];
		++digit;
	}
	for( int i = digit; i >= 1; --i ) {
		int tmp = (x-1) / (int)cnt[i-1];
		putchar( 10 - k + tmp + '0' );
		x -= tmp * (int)cnt[i-1];
	}
	assert( x == 1 );
	puts("");
}

int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		int k, x;
		_w = scanf( "%d%d", &k, &x );
		solve(k, x);
	}
	return 0;
}
