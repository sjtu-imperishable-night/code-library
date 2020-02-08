#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int INF = 1e9;
const int N = 20;
int _w;

ll gcd( ll a, ll b ) {
	return b ? gcd(b, a%b) : a;
}

struct fraction {
	ll up, down;
	
	fraction() {
		up = 0, down = 1;
	}
	fraction( int x ) {
		up = x, down = 1;
	}
	fraction( ll _up, ll _down ) {
		up = _up, down = _down;
		ll g = gcd(abs(up), down);
		up /= g, down /= g;
	}

	void print() {
		printf( "%lld/%lld", up, down );
	}
};

fraction operator+( const fraction &lhs, const fraction &rhs ) {
	ll a = lhs.down;
	ll b = lhs.up;
	ll c = rhs.down;
	ll d = rhs.up;
	ll down = a * c;
	ll up = b * c + a * d;
	return fraction(up, down);
}

fraction operator-( const fraction &rhs ) {
	return fraction(-rhs.up, rhs.down);
}

fraction operator-( const fraction &lhs, const fraction &rhs ) {
	return lhs + (-rhs);
}

bool operator==( const fraction &lhs, const fraction &rhs ) {
	return lhs.up == rhs.up && lhs.down == rhs.down;
}

bool operator!=( const fraction &lhs, const fraction &rhs ) {
	return !(lhs == rhs);
}

fraction operator*( const fraction &lhs, const fraction &rhs ) {
	return fraction(lhs.up * rhs.up, lhs.down * rhs.down);
}

fraction operator/( const fraction &lhs, const fraction &rhs ) {
	ll up = rhs.down;
	ll down = rhs.up;
	if( down < 0 ) {
		down = -down;
		up = -up;
	}
	return fraction(up * lhs.up, down * lhs.down);
}

int n, m, a[N][N];

int read() {
	char str[100];
	_w = scanf( "%s", str );
	if( str[0] == '?' ) {
		return INF;
	} else {
		int x;
		_w = sscanf( str, "%d", &x );
		return x;
	}
}

void solven1() {
	int cnt = 0;
	for( int i = 1; i <= m; ++i )
		cnt += a[1][i] != INF;
	if( cnt == 0 ) {
		puts("Multiple");
		for( int i = 1; i <= m; ++i )
			printf( "%d/1 ", i );
		puts("");
		puts("and");
		for( int i = 1; i <= m; ++i )
			printf( "%d/1 ", -i );
		puts("");
	} else if( cnt == 1 ) {
		int pos = -1;
		for( int i = 1; i <= m; ++i )
			if( a[1][i] != INF ) {
				pos = i;
				break;
			}
		puts("Multiple");
		for( int i = pos+1; i <= m; ++i )
			a[1][i] = a[1][i-1] + 1;
		for( int i = pos-1; i >= 1; --i )
			a[1][i] = a[1][i+1] - 1;
		for( int i = 1; i <= m; ++i )
			printf( "%d/1 ", a[1][i] );
		puts("");
		puts("and");
		for( int i = pos+1; i <= m; ++i )
			a[1][i] = a[1][i-1] + 2;
		for( int i = pos-1; i >= 1; --i )
			a[1][i] = a[1][i+1] - 2;
		for( int i = 1; i <= m; ++i )
			printf( "%d/1 ", a[1][i] );
		puts("");
	} else {
		int p1, p2;
		for( int i = 1; i <= m; ++i )
			if( a[1][i] != INF ) {
				p1 = i;
				break;
			}
		for( int i = p1+1; i <= m; ++i )
			if( a[1][i] != INF ) {
				p2 = i;
				break;
			}
		fraction ans[N];
		ans[p1] = a[1][p1];
		ans[p2] = a[1][p2];
		fraction d = (ans[p2] - ans[p1]) / (p2 - p1);
		for( int i = p1+1; i <= m; ++i )
			ans[i] = ans[i-1] + d;
		for( int i = p1-1; i >= 1; --i )
			ans[i] = ans[i+1] - d;
		for( int i = 1; i <= m; ++i )
			if( a[1][i] != INF ) {
				if( a[1][i] != ans[i] ) {
					puts("None");
					return;
				}
			}
		puts("Unique");
		for( int i = 1; i <= m; ++i )
			ans[i].print(), putchar(' ');
		puts("");
	}
}

