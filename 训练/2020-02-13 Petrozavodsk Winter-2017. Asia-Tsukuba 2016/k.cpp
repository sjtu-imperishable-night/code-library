#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int _w;

int n;
ll a[100];
int b[100];

ll solve( char *s ) {
	int len = (int)strlen(s);
	for( int i = 0; i < len; ++i )
		if( s[i] == 'B' ) s[i] = 'L';
		else s[i] = 'R';
	int sgn = 1;
	if( s[0] == 'R' ) {
		sgn = -1;
		for( int i = 0; i < len; ++i )
			if( s[i] == 'L' ) s[i] = 'R';
			else s[i] = 'L';
	}
	int first = -1;
	for( int i = 0; i < len; ++i )
		if( s[i] == 'R' ) {
			first = i;
			break;
		}
	if( first == -1 ) {
		ll ans = len;
		ans <<= 40;
		ans *= sgn;
		return ans;
	} else {
		s[len++] = 'L';
		ll ans = first-1;
		ans <<= 40;
		int cnt = 1;
		for( ; first + cnt < len; ++cnt ) {
			int bit = 40 - cnt;
			int ch = s[first + cnt];
			if( ch == 'L' ) {
				ans |= 1LL << bit;
			} else {
				;
			}
		}
		ans *= sgn;
		return ans;
	}
}

map<ll,int> cnt;

int main() {
	_w = scanf( "%d", &n );
	for( int i = 0; i < n; ++i ) {
		char tmp[100];
		_w = scanf( "%s", tmp );
		b[i] = (int)strlen(tmp);
		a[i] = solve(tmp);
	}
	int mid = n/2;
	for( int s = 0; s < (1<<mid); ++s ) {
		ll sum = 0;
		int sumb = 0;
		for( int i = 0; i < mid; ++i )
			if( s & (1<<i) )
				sum += a[i], sumb += b[i];
		cnt[sum] = max( cnt[sum], sumb );
	}
	int ans = 0;
	int large = n-mid;
	for( int s = 0; s < (1<<large); ++s ) {
		ll sum = 0;
		int sumb = 0;
		for( int i = 0; i < large; ++i )
			if( s & (1<<i) )
				sum += a[mid + i], sumb += b[mid + i];
		if( cnt.count(-sum) ) {
			ans = max( ans, sumb + cnt[-sum] );
		}
	}
	printf( "%d\n", ans );
	return 0;
}
