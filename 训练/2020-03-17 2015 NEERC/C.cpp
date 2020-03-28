#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int N = 500010;
const int M = 500010;
int _w;

namespace G {
	int head[N], nxt[N*2], to[N*2], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
		to[eid] = u, nxt[eid] = head[v], head[v] = eid++;
	}
}

int n, m;

namespace CJK {
	int head[N], nxt[N*2], to[N*2], eid;
	void init() {
		eid = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
		to[eid] = u, nxt[eid] = head[v], head[v] = eid++;
	}
}

namespace BCC {
	int dfn[N], dfs_clock, low[N], bccno[N];
	int bcc_cnt, iscut[N];
	vector<int> bcc[N];
	stack<pii> stk;
	
	void dfs( int u, int fa ) {
		using namespace G;
		low[u] = dfn[u] = ++dfs_clock;
		int child = 0;
		for( int e = head[u]; ~e; e = nxt[e] ) {
			int v = to[e];
			if( v == fa ) continue;
			if( !dfn[v] ) {
				stk.push( pii(u, v) );
				dfs(v, u);
				++child;
				low[u] = min( low[u], low[v] );
				if( low[v] >= dfn[u] ) {
					iscut[u] = true;
					++bcc_cnt;
					bcc[bcc_cnt].clear();
					while(1) {
						pii e = stk.top();
						stk.pop();
						if( bccno[e.first] != bcc_cnt ) {
							bccno[e.first] = bcc_cnt;
							bcc[bcc_cnt].push_back(e.first);
						}
						if( bccno[e.second] != bcc_cnt ) {
							bccno[e.second] = bcc_cnt;
							bcc[bcc_cnt].push_back(e.second);
						}
						if( e.first == u && e.second == v ) break;
					}
				}
			} else if( dfn[v] < dfn[u] ) {
				stk.push( pii(u, v) );
				low[u] = min( low[u], dfn[v] );
			}
		}
		if( fa == -1 && child == 1 )
			iscut[u] = false;
	}
	
	void solve() {
		memset(dfn, 0, sizeof dfn);
		dfs_clock = 0;
		memset(bccno, 0, sizeof bccno);
		bcc_cnt = 0;
		memset(iscut, false, sizeof iscut);
		for( int i = 1; i <= n; ++i )
			if( !dfn[i] ) dfs(i, -1);
	}
}

int cyc = 0, sz[N], cyc_sz[N];
ll sz_ans, cyc_sz_ans[N];

int solve_sz( int s ) {
	queue<int> q, vec;
	int tot = 0;
	q.push(s), sz[s] = 1;
	while( !q.empty() ) {
		int u = q.front(); q.pop();
		vec.push(u);
		++tot;
		using namespace CJK;
		for( int i = head[u]; ~i; i = nxt[i] ) {
			int v = to[i];
			if( v > n || sz[v] ) continue;
			sz[v] = 1;
			q.push(v);
		}
	}
	while( !vec.empty() ) {
		int u = vec.front();
		vec.pop();
		sz[u] = tot;
	}
	return tot;
}

int sub[N];

void solve_sub( int u, int fa ) {
	using namespace CJK;
	sub[u] = u <= n;
	for( int i = head[u]; ~i; i = nxt[i] ) {
		int v = to[i];
		if( v == fa ) continue;
		solve_sub(v, u);
		sub[u] += sub[v];
	}
}

void prelude() {
	BCC::solve();
	CJK::init();
	using BCC::bcc_cnt;
	for( int i = 1; i <= bcc_cnt; ++i ) {
		using BCC::bcc;
		if( bcc[i].size() == 2 ) {
			CJK::link( bcc[i][0], bcc[i][1] );
		} else {
			++cyc;
			for( int u : bcc[i] )
				CJK::link(u, cyc+n);
		}
	}
	for( int i = 1; i <= n; ++i )
		if( sz[i] == 0 ) {
			int tot = solve_sz(i);
			sz_ans += 1LL * tot * (tot-1) / 2 - (tot-1);
		}
	solve_sub(1, 0);
	for( int i = 1; i <= cyc; ++i ) {
		int u = i+n;
		using namespace CJK;
		for( int e = head[u]; ~e; e = nxt[e] ) {
			int v = to[e];
			cyc_sz[i] += sz[v];
			int tmp = sz[v];
			cyc_sz_ans[i] += 1LL * tmp * (tmp-1) / 2 - (tmp-1);
		}
	}
}

ll ans = 0;

void update( int u, int v ) {
	if( u > v ) return;
	if( v > n ) {
		int id = v-n;
		ll now = sz_ans - cyc_sz_ans[id];
		int tmp = cyc_sz[id];
		now += 1LL * tmp * (tmp-1) / 2 - (tmp-1);
		ans += now;
	} else {
		int part1 = min( sub[u], sub[v] );
		int part2 = n - part1;
		ans += 1LL * part1 * part2;
	}
}

int offset = 0;

void solve() {
	prelude();
	for( int i = 1; i <= cyc+n; ++i ) {
		using namespace CJK;
		for( int e = head[i]; ~e; e = nxt[e] ) {
			int j = to[e];
			update(i, j);
		}
	}
	printf( "%lld\n", ans - offset );
}

int main() {
	freopen("cactus.in", "r", stdin);
	freopen("cactus.out", "w", stdout);
	_w = scanf( "%d%d", &n, &m );
	G::init();
	while( m-- ) {
		int k;
		_w = scanf( "%d", &k );
		int last = 0;
		while( k-- ) {
			int now;
			_w = scanf( "%d", &now );
			if( last ) {
				G::link(now, last);
				++offset;
			}
			last = now;
		}
	}
	solve();
	return 0;
}