void solvem1() {
	int cnt = 0;
	for( int i = 1; i <= m; ++i )
		cnt += a[1][i] != INF;
	if( cnt == 0 ) {
		puts("Multiple");
		for( int i = 1; i <= m; ++i )
			printf( "%d/1\n", i );
		puts("and");
		for( int i = 1; i <= m; ++i )
			printf( "%d/1\n", -i );
	} else if( cnt == 1 ) {
		int pos = -1;
		for( int i = 1; i <= m; ++i )
			if( a[1][i] != INF ) {
				pos = i;
				break;
			}
		puts("Multiple");
		for( int i = pos+1; i <= m; ++i )
			a[1][i] = a[1][i-1] + 1;
		for( int i = pos-1; i >= 1; --i )
			a[1][i] = a[1][i+1] - 1;
		for( int i = 1; i <= m; ++i )
			printf( "%d/1\n", a[1][i] );
		puts("and");
		for( int i = pos+1; i <= m; ++i )
			a[1][i] = a[1][i-1] + 2;
		for( int i = pos-1; i >= 1; --i )
			a[1][i] = a[1][i+1] - 2;
		for( int i = 1; i <= m; ++i )
			printf( "%d/1\n", a[1][i] );
	} else {
		int p1, p2;
		for( int i = 1; i <= m; ++i )
			if( a[1][i] != INF ) {
				p1 = i;
				break;
			}
		for( int i = p1+1; i <= m; ++i )
			if( a[1][i] != INF ) {
				p2 = i;
				break;
			}
		fraction ans[N];
		ans[p1] = a[1][p1];
		ans[p2] = a[1][p2];
		fraction d = (ans[p2] - ans[p1]) / (p2 - p1);
		for( int i = p1+1; i <= m; ++i )
			ans[i] = ans[i-1] + d;
		for( int i = p1-1; i >= 1; --i )
			ans[i] = ans[i+1] - d;
		for( int i = 1; i <= m; ++i )
			if( a[1][i] != INF ) {
				if( a[1][i] != ans[i] ) {
					puts("None");
					return;
				}
			}
		puts("Unique");
		for( int i = 1; i <= m; ++i )
			ans[i].print(), putchar('\n');
	}
}

struct EQ {
	fraction eq[5];
	
	fraction &operator[]( int idx ) {
		return eq[idx];
	}
	const fraction &operator[]( int idx ) const {
		return eq[idx];
	}
};

EQ operator+( const EQ &lhs, const EQ &rhs ) {
	EQ ans;
	for( int i = 0; i < 5; ++i )
		ans[i] = lhs[i] + rhs[i];
	return ans;
}

EQ operator-( const EQ &rhs ) {
	EQ ans;
	for( int i = 0; i < 5; ++i )
		ans[i] = -rhs[i];
	return ans;
}

EQ operator-( const EQ &lhs, const EQ &rhs ) {
	EQ ans;
	for( int i = 0; i < 5; ++i )
		ans[i] = lhs[i] - rhs[i];
	return ans;
}

EQ operator/( const EQ &lhs, const fraction &rhs ) {
	EQ ans;
	for( int i = 0; i < 5; ++i )
		ans[i] = lhs[i] / rhs;
	return ans;
}

EQ operator*( const EQ &lhs, const fraction &rhs ) {
	EQ ans;
	for( int i = 0; i < 5; ++i )
		ans[i] = lhs[i] * rhs;
	return ans;
}

fraction operator*( const EQ &lhs, const EQ &rhs ) {
	fraction ans;
	for( int i = 1; i <= 4; ++i )
		ans = ans + lhs[i] * rhs[i];
	return ans;
}

