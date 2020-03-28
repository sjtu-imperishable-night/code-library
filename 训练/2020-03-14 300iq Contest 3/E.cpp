#include <bits/stdc++.h>

using namespace std;
const int N = 530010;
int _w;

int n, a[N], s[N], cnt[N], U;
vector<int> vec[N];

void prelude( int k ) {
	static int tmp[N];
	
	for( int L = 0; L <= n; L += U ) {
		int i = L / U;
		vec[i].resize(U);
		for( int j = 0; j < U; ++j ) {
			vec[i][j] = 0;
			tmp[j] = a[L+j];
		}
		int sum = 0;
		for( int j = 0; j < (1<<k); ++j )
			sum += tmp[j];
		for( int j = 0; j < U; ++j ) {
			vec[i][j] = sum;
			sum -= tmp[j];
			sum += tmp[(j + (1<<k)) & (U-1)];
			if( i ) vec[i][j] += vec[i-1][j];
		}
	}
}

inline int fuck( int L, int R, int l, int r, int begin ) {
	L = max(L, l);
	R = min(R, r);
	if( L <= R ) {
		return cnt[begin+R] - cnt[begin+L-1];
	} else {
		return 0;
	}
}

inline int _check( int i, int L, int R, int l, int k ) {
	int begin = i << (k+1);
	int r = (l + (1<<k) - 1) & (U-1);
	if( l <= r ) {
		L = max(L, l);
		R = min(R, r);
		if( L <= R ) {
			return cnt[begin+R] - cnt[begin+L-1];
		} else {
			return 0;
		}
	} else {
		return fuck(L, R, l, U-1, begin) + fuck(L, R, 0, r, begin);
	}
}

inline bool check( int L, int R, int l, int k ) {
	int ri = (R>>(k+1)) - 1;
	int li = (L>>(k+1));
	int ans = 0;
	if( li <= ri ) {
		ans = vec[ri][l] - vec[li][l];
		L &= U-1;
		R &= U-1;
		ans += _check(li, L, U-1, l, k);
		ans += _check(ri+1, 0, R, l, k);
		return ans & 1;
	} else {
		L &= U-1;
		R &= U-1;
		ans = _check(li, L, R, l, k);
		return ans & 1;
	}
}

void solve() {
	for( int k = 0; (1<<k) <= n; ++k ) {
		U = 1<<(k+1);
		prelude(k);
		for( int x = 1; x <= n; ++x ) {
			if( x+1 <= (1<<k) ) continue;
			for( int i = 0; (x+1)*i <= n; ++i ) {
				int begin = (x+1)*i;
				int l = (begin + (1<<k)) & (U-1);
				if( check(begin, min(begin+x, n), l, k) )
					s[x] ^= 1<<k;
			}
		}
	}
	for( int i = 1; i <= n; ++i ) {
		if( i != 1 ) putchar(' ');
		printf( "%s", s[i] ? "Alice" : "Bob" );
	}
	puts("");
}

int main() {
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i ) {
		int x;
		_w = scanf( "%d", &x );
		++a[x];
		a[x] &= 1;
	}
	for( int i = 1; i <= n; ++i )
		cnt[i] = cnt[i-1] + a[i];
	solve();
	return 0;
}
