#include <bits/stdc++.h>

using namespace std;
const int N = 100;
int _w;

int n, k, sum;
queue<int> prob[N];

int main() {
	freopen("easy.in", "r", stdin);
	freopen("easy.out", "w", stdout);
	_w = scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; ++i ) {
		int cnt;
		_w = scanf( "%d", &cnt );
		while( cnt-- ) {
			int x;
			_w = scanf( "%d", &x );
			prob[i].push(x);
		}
	}
	for( int fuck = 0; fuck < 1000; ++fuck ) {
		for( int i = 1; i <= n; ++i )
			if( !prob[i].empty() ) {
				int now = prob[i].front();
				prob[i].pop();
				if( now >= sum ) {
					sum += now;
					--k;
					if( !k ) {
						printf( "%d\n", sum );
						return 0;
					}
				}
			} else {
				int now = 50;
				if( now >= sum ) {
					sum += now;
					--k;
					if( !k ) {
						printf( "%d\n", sum );
						return 0;
					}
				}
			}
	}
	sum += k * 50;
	printf( "%d\n", sum );
	return 0;
}