EQ eq_table[N][N];

void init_eq() {
	eq_table[1][1][1] = 1;
	eq_table[1][2][2] = 1;
	eq_table[2][1][3] = 1;
	eq_table[2][2][4] = 1;
	for( int i = 1; i <= 2; ++i ) {
		EQ d = eq_table[i][2] - eq_table[i][1];
		for( int j = 3; j <= m; ++j )
			eq_table[i][j] = eq_table[i][j-1] + d;
	}
	for( int j = 1; j <= m; ++j ) {
		EQ d = eq_table[2][j] - eq_table[1][j];
		for( int i = 3; i <= n; ++i )
			eq_table[i][j] = eq_table[i-1][j] + d;
	}
}

EQ equa[N*N];
int eq_cnt = 0;

void add_eq( int x, int y, int num ) {
	++eq_cnt;
	equa[eq_cnt] = eq_table[x][y];
	equa[eq_cnt][0] = num;
}

vector<int> pivot;
EQ ans;

bool gauss() {
	int line = 1;
	for( int i = 1; i <= 4; ++i ) {
		int tmp = -1;
		for( int j = line; j <= eq_cnt; ++j )
			if( equa[j][i] != 0 ) {
				tmp = j;
				break;
			}
		if( tmp == -1 ) {
			;
		} else {
			swap( equa[line], equa[tmp] );
			for( int j = line+1; j <= eq_cnt; ++j ) {
				equa[j] = equa[j] - equa[line] / equa[line][i] * equa[j][i];
			}
			pivot.push_back(i);
			++line;
		}
	}
	for( int i = line; i <= eq_cnt; ++i )
		if( equa[i][0] != 0 )
			return false;
	return true;
}

void calc() {
	for( int line = eq_cnt; line >= 1; --line ) {
		for( int x : pivot ) {
			if( equa[line][x] != 0 ) {
				ans[x] = equa[line][0];
				for( int i = x+1; i <= 4; ++i )
					ans[x] = ans[x] - ans[i] * equa[line][i];
				ans[x] = ans[x] / equa[line][x];
				break;
			}
		}
	}
}

void solve() {
	init_eq();
	for( int i = 1; i <= n; ++i )
		for( int j = 1; j <= m; ++j )
			if( a[i][j] != INF )
				add_eq(i, j, a[i][j]);
	if( !gauss() ) {
		puts("None");
	} else {
		if( pivot.size() == 4 ) {
			puts("Unique");
			calc();
			for( int i = 1; i <= n; ++i, puts("") )
				for( int j = 1; j <= m; ++j )
					(eq_table[i][j] * ans).print(), putchar(' ');
		} else {
			puts("Multiple");
			for( int i = 1; i <= 4; ++i )
				ans[i] = 0;
			calc();
			for( int i = 1; i <= n; ++i, puts("") )
				for( int j = 1; j <= m; ++j )
					(eq_table[i][j] * ans).print(), putchar(' ');
			puts("and");
			for( int i = 1; i <= 4; ++i )
				ans[i] = 1;
			calc();
			for( int i = 1; i <= n; ++i, puts("") )
				for( int j = 1; j <= m; ++j )
					(eq_table[i][j] * ans).print(), putchar(' ');
		}
	}
}

int main() {
	cin >> n >> m;
	for( int i = 1; i <= n; ++i )
		for( int j = 1; j <= m; ++j )
			a[i][j] = read();
	if( n == 1 && m == 1 ) {
		if( a[1][1] == INF ) {
			puts("Multiple");
			puts("1/1");
			puts("and");
			puts("2/1");
		} else {
			puts("Unique");
			printf( "%d/1\n", a[1][1] );
		}
	} else if( n == 1 ) {
		solven1();
	} else if( m == 1 ) {
		swap(n, m);
		for( int i = 1; i <= m; ++i )
			a[1][i] = a[i][1];
		solvem1();
	} else {
		solve();
	}
	return 0;
}
