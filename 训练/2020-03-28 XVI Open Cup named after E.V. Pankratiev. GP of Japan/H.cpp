#include <bits/stdc++.h>

using namespace std;
const int N = 310;
const double EPS = 1e-8;
int _w;

int dcmp( double x ) {
	if( fabs(x) < EPS ) return 0;
	else return x < 0 ? -1 : 1;
}

double dist( double x1, double y1, double x2, double y2 ) {
	double dx = x1 - x2;
	double dy = y1 - y2;
	return sqrt(dx * dx + dy * dy);
}

int n;
double xl[N], yl[N], xr[N], yr[N], g[N][N];
double ans;

namespace KM {
	int left[N], right[N];
	int visl[N], visr[N];
	double lx[N], ly[N], slack[N];

	bool augment( int u ) {
		visl[u] = 1;
		for( int v = 1; v <= n; ++v ) {
			if( visr[v] ) continue;
			double slk = lx[u] + ly[v] - g[u][v];
			if( dcmp(slk) == 0 ) {
				visr[v] = 1;
				if( !right[v] || augment( right[v] ) ) {
					right[v] = u, left[u] = v;
					return true;
				}
			} else {
				slack[v] = min( slack[v], slk );
			}
		}
		return false;
	}
	double solve() {
		for( int i = 1; i <= n; ++i )
			lx[i] = -1e100;
		for( int i = 1; i <= n; ++i )
			for( int j = 1; j <= n; ++j )
				lx[i] = max( lx[i], g[i][j] );
		for( int i = 1; i <= n; ++i ) {
			for( int j = 1; j <= n; ++j ) {
				visl[j] = visr[j] = 0;
				slack[j] = 1e100;
			}
			if( augment(i) ) continue;
			while(1) {
				double d = 1e100;
				int u;
				for( int j = 1; j <= n; ++j )
					if( !visr[j] )
						d = min( d, slack[j] );
				for( int j = 1; j <= n; ++j ) {
					if( visl[j] ) lx[j] -= d;
					if( visr[j] ) ly[j] += d;
					else {
						slack[j] -= d;
						if( dcmp(slack[j]) == 0 ) u = j;
					}
				}
				if( !right[u] ) break;
				visr[u] = 1, visl[right[u]] = 1;
				u = right[u];
				for( int j = 1; j <= n; ++j )
					slack[j] = min( slack[j], lx[u] + ly[j] - g[u][j] );
			}
			for( int j = 1; j <= n; ++j )
				visl[j] = visr[j] = 0;
			augment(i);
		}
		double ans = 0;
		for( int i = 1; i <= n; ++i )
			ans += lx[i] + ly[i];
		return ans;
	}
}

int main() {
	_w = scanf( "%d", &n );
	int nm, sl;
	_w = scanf( "%d%d", &nm, &sl );
	for( int i = 1; i <= n; ++i ) {
		_w = scanf( "%lf%lf%lf%lf", xl+i, yl+i, xr+i, yr+i );
		ans += dist( xl[i], yl[i], xr[i], yr[i] );
	}
	for( int i = 1; i <= n; ++i )
		for( int j = 1; j <= n; ++j )
			g[i][j] = -dist( xl[i], yl[i], xr[j], yr[j] );
	ans += -KM::solve();
	printf( "%.20lf\n", ans );
	return 0;
}
