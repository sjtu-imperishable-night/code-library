#include <bits/stdc++.h>

using namespace std;
const int N = 30;
const int M = 1000010;
int _w;

int n, master[M], setid, setsz[M], setsz_backup[M], mx[M];
vector<int> belong[N];
int ans[N][N];

void _solve( int dest ) {
	memset( ans[dest], -1, sizeof ans[dest] );
	for( int i = 1; i <= setid; ++i ) {
		setsz[i] = setsz_backup[i];
		mx[i] = 0;
	}
	queue<int> q;
	ans[dest][dest] = 0;
	q.push(dest);
	while( !q.empty() ) {
		int u = q.front(); q.pop();
		// printf( "dest = %d, u = %d\n", dest, u );
		for( int st : belong[u] ) {
			// printf( "st = %d\n", st );
			mx[st] = max( mx[st], ans[dest][u] );
			--setsz[st];
			if( setsz[st] == 0 ) {
				int v = master[st];
				if( ans[dest][v] == -1 ) {
					ans[dest][v] = mx[st] + 1;
					q.push(v);
				}
			}
		}
	}
}

void solve() {
	for( int dest = 1; dest <= n; ++dest ) {
		_solve(dest);
	}
	for( int i = 1; i <= n; ++i ) {
		for( int j = 1; j <= n; ++j )
			printf( "%d ", ans[j][i] );
		puts("");
	}
}

int main() {
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i ) {
		int cnt;
		_w = scanf( "%d", &cnt );
		while( cnt-- ) {
			++setid;
			master[setid] = i;
			char str[100];
			_w = scanf( "%s", str );
			int len = (int)strlen(str);
			setsz_backup[setid] = len;
			for( int j = 0; j < len; ++j ) {
				int ch = str[j] - 'a' + 1;
				belong[ch].push_back(setid);
			}
		}
	}
	solve();
	return 0;
}
