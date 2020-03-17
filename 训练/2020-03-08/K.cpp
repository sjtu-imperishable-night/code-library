#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 200010;
int _w;

int n, s[N];
char str[N];

struct SAM {
	int ch[N*2][26], len[N*2], pa[N*2], idx;
	
	void init() {
		for( int i = 0; i < n*2+10; ++i ) {
			memset( ch[i], 0, sizeof ch[i] );
			len[i] = 0;
			pa[i] = 0;
		}
		idx = 1;
		pa[0] = -1;
	}
	int append( int p, int c ) {
		int np = idx++;
		len[np] = len[p] + 1;
		while( p != -1 && !ch[p][c] )
			ch[p][c] = np, p = pa[p];
		if( p == -1 ) pa[np] = 0;
		else {
			int q = ch[p][c];
			if( len[q] == len[p] + 1 ) pa[np] = q;
			else {
				int nq = idx++;
				memcpy(ch[nq], ch[q], sizeof ch[q]);
				len[nq] = len[p] + 1;
				pa[nq] = pa[q];
				pa[q] = pa[np] = nq;
				while( p != -1 && ch[p][c] == q )
					ch[p][c] = nq, p = pa[p];
			}
		}
		return np;
	}
};
SAM sam, rsam;

struct Graph {
	int head[N*2], nxt[N*2], to[N*2], eid;
	void init() {
		eid = 0;
		for( int i = 0; i < n*2+10; ++i )
			head[i] = -1;
	}
	void link( int u, int v ) {
		to[eid] = v, nxt[eid] = head[u], head[u] = eid++;
	}
};
Graph tree, rtree;

int dfn[N*2], dfnc, rb[N*2];
int rdfn[N*2], rdfnc, rrb[N*2];

void dfs( int u, const Graph &G, int *dfs_num, int &dfn_cnt, int *dfn_rb ) {
	dfs_num[u] = ++dfn_cnt;
	for( int i = G.head[u]; ~i; i = G.nxt[i] ) {
		int v = G.to[i];
		dfs(v, G, dfs_num, dfn_cnt, dfn_rb);
	}
	dfn_rb[u] = dfn_cnt;
}

pii pt[N];

int cnt[N*2], seq[N*2], scnt[N*2];

void radix_sort() {
	for( int i = 0; i < sam.idx; ++i )
		scnt[i] = 0;
	for( int i = 0; i < sam.idx; ++i )
		++scnt[sam.len[i]];
	for( int i = 1; i < sam.idx; ++i )
		scnt[i] += scnt[i-1];
	for( int i = sam.idx-1; i >= 0; --i )
		seq[--scnt[sam.len[i]]] = i;
}

void solve_cnt() {
	for( int i = 0; i < sam.idx; ++i )
		cnt[i] = 0;
	int last = 0;
	for( int i = 1; i <= n; ++i ) {
		last = sam.ch[last][s[i]];
		++cnt[last];
	}
	radix_sort();
	for( int i = sam.idx-1; i >= 1; --i ) {
		int u = seq[i];
		cnt[sam.pa[u]] += cnt[u];
	}
}

namespace Plane {
	inline int lb( int x ) {
		return x & (-x);
	}
	
	vector<int> vec[N*2];
	
	void init() {
		for( int i = 0; i < n*2+10; ++i )
			vec[i].clear();
	}
	void solve() {
		for( int i = 0; i < n*2+10; ++i )
			sort( vec[i].begin(), vec[i].end() );
	}
	void insert( int x, int y ) {
		for( ; x < n*2+10; x += lb(x) )
			vec[x].push_back(y);
	}
	int count( const vector<int> &v, int l, int r ) {
		auto lit = lower_bound(v.begin(), v.end(), l);
		auto rit = upper_bound(v.begin(), v.end(), r);
		return int(rit - lit);
	}
	int query( int x, int yl, int yr ) {
		int s = 0;
		for( ; x; x -= lb(x) )
			s += count( vec[x], yl, yr );
		return s;
	}
	int query( int xl, int xr, int yl, int yr ) {
		return query(xr, yl, yr) - query(xl-1, yl, yr);
	}
}

void init() {
	sam.init();
	rsam.init();
	
	int last;
	
	last = 0;
	for( int i = 1; i <= n; ++i )
		last = sam.append(last, s[i]);
	last = 0;
	for( int i = n; i >= 1; --i )
		last = rsam.append(last, s[i]);
	
	tree.init();
	rtree.init();
	for( int i = 1; i < sam.idx; ++i )
		tree.link( sam.pa[i], i );
	for( int i = 1; i < rsam.idx; ++i )
		rtree.link( rsam.pa[i], i );
	
	dfnc = 0;
	rdfnc = 0;
	dfs(0, tree, dfn, dfnc, rb);
	dfs(0, rtree, rdfn, rdfnc, rrb);
	
	last = 0;
	for( int i = 1; i <= n; ++i ) {
		pt[i].first = dfn[last];
		last = sam.ch[last][s[i]];
	}
	last = 0;
	for( int i = n; i >= 1; --i ) {
		pt[i].second = rdfn[last];
		last = rsam.ch[last][s[i]];
	}
	
	Plane::init();
	for( int i = 1; i <= n; ++i )
		Plane::insert( pt[i].first, pt[i].second );
	Plane::solve();
	
	solve_cnt();
}

int nod[N], rnod[N];

int count_all( int len ) {
	int u = nod[len];
	if( u == -1 ) return 0;
	return cnt[u];
}

void query() {
	int len = (int)strlen(str+1);
	for( int i = 0; i <= len+1; ++i )
		nod[i] = rnod[i] = -1;
	
	nod[0] = 0;
	for( int i = 1; i <= len; ++i ) {
		nod[i] = sam.ch[nod[i-1]][str[i] - 'a'];
		if( !nod[i] ) {
			nod[i] = -1;
			break;
		}
	}
	
	rnod[len+1] = 0;
	for( int i = len; i >= 1; --i ) {
		rnod[i] = rsam.ch[rnod[i+1]][str[i] - 'a'];
		if( !rnod[i] ) {
			rnod[i] = -1;
			break;
		}
	}
	
	ll ans = 0;
	for( int i = 1; i <= len; ++i ) {
		int u = nod[i-1];
		int v = rnod[i+1];
		if( u == -1 || v == -1 ) continue;
		ans += Plane::query( dfn[u], rb[u], rdfn[v], rrb[v] );
	}
	ans -= 1LL * count_all(len) * (len-1);
	printf( "%lld\n", ans );
}

int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		_w = scanf( "%s", str+1 );
		n = (int)strlen(str+1);
		for( int i = 1; i <= n; ++i )
			s[i] = str[i] - 'a';
		init();
		int q;
		_w = scanf( "%d", &q );
		while( q-- ) {
			_w = scanf( "%s", str+1 );
			query();
		}
	}
	return 0;
}
