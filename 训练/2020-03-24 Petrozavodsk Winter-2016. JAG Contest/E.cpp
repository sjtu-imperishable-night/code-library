#include <bits/stdc++.h>

using namespace std;
const int N = 110;
const int L = 1100;
int _w;

int n, l;
char str[L];

struct Per {
	int a[N*N];
	
	Per() {
		for( int i = 1; i <= n*n; ++i )
			a[i] = i;
	}
	
	int *operator[]( int line ) {
		return a + ((line-1) * n + 1) - 1;
	}
	
	void rotate( char dir, int id ) {
		// printf( "dir = %c, id = %d\n", dir, id );
		if( dir == 'R' ) {
			int tmp = (*this)[id][n];
			for( int j = n-1; j >= 1; --j )
				(*this)[id][j+1] = (*this)[id][j];
			(*this)[id][1] = tmp;
		} else if( dir == 'L' ) {
			int tmp = (*this)[id][1];
			for( int j = 2; j <= n; ++j )
				(*this)[id][j-1] = (*this)[id][j];
			(*this)[id][n] = tmp;
		} else if( dir == 'D' ) {
			int tmp = (*this)[n][id];
			for( int i = n-1; i >= 1; --i )
				(*this)[i+1][id] = (*this)[i][id];
			(*this)[1][id] = tmp;
		} else if( dir == 'U' ) {
			int tmp = (*this)[1][id];
			for( int i = 2; i <= n; ++i )
				(*this)[i-1][id] = (*this)[i][id];
			(*this)[n][id] = tmp;
		} else {
			assert(0);
		}
		// puts("finish rotate");
	}
	
	void print() {
		for( int i = 1; i <= n; ++i, puts("") )
			for( int j = 1; j <= n; ++j )
				printf( "%d ", (*this)[i][j] );
	}
};

Per mul( Per a, Per b ) {
	Per c;
	for( int i = 1; i <= n*n; ++i )
		c.a[i] = a.a[b.a[i]];
	return c;
}

Per fpow( Per a, int b ) {
	// a.print();
	// printf( "b = %d\n", b );
	Per c;
	while(b) {
		if( b & 1 ) c = mul(c, a);
		a = mul(a, a);
		b >>= 1;
	}
	return c;
}

int read_num( int &pos ) {
	int x = 0;
	while( isdigit( str[pos] ) ) {
		x = x * 10 + str[pos] - '0';
		++pos;
	}
	return x;
}

Per parse( int &pos ) {
	if( str[pos] == '(' ) {
		++pos;
		Per per;
		while( str[pos] != ')' ) {
			per = mul(per, parse(pos));
		}
		++pos;
		int repeat = read_num(pos);
		// per.print();
		return fpow(per, repeat);
	} else {
		assert( isupper( str[pos] ) );
		char ch = str[pos];
		++pos;
		int id = read_num(pos);
		Per per;
		per.rotate(ch, id);
		return per;
	}
}

void solve() {
	int pos = 1;
	Per per;
	while( pos < l ) {
		per = mul(per, parse(pos));
	}
	for( int i = 1; i <= n; ++i, puts("") )
		for( int j = 1; j <= n; ++j )
			printf( "%d ", per[i][j] );
}

int main() {
	_w = scanf( "%d%d", &n, &l );
	_w = scanf( "%s", str+1 );
	solve();
	return 0;
}
