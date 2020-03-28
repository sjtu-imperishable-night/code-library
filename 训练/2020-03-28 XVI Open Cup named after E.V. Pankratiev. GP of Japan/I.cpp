#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const int N = 4010;
const ll INFLL = 1e18;
int _w;

int n, T;

struct Song {
	int t, p, f;
	Song() {}
	Song( int tt, int pp, int ff ) {
		t = tt, p = pp, f = ff;
	}
	bool operator<( const Song &rhs ) const {
		return f < rhs.f;
	}
};
Song song[N];

ll dp[N][N];

namespace Plane {
	pll q[N];
	int head, tail;
	
	void init() {
		head = tail = 0;
	}
	pll vec( pll a, pll b ) {
		return pll( b.first - a.first, b.second - a.second );
	}
	ll cross( pll a, pll b ) {
		return a.first * b.second - a.second * b.first;
	}
	void insert( ll x, ll y ) {
		pll now(x, y);
		while( tail - head >= 2 && cross( vec( q[tail-2], q[tail-1] ), vec( q[tail-2], now ) ) >= 0 )
			--tail;
		q[tail++] = now;
	}
	ll func( pll p, ll k ) {
		return p.second - k * p.first;
	}
	ll query( ll k ) {
		k = -k;
		while( tail - head >= 2 && func( q[head+1], k ) > func( q[head], k ) )
			++head;
		return func( q[head], k );
	}
}

void solve() {
	for( int i = 1; i <= n; ++i )
		dp[song[i].t][i] = song[i].p;
	for( int t = 0; t < T; ++t ) {
		Plane::init();
		for( int i = 2; i <= n; ++i ) {
			Plane::insert( song[i-1].f, -1LL * song[i-1].f * song[i-1].f + dp[t][i-1] );
			ll tmp = Plane::query( 2 * song[i].f ) + song[i].p - 1LL * song[i].f * song[i].f;
			if( t + song[i].t <= T )
				dp[t + song[i].t][i] = max( dp[t + song[i].t][i], tmp );
		}
	}
	ll ans = 0;
	for( int t = 0; t <= T; ++t )
		for( int i = 1; i <= n; ++i )
			ans = max( ans, dp[t][i] );
	cout << ans << endl;
}

int main() {
	_w = scanf( "%d%d", &n, &T );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d%d%d", &song[i].t, &song[i].p, &song[i].f );
	sort( song+1, song+n+1 );
	solve();
	return 0;
}
