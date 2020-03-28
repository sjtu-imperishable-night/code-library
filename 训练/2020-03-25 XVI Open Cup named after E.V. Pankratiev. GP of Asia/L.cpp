#include <bits/stdc++.h>

using namespace std;
const int N = 5010;
int _w;

int n, m;
char s[N], t[N];

bool f[N][N], after[N][N];

bool solve() {
	f[1][1] = true;
	for( int i = 1; i <= n; ++i )
		for( int j = 1; j <= m; ++j ) {
			after[i][j] |= after[i][j-1];
			f[i][j] |= after[i][j];
			if( f[i][j] ) {
				if( s[i+1] == t[j+1] ) {
					f[i+1][j+1] = true;
				}
				if( t[j+1] != t[j] ) {
					after[i][j+1] = true;
				}
			}
		}
	return f[n][m];
}

int main() {
	_w = scanf( "%s%s", s+1, t+1 );
	n = (int)strlen(s+1);
	m = (int)strlen(t+1);
	if( s[1] != t[1] ) {
		puts("No");
	} else {
		puts( solve() ? "Yes" : "No" );
	}
	return 0;
}
