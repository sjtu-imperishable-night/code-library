#include <bits/stdc++.h>

using namespace std;
const int N = 100010;
int _w;

int fpow( int a, int b ) {
	int c = 1;
	while(b) {
		if( b & 1 ) c *= a;
		a *= a;
		b >>= 1;
	}
	return c & ((1<<31)-1);
}

int inv( int x ) {
	return fpow(x, (1<<30)-1);
}

int n, a[N], b[N];

void gen() {
	///*
	for( int i = 1; i <= n; ++i )
		a[i] = i * 2 + 1;
	return;
	//*/
	set<int> tmp;
	for( int i = 1; i <= n; ++i ) {
		int x = rand() & ((1<<31)-1);
		x |= 1;
		while( tmp.count(x) ) {
			x = rand() & ((1<<31)-1);
			x |= 1;
		}
		tmp.insert(x);
		a[i] = x;
	}
}

vector<int> vec;

bool ok( int ans ) {
	vector<int> tmp;
	tmp.reserve(n+1);
	for( int i = 1; i <= n; ++i )
		tmp.push_back( (a[i] * ans) & ((1<<31)-1) );
	sort(tmp.begin(), tmp.end());
	for( int i = 1; i <= n/2; ++i ) {
		int x = b[i];
		auto it = lower_bound(tmp.begin(), tmp.end(), x);
		if( it == tmp.end() ) return false;
		if( *it != x ) return false;
	}
	return true;
}

bool check() {
	sort(vec.begin(), vec.end());
	int num = -1, cnt = -1;
	int first = 0;
	for( int i = 1; i < (int)vec.size(); ++i )
		if( vec[i] != vec[i-1] ) {
			int new_num = vec[i-1];
			int new_cnt = i - first;
			if( new_cnt > cnt ) {
				cnt = new_cnt;
				num = new_num;
			}
			first = i;
		}
	int new_num = vec.back();
	int new_cnt = (int)vec.size() - first;
	if( new_cnt > cnt ) {
		cnt = new_cnt;
		num = new_num;
	}
	if( ok(num) ) {
		printf( "%d\n", num );
		exit(0);
	} else {
		return true;
	}
}

void guess( int L, int R ) {
	R = min(R, n);
	for( int i = L; i <= R; ++i ) {
		int iv = inv( a[i] );
		for( int j = 1; j <= n/2; ++j )
			vec.push_back( (b[j] * iv) & ((1<<31)-1) );
	}
}

void solve() {
	const int STEP = 50;
	int L = 1, R = STEP;
	while( vec.empty() || check() ) {
		guess(L, R);
		L += STEP, R += STEP;
	}
}

int main() {
	srand(998244353);
	_w = scanf( "%d", &n );
	gen();
	for( int i = 1; i <= n; ++i )
		printf( "%d ", a[i] );
	puts(""), fflush(stdout);
	for( int i = 1; i <= n/2; ++i )
		_w = scanf( "%d", b+i );
	random_shuffle(a+1, a+n+1);
	solve();
	return 0;
}
