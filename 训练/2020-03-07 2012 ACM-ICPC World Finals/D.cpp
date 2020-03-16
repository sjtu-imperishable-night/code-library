#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 110;
const int M = 100010;
const int B = 131;
const int M1 = 998244353;
const int M2 = 1e9+7;
int _w;

struct Hash {
	int h1, h2;
	
	Hash() {
		h1 = h2 = 0;
	}
	Hash( int h11, int h22 ) {
		h1 = h11, h2 = h22;
	}
	
	Hash operator+( const Hash &rhs ) const {
		int t1 = (h1 + rhs.h1) % M1;
		int t2 = (h2 + rhs.h2) % M2;
		return Hash(t1, t2);
	}
	Hash operator-( const Hash &rhs ) const {
		int t1 = (h1 - rhs.h1 + M1) % M1;
		int t2 = (h2 - rhs.h2 + M2) % M2;
		return Hash(t1, t2);
	}
	void go( int ch ) {
		h1 = int((1LL * h1 * B + ch) % M1);
		h2 = int((1LL * h2 * B + ch) % M2);
	}
	bool operator==( const Hash &rhs ) const {
		return h1 == rhs.h1 && h2 == rhs.h2;
	}
	Hash operator*( const Hash &rhs ) const {
		int t1 = int(1LL * h1 * rhs.h1 % M1);
		int t2 = int(1LL * h2 * rhs.h2 % M2);
		return Hash(t1, t2);
	}
	void print() const {
		printf( "%d %d\n", h1, h2 );
	}
};

Hash pw[M];

void init() {
	pw[0] = Hash(1, 1);
	for( int i = 1; i < M; ++i ) {
		pw[i] = pw[i-1];
		pw[i].go(0);
	}
}

int n, m;
char str[M];
Hash hstr, pf[N][M], sf[N][M];
int len[N];
ll f[N];

ll F( int fuck ) {
	if( len[fuck] != -1 ) return f[fuck];
	
	if( fuck == 0 ) {
		pf[fuck][1] = sf[fuck][1] = Hash('0', '0');
		len[fuck] = 1;
		f[fuck] = pf[fuck][1] == hstr;
		return f[fuck];
	} else if( fuck == 1 ) {
		pf[fuck][1] = sf[fuck][1] = Hash('1', '1');
		len[fuck] = 1;
		f[fuck] = pf[fuck][1] == hstr;
		return f[fuck];
	} else {
		f[fuck] = F(fuck-1) + F(fuck-2);
		len[fuck] = len[fuck-1] + len[fuck-2];
		len[fuck] = min( len[fuck], m );
		for( int i = 1; i <= min( m-1, len[fuck-1] ); ++i ) {
			int j = m-i;
			if( j <= len[fuck-2] ) {
				f[fuck] += hstr == sf[fuck-1][i] * pw[j] + pf[fuck-2][j];
				// hstr.print();
				// (sf[fuck-1][i] * pw[j] + pf[fuck-2][j]).print();
				// puts("???");
			}
		}
		for( int i = 1; i <= len[fuck-1]; ++i )
			pf[fuck][i] = pf[fuck-1][i];
		for( int i = len[fuck-1] + 1; i <= len[fuck]; ++i )
			pf[fuck][i] = pf[fuck-1][len[fuck-1]] * pw[i - len[fuck-1]] + pf[fuck-2][i - len[fuck-1]];
		for( int i = 1; i <= len[fuck-2]; ++i )
			sf[fuck][i] = sf[fuck-2][i];
		for( int i = len[fuck-2] + 1; i <= len[fuck]; ++i )
			sf[fuck][i] = sf[fuck-1][i - len[fuck-2]] * pw[len[fuck-2]] + sf[fuck-2][len[fuck-2]];
		return f[fuck];
	}
}

ll solve() {
	hstr = Hash();
	for( int i = 0; i < m; ++i )
		hstr.go( str[i] );
	memset(len, -1, sizeof len);
	return F(n);
}

int main() {
	init();
	int kase = 0;
	while( ~scanf( "%d", &n ) ) {
		_w = scanf( "%s", str );
		m = (int)strlen(str);
		printf( "Case %d: %lld\n", ++kase, solve() );
	}
	return 0;
}
