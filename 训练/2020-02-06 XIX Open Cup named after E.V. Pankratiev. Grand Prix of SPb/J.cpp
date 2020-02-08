#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int N = 110;
int _w;

int n, k, q, a[N][N];

void question( int idx ) {
	puts("?"), fflush(stdout);
	char tmp[N];
	_w = scanf( "%s", tmp+1 );
	for( int i = 1; i <= n; ++i )
		a[idx][i] = tmp[i] - '0';
}

bool special() {
	int ans[N];
	for( int pos = 1; pos <= n; ++pos ) {
		int c0 = 0, c1 = 0;
		for( int i = 1; i <= q; ++i ) {
			c0 += a[i][pos] == 0;
			c1 += a[i][pos] == 1;
		}
		if( c0 <= 30 ) ans[pos] = 1;
		else if( c1 <= 30 ) ans[pos] = 0;
		else return false;
	}
	printf( "! " );
	for( int i = 1; i <= n; ++i )
		printf( "%d", ans[i] );
	putchar(' ');
	for( int i = 1; i <= n; ++i )
		printf( "%d", ans[i] );
	puts("");
	fflush(stdout);
	return true;
}

vector<int> astr, bstr;
int aa[N], bb[N];

int fc( int *s, int *t ) {
	int cnt = 0;
	for( int i = 1; i <= n; ++i )
		cnt += s[i] != t[i];
	return cnt;
}

bool check() {
	for( int i = 1; i <= q; ++i ) {
		if( fc(aa, a[i]) != k && fc(bb, a[i]) != k )
			return false;
	}
	return true;
}

void fuck( const vector<int> &idx, int *s ) {
	for( int pos = 1; pos <= n; ++pos ) {
		int c0 = 0, c1 = 0;
		for( int i : idx ) {
			c0 += a[i][pos] == 0;
			c1 += a[i][pos] == 1;
		}
		s[pos] = c0 > c1 ? 0 : 1;
	}
}

bool gt( int *s, int *t ) {
	vector<int> svec, tvec;
	for( int i = 1; i <= n; ++i )
		svec.push_back( s[i] );
	for( int i = 1; i <= n; ++i )
		tvec.push_back( t[i] );
	return svec > tvec;
}

vector<pii> before_fuck;

void solve() {
	if( special() ) {
		return;
	} else {
		for( int pos = 1; pos <= n; ++pos ) {
			int c0 = 0, c1 = 0;
			for( int i = 1; i <= q; ++i ) {
				c0 += a[i][pos] == 0;
				c1 += a[i][pos] == 1;
			}
			before_fuck.push_back( pii(abs(c0-c1), pos) );
		}
		sort(before_fuck.begin(), before_fuck.end());
		for( pii info : before_fuck ) {
			int best = info.second;
			astr.clear();
			bstr.clear();
			for( int i = 1; i <= q; ++i )
				if( a[i][best] == 0 ) astr.push_back(i);
				else bstr.push_back(i);
			fuck(astr, aa);
			fuck(bstr, bb);
			if( check() ) {
				int *s = aa, *t = bb;
				if( gt(s, t) ) swap(s, t);
				printf( "! " );
				for( int i = 1; i <= n; ++i )
					printf( "%d", s[i] );
				putchar(' ');
				for( int i = 1; i <= n; ++i )
					printf( "%d", t[i] );
				puts(""), fflush(stdout);
				return;
			} else {
				;
			}
		}
		assert(0);
	}
}

int main() {
	_w = scanf( "%d%d%d", &n, &k, &q );
	for( int i = 1; i <= q; ++i ) question(i);
	solve();
	return 0;
}
