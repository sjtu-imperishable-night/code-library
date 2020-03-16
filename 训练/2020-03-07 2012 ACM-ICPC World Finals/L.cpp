#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 100010;
int _w;

int n, m;
ll a[N], b[N];
multiset<ll, greater<ll> > sa, sb;

bool solve1() {
	sa.clear();
	sb.clear();
	
	for( int i = 1; i <= n; ++i )
		sa.insert( a[i] );
	for( int i = 1; i <= m; ++i )
		sb.insert( b[i] );
	
	int player = 1;
	bool first = true;
	while( sa.size() && sb.size() ) {
		if( player == 1 ) {
			if( first ) {
				if( sa.size() == 1 ) {
					return false;
				} else {
					ll tmp = *sa.begin();
					sa.erase( sa.begin() );
					tmp += *sa.begin();
					sa.erase( sa.begin() );
					sa.insert( tmp );
				}
			} else {
				if( *sa.begin() > *sb.begin() ) {
					sb.erase( sb.begin() );
				} else {
					if( sa.size() == 1 ) {
						;
					} else {
						ll tmp = *sa.begin();
						sa.erase( sa.begin() );
						tmp += *sa.begin();
						sa.erase( sa.begin() );
						sa.insert( tmp );
					}
				}
			}
		} else if( player == 2 ) {
			if( *sb.begin() > *sa.begin() ) {
				sa.erase( sa.begin() );
			} else {
				if( sb.size() == 1 ) {
					;
				} else {
					ll tmp = *sb.begin();
					sb.erase( sb.begin() );
					tmp += *sb.begin();
					sb.erase( sb.begin() );
					sb.insert( tmp );
				}
			}
		}
		player = 3 - player;
		first = false;
	}
	return sa.size() ? true : false;
}

bool solve2() {
	sa.clear();
	sb.clear();
	
	for( int i = 1; i <= n; ++i )
		sa.insert( a[i] );
	for( int i = 1; i <= m; ++i )
		sb.insert( b[i] );
	
	int player = 1;
	bool first = true;
	while( sa.size() && sb.size() ) {
		if( player == 1 ) {
			if( first ) {
				if( *sa.begin() > *sb.begin() ) {
					sb.erase( sb.begin() );
				} else {
					return false;
				}
			} else {
				if( *sa.begin() > *sb.begin() ) {
					sb.erase( sb.begin() );
				} else {
					if( sa.size() == 1 ) {
						;
					} else {
						ll tmp = *sa.begin();
						sa.erase( sa.begin() );
						tmp += *sa.begin();
						sa.erase( sa.begin() );
						sa.insert( tmp );
					}
				}
			}
		} else if( player == 2 ) {
			if( *sb.begin() > *sa.begin() ) {
				sa.erase( sa.begin() );
			} else {
				if( sb.size() == 1 ) {
					;
				} else {
					ll tmp = *sb.begin();
					sb.erase( sb.begin() );
					tmp += *sb.begin();
					sb.erase( sb.begin() );
					sb.insert( tmp );
				}
			}
		}
		player = 3 - player;
		first = false;
	}
	return sa.size() ? true : false;
}

int main() {
	int kase = 0;
	while( scanf( "%d%d", &n, &m ) != -1 ) {
		for( int i = 1; i <= n; ++i )
			_w = scanf( "%lld", a+i );
		for( int i = 1; i <= m; ++i )
			_w = scanf( "%lld", b+i );
		printf( "Case %d: ", ++kase );
		puts( solve1() || solve2() ? "Takeover Incorporated" : "Buyout Limited" );
	}
	return 0;
}
