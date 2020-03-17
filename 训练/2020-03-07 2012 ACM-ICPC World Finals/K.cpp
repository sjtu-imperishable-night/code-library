#include <bits/stdc++.h>

using namespace std;
const int N = 55;
const int M = 2510;
const int INF = 0x3f3f3f3f;
const int V = 10010;
int _w;

int n, an;
vector<int> vec[N], all;
set<int> color[V];
int f[M][N];

int solve() {
	an = int(unique(all.begin(), all.end()) - all.begin());
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	for( int i = 0; i < an; ++i )
		for( int j = 0; j <= n; ++j )
			if( f[i][j] != INF ) {
				int h = all[i];
				for( int c : color[h] ) {
					if( c == j ) {
						int tmp = (int)color[h].size();
						if( color[h].size() == 1 ) --tmp;
						f[i+1][c] = min( f[i+1][c], f[i][j] + tmp );
					} else {
						int tmp = (int)color[h].size();
						if( color[h].count(j) ) --tmp;
						f[i+1][c] = min( f[i+1][c], f[i][j] + tmp );
					}
				}
			}
	int ans = INF;
	for( int j = 0; j <= n; ++j )
		ans = min( ans, f[an][j] );
	--ans;
	ans -= n-1;
	ans *= 2;
	ans += n-1;
	return ans;
}

int main() {
	int kase = 0;
	while( scanf( "%d", &n ) != -1 ) {
		all.clear();
		for( int i = 0; i < V; ++i )
			color[i].clear();
		for( int i = 1; i <= n; ++i ) {
			int h;
			_w = scanf( "%d", &h );
			vec[i].clear();
			while( h-- ) {
				int x;
				_w = scanf( "%d", &x );
				vec[i].push_back(x);
				all.push_back(x);
				color[x].insert(i);
			}
		}
		sort( all.begin(), all.end() );
		printf( "Case %d: %d\n", ++kase, solve() );
	}
	return 0;
}
