#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int dx[] = {-1, 1, 0, 0, 0, 0};
const int dy[] = {0, 0, -1, 1, 0, 0};
const int dz[] = {0, 0, 0, 0, -1, 1};
int _w;

struct Point {
	int x, y, z;
	Point() {}
	Point( int xx, int yy, int zz ) {
		x = xx, y = yy, z = zz;
	}
	bool operator<( const Point &rhs ) const {
		if( x == rhs.x ) {
			if( y == rhs.y ) {
				return z < rhs.z;
			} else {
				return y < rhs.y;
			}
		} else {
			return x < rhs.x;
		}
	}
};

int a, b, c, n;
ll ans;
set<Point> st;

int main() {
	_w = scanf( "%d%d%d%d", &a, &b, &c, &n );
	ans = 1LL * a * b * 2 + 1LL * a * c * 2 + 1LL * b * c * 2;
	while( n-- ) {
		int x, y, z;
		_w = scanf( "%d%d%d", &x, &y, &z );
		ans += 6;
		for( int d = 0; d < 6; ++d ) {
			int nx = x + dx[d];
			int ny = y + dy[d];
			int nz = z + dz[d];
			if( st.count( Point(nx, ny, nz) ) )
				ans -= 2;
		}
		st.insert( Point(x, y, z) );
		if( x == 0 ) ans -= 2;
		if( x == a-1 ) ans -= 2;
		if( y == 0 ) ans -= 2;
		if( y == b-1 ) ans -= 2;
		if( z == 0 ) ans -= 2;
		if( z == c-1 ) ans -= 2;
	}
	cout << ans << endl;
	return 0;
}
