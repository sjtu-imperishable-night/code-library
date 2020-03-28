#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int N = 110;
int _w;

namespace Dinic {
	const int MAXV = 1000010;
	const int MAXE = 1000010;
	struct Edge {
		int u, v, c, f;
		Edge() {}
		Edge( int uu, int vv, int cc, int ff ) {
			u = uu, v = vv, c = cc, f = ff;
		}
	};
	int n, m, s, t;
	int head[MAXV], nxt[MAXE*2];
	Edge edge[MAXE*2];
	void init( int n2 ) {
		n = n2, m = 0;
		for( int i = 0; i < n; ++i )
			head[i] = -1;
	}
	void adde( int u, int v, int c ) {
		edge[m] = Edge(u, v, c, 0);
		nxt[m] = head[u], head[u] = m++;
		edge[m] = Edge(v, u, 0, 0);
		nxt[m] = head[v], head[v] = m++;
	}
	int dis[MAXV], cur[MAXV];
	queue<int> q;
	bool bfs() {
		while( !q.empty() ) q.pop();
		for( int i = 0; i < n; ++i )
			dis[i] = 1e9;
		dis[s] = 0, q.push(s);
		while( !q.empty() ) {
			int u = q.front(); q.pop();
			if( u == t ) break;
			for( int i = head[u]; ~i; i = nxt[i] ) {
				Edge &e = edge[i];
				if( e.c > e.f && dis[e.v] == 1e9 ) {
					dis[e.v] = dis[u] + 1;
					q.push(e.v);
				}
			}
		}
		return dis[t] != 1e9;
	}
	int dfs( int u, int res ) {
		if( u == t || !res ) return res;
		int flow = 0;
		for( int &i = cur[u]; ~i; i = nxt[i] ) {
			Edge &e = edge[i];
			if( e.c > e.f && dis[e.v] == dis[u] + 1 ) {
				int f = dfs(e.v, min(e.c-e.f, res));
				flow += f, res -= f;
				e.f += f, edge[i^1].f -= f;
				if( !res ) break;
			}
		}
		return flow;
	}
	int solve( int s2, int t2 ) {
		s = s2, t = t2;
		int flow = 0;
		while( bfs() ) {
			for( int i = 0; i < n; ++i )
				cur[i] = head[i];
			flow += dfs(s, 1e9);
		}
		return flow;
	}
	void update( vector<int> &anset, const vector<int> &part1, const vector<int> &part2 ) {
		anset.clear();
		for( int x : part1 )
			if( dis[x] != 1e9 )
				anset.push_back(x);
		for( int y : part2 )
			if( dis[y] == 1e9 )
				anset.push_back(y);
	}
}

int n, d, px[N], py[N];
int ans;
vector<int> anset;

int dist2( int i, int j ) {
	int dx = px[i] - px[j];
	int dy = py[i] - py[j];
	return dx * dx + dy * dy;
}

pii Vec( int i, int j ) {
	return pii( px[j] - px[i], py[j] - py[i] );
}

int Cross( pii a, pii b ) {
	return a.first * b.second - a.second * b.first;
}

bool OnLeft( int P, int A, int B ) {
	return Cross(Vec(A, B), Vec(A, P)) >= 0;
}

vector<int> part1, part2;

void _solve( int P, int Q ) {
	int d2 = dist2(P, Q);
	part1.clear();
	part2.clear();
	for( int i = 1; i <= n; ++i ) {
		if( dist2(i, P) <= d2 && dist2(i, Q) <= d2 ) {
			if( OnLeft(i, P, Q) ) {
				part1.push_back(i);
			} else {
				part2.push_back(i);
			}
		}
	}
	if( part1.size() + part2.size() <= (size_t)ans ) return;
	Dinic::init(n+2);
	for( int x : part1 )
		Dinic::adde(0, x, 1);
	for( int y : part2 )
		Dinic::adde(y, n+1, 1);
	for( int x : part1 )
		for( int y : part2 )
			if( dist2(x, y) > d2 )
				Dinic::adde(x, y, 1);
	int match = Dinic::solve(0, n+1);
	if( part1.size() + part2.size() - match > ans ) {
		ans = part1.size() + part2.size() - match;
		Dinic::update(anset, part1, part2);
	}
}

void solve() {
	for( int i = 1; i <= n; ++i )
		for( int j = i; j <= n; ++j )
			if( dist2(i, j) <= d*d ) {
				_solve(i, j);
			}
	printf( "%d\n", ans );
	for( int x : anset )
		printf( "%d ", x );
	puts("");
}

int main() {
	_w = scanf( "%d%d", &n, &d );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d%d", px+i, py+i );
	solve();
	return 0;
}
