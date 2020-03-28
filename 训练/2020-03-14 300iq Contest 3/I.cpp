#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 110;
const int MOD = 998244353;
int _w;

int n, k, now, vis[N];
ll a[N], ans = 0;

void solve() {
	now = k;
	for( int i = 0; i < k; ++i )
		vis[i] = false;
	for( int i = 1; i <= n; ++i ) {
		int cnt = 0;
		for( int j = 0; j < k; ++j )
			if( a[i] & (1LL << j) ) {
				if( vis[j] ) {
					;
				} else {
					vis[j] = true;
					++cnt;
				}
			}
		ans += 1LL * ((1LL << now) - (1LL << (now - cnt))) % MOD * i;
		ans %= MOD;
		now -= cnt;
	}
	printf( "%lld\n", ans );
}

int main() {
	_w = scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%lld", a+i );
	solve();
	return 0;
}
