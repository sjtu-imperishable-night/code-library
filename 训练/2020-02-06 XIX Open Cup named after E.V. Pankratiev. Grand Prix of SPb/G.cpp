#include <bits/stdc++.h>

using namespace std;
int _w;

int n, d;

int main() {
	cin >> n >> d;
	if( n <= 9 ) {
		if( d == n ) {
			printf( "%d%d\n", 1, n-1 );
		} else {
			printf( "%d\n", n );
		}
	} else {
		if( d == 9 ) {
			int cnt = n / 8;
			int rem = n % 8;
			if( rem ) printf( "%d", rem );
			while( cnt-- ) printf( "%d", 8 );
			puts("");
		} else {
			int cnt = n / 9;
			int rem = n % 9;
			if( !rem ) {
				while( cnt-- ) printf( "%d", 9 );
				puts("");
			} else {
				if( d != rem ) {
					printf( "%d", rem );
					while( cnt-- ) printf( "%d", 9 );
					puts("");
				} else {
					if( d != 8 ) {
						printf( "%d%d", d+1, 8 );
						--cnt;
						while( cnt-- ) printf( "%d", 9 );
						puts("");
					} else {
						printf( "%d%d", 1, 7 );
						while( cnt-- ) printf( "%d", 9 );
						puts("");
					}
				}
			}
		}
	}
	return 0;
}
