#include <bits/stdc++.h>
     
using namespace std;
typedef pair<int,int> pii;
const int N = 100010;
const int INF = 1e9;
const int MOD = 998244353;
const int PHI = MOD-1;
const int A = 3;
const int B = 7;
int _w;
     
int fpow( int a, int b ) {
	int c = 1;
	while(b) {
		if( b & 1 ) c = int(1LL * c * a % MOD);
		a = int(1LL * a * a % MOD);
		b >>= 1;
	}
	return c;
}
     
int inv( int x ) {
	return fpow(x, MOD-2);
}
     
void add_mod( int &a, int b ) {
	a += b;
	a -= a >= MOD ? MOD : 0;
}
     
void sub_mod( int &a, int b ) {
	a -= b;
	a += a < 0 ? MOD : 0;
}
     
int gcd( int a, int b ) {
	return b ? gcd(b, a%b) : a;
}
     
struct Line {
	int a, b, c;
    	
	Line() {}
	Line( int aa, int bb, int cc ) {
		a = aa, b = bb, c = cc;
		int g = gcd(gcd(a, b), c);
		a /= g, b /= g, c /= g;
		if( a < 0 ) {
			a = -a;
			b = -b;
			c = -c;
		} else if( a == 0 ) {
			if( b < 0 ) {
				b = -b;
				c = -c;
			} else if( b == 0 ) {
				if( c < 0 ) {
					c = -c;
				}
			}
		}
	}
    	
	bool operator<( const Line &rhs ) const {
		if( a == rhs.a ) {
			if( b == rhs.b ) {
				return c > rhs.c;
			} else {
				return b > rhs.b;
			}
		} else {
			return a > rhs.a;
		}
	}
};
     
int n;
     
int dengbi( int q, int begin, int end ) {
	int now = fpow(q, end+1);
	sub_mod( now, fpow(q, begin) );
	return int(1LL * now * inv(q-1) % MOD);
}
     
int calc_rect( pii rect[2] ) {
	int xl = min( rect[0].first, rect[1].first );
	int xr = max( rect[0].first, rect[1].first );
	int yl = min( rect[0].second, rect[1].second );
	int yr = max( rect[0].second, rect[1].second );
	return int(1LL * dengbi(A, xl+INF, xr-1+INF) * dengbi(B, yl+INF, yr-1+INF) % MOD);
}
     
int calc( pii rect[N][2] ) {
	int sum = 0;
	for( int i = 1; i <= n; ++i )
		add_mod( sum, calc_rect( rect[i] ) );
	return sum;
}
     
pii rect[N][2], test[N][2];
int rect_val;
     
bool check() {
	return rect_val == calc( test );
}
     
vector<Line> ans;
     
void solve_heng() {
	int minx = INF;
	int maxx = -INF;
	for( int i = 1; i <= n; ++i )
		for( int j = 0; j < 2; ++j ) {
			minx = min( minx, rect[i][j].first );
			maxx = max( maxx, rect[i][j].first );
		}
	for( int i = 1; i <= n; ++i )
		for( int j = 0; j < 2; ++j ) {
			pii now = rect[i][j];
			now.first = minx + maxx - now.first;
			test[i][j] = now;
		}
	if( check() ) {
		ans.push_back( Line(2, 0, minx + maxx) );
	}
}
     
void solve_shu() {
	int miny = INF;
	int maxy = -INF;
	for( int i = 1; i <= n; ++i )
		for( int j = 0; j < 2; ++j ) {
			miny = min( miny, rect[i][j].second );
			maxy = max( maxy, rect[i][j].second );
		}
	for( int i = 1; i <= n; ++i )
		for( int j = 0; j < 2; ++j ) {
			pii now = rect[i][j];
			now.second = miny + maxy - now.second;
			test[i][j] = now;
		}
	if( check() ) {
		ans.push_back( Line(0, 2, miny + maxy) );
	}
}
     
void solve_plus() {
	int min_plus = INF;
	int max_plus = -INF;
	for( int i = 1; i <= n; ++i )
		for( int j = 0; j < 2; ++j ) {
			int tmp = rect[i][j].first + rect[i][j].second;
			min_plus = min( min_plus, tmp );
			max_plus = max( max_plus, tmp );
		}
	for( int i = 1; i <= n; ++i )
		for( int j = 0; j < 2; ++j ) {
			pii now = rect[i][j];
			int minus = now.first - now.second;
			int plus = min_plus + max_plus - now.first - now.second;
			now.first = (minus + plus) / 2;
			now.second = (plus - minus) / 2;
			test[i][j] = now;
		}
	if( check() ) {
		ans.push_back( Line(2, 2, min_plus + max_plus) );
	}
}
     
void solve_minus() {
	int min_minus = INF;
	int max_minus = -INF;
	for( int i = 1; i <= n; ++i )
		for( int j = 0; j < 2; ++j ) {
			int tmp = rect[i][j].first - rect[i][j].second;
			min_minus = min( min_minus, tmp );
			max_minus = max( max_minus, tmp );
		}
	for( int i = 1; i <= n; ++i )
		for( int j = 0; j < 2; ++j ) {
			pii now = rect[i][j];
			int plus = now.first + now.second;
			int minus = min_minus + max_minus - (now.first - now.second);
			now.first = (minus + plus) / 2;
			now.second = (plus - minus) / 2;
			test[i][j] = now;
		}
	if( check() ) {
		ans.push_back( Line(2, -2, min_minus + max_minus) );
	}
}
     
void solve() {
	ans.clear();
	rect_val = calc( rect );
	solve_heng();
	solve_shu();
	solve_plus();
	for( int i = 1; i <= n; ++i )
		swap( rect[i][0].second, rect[i][1].second );
	solve_minus();
	sort( ans.begin(), ans.end() );
	printf( "%d\n", (int)ans.size() );
	for( int i = 0; i < (int)ans.size(); ++i )
		if( i == 0 ) printf( "%d %d %d", ans[i].a, ans[i].b, ans[i].c );
		else printf( " %d %d %d", ans[i].a, ans[i].b, ans[i].c );
	puts("");
}
     
int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		_w = scanf( "%d", &n );
		for( int i = 1; i <= n; ++i ) {
			_w = scanf( "%d%d", &rect[i][0].first, &rect[i][0].second );
			_w = scanf( "%d%d", &rect[i][1].first, &rect[i][1].second );
		}
		solve();
	}
	return 0;
}
