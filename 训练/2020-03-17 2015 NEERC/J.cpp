#include <bits/stdc++.h>

using namespace std;
const int N = 1010;
int _w;

int n;
char str[N];

int query() {
	puts(str+1);
	fflush(stdout);
	int ans;
	_w = scanf( "%d", &ans );
	if( ans == n ) exit(0);
	return ans;
}

void solve1() {
	while( query() != n/2 ) {
		for( int i = 1; i <= n; ++i )
			if( rand() & 1 ) str[i] = '1';
			else str[i] = '0';
	}
}

int rela[N];

int query_rev( int p, int q ) {
	str[p] = '0' + '1' - str[p];
	str[q] = '0' + '1' - str[q];
	int ans = query();
	str[p] = '0' + '1' - str[p];
	str[q] = '0' + '1' - str[q];
	return ans;
}

int ok[N];
char output[N];

bool test( int state ) {
	ok[1] = state;
	for( int i = 1; i < n; ++i ) {
		ok[i+1] = ok[i] ^ rela[i];
	}
	for( int i = 1; i <= n; ++i )
		if( ok[i] ) {
			output[i] = str[i];
		} else {
			output[i] = '0' + '1' - str[i];
		}
	output[n+1] = 0;
	puts(output+1);
	fflush(stdout);
	int ans;
	_w = scanf( "%d", &ans );
	return ans == n;
}

void solve2() {
	for( int i = 1; i < n; ++i ) {
		if( query_rev(i, i+1) == n/2 ) {
			rela[i] = 1;
		} else {
			rela[i] = 0;
		}
	}
	if( test(1) ) return;
	else test(0);
}

int main() {
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i )
		if( rand() & 1 ) str[i] = '1';
		else str[i] = '0';
	str[n+1] = 0;
	solve1();
	solve2();
	return 0;
}
