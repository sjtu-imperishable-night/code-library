#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int N = 4010;
const int B = 19260817;
const int M1 = 998244353;
const int M2 = 1e9+7;
int _w;

int sn, tn;
char s[N], t[N];
int hashs[N][26], hasht[N][26];
int hnums[N][2], hnumt[N][2];

inline int append( int h, int c, int mod ) {
	return int((1LL * h * B + c) % mod);
}

void init( char *a, int n, int hasha[N][26], int hnum[N][2] ) {
	for( int i = 1; i <= n; ++i ) {
		for( int j = 0; j < 26; ++j )
			hasha[i][j] = hasha[i-1][j];
		++hasha[i][a[i] - 'a'];
		int h1 = 0;
		int h2 = 0;
		for( int j = 0; j < 26; ++j ) {
			h1 = append(h1, hasha[i][j], M1);
			h2 = append(h2, hasha[i][j], M2);
		}
		hnum[i][0] = h1;
		hnum[i][1] = h2;
	}
}

pii hsh( int h[N][2], int l, int r ) {
	int h1 = (h[r][0] - h[l][0] + M1) % M1;
	int h2 = (h[r][1] - h[l][1] + M2) % M2;
	return pii(h1, h2);
}

bool solve( int len ) {
	set<pii> st;
	for( int i = len; i <= sn; ++i )
		st.insert( hsh(hnums, i-len, i) );
	for( int j = len; j <= tn; ++j )
		if( st.count( hsh(hnumt, j-len, j) ) )
			return true;
	return false;
}

int main() {
	_w = scanf( "%s%s", s+1, t+1 );
	sn = (int)strlen(s+1);
	tn = (int)strlen(t+1);
	init(s, sn, hashs, hnums);
	init(t, tn, hasht, hnumt);
	int len = min(sn, tn);
	for( int i = len; i >= 1; --i ) {
		if( solve(i) ) {
			printf( "%d\n", i );
			return 0;
		}
	}
	puts("0");
	return 0;
}
