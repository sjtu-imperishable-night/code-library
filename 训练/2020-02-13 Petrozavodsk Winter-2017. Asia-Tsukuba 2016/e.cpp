#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int,ll> pii;
const char SYMB[] = {'0', '1', '+', '-', '=', '*', '(', ')'};
int _w;

int n;
char s[100], t[100];
vector<int> ch;
bool used[8];

void init_ch() {
	set<int> st;
	for( int i = 0; i < n; ++i ) {
		int c = s[i];
		if( islower(c) || isupper(c) ) {
			st.insert(c);
		}
	}
	for( int c : st )
		ch.push_back(c);
}

int ans = 0;
pii dpE[32][32], dpT[32][32], dpF[32][32];

pii checkE( int L, int R );

pii checkN( int L, int R ) {
	if( L > R ) {
		return pii(false, 0);
	} else if( L == R ) {
		return pii(t[L] == '0' || t[L] == '1', t[L] - '0');
	} else {
		if( t[L] != '1' ) return pii(false, 0);
		ll num = 1;
		for( int i = L+1; i <= R; ++i )
			if( t[i] != '0' && t[i] != '1' ) {
				return pii(false, 0);
			} else {
				num <<= 1;
				num |= t[i] - '0';
			}
		return pii(true, num);
	}
}

pii checkF( int L, int R ) {
	if( L > R ) {
		return pii(false, 0);
	}
	pii &now = dpF[L][R];
	if( now.first != -1 ) return now;
	now = checkN(L, R);
	if( now.first ) {
		return now;
	}
	now = checkF(L+1, R);
	if( t[L] == '-' && now.first ) {
		now.second = -now.second;
		return now;
	}
	now = checkE(L+1, R-1);
	if( t[L] == '(' && t[R] == ')' && now.first ) {
		return now;
	}
	now.first = false;
	return now;
}

pii checkT( int L, int R ) {
	if( L > R ) {
		return pii(false, 0);
	}
	pii &now = dpT[L][R];
	if( now.first != -1 ) return now;
	now = checkF(L, R);
	if( now.first ) {
		return now;
	}
	for( int i = L; i <= R; ++i )
		if( t[i] == '*' ) {
			pii pl = checkT(L, i-1);
			pii pr = checkF(i+1, R);
			if( pl.first && pr.first ) {
				now.first = true;
				now.second = pl.second * pr.second;
				return now;
			}
		}
	now.first = false;
	return now;
}

pii checkE( int L, int R ) {
	if( L > R ) {
		return pii(false, 0);
	}
	pii &now = dpE[L][R];
	if( now.first != -1 ) return now;
	now = checkT(L, R);
	if( now.first ) {
		return now;
	}
	for( int i = L; i <= R; ++i )
		if( t[i] == '+' || t[i] == '-' ) {
			pii pl = checkE(L, i-1);
			pii pr = checkT(i+1, R);
			if( pl.first && pr.first ) {
				now.first = true;
				if( t[i] == '+' ) {
					now.second = pl.second + pr.second;
				} else {
					now.second = pl.second - pr.second;
				}
				return now;
			}
		}
	now.first = false;
	return now;
}

bool checkQ( int L, int R ) {
	int cnt = 0, pos;
	for( int i = L; i <= R; ++i )
		if( t[i] == '=' ) {
			pos = i;
			++cnt;
		}
	if( cnt != 1 ) return false;
	pii pl = checkE(L, pos-1);
	pii pr = checkE(pos+1, R);
	return pl.first && pr.first && pl.second == pr.second;
}

void dfs( int idx ) {
	if( idx == (int)ch.size() ) {
		memset(dpE, -1, sizeof dpE);
		memset(dpT, -1, sizeof dpT);
		memset(dpF, -1, sizeof dpF);
		if( checkQ(0, n-1) )
			++ans;
	} else {
		for( int i = 0; i < 8; ++i )
			if( !used[i] ) {
				used[i] = true;
				for( int pos = 0; pos < n; ++pos )
					if( s[pos] == ch[idx] )
						t[pos] = SYMB[i];
				dfs(idx+1);
				used[i] = false;
			}
	}
}

int main() {
	_w = scanf( "%s", s );
	n = (int)strlen(s);
	init_ch();
	if( ch.size() > 8 ) {
		puts("0");
		return 0;
	}
	for( int i = 0; i < n; ++i )
		t[i] = s[i];
	dfs(0);
	printf( "%d\n", ans );
	return 0;
}
