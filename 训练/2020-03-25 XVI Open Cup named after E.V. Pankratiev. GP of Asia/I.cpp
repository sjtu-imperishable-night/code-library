#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 100010;
int _w;

int n, px[N], py[N];
char dir[N];
ll maxt;

namespace G {
	int head[N], nxt[N*10], to[N*10], len[N*10], eid;
	void init() {
		memset(head, -1, sizeof head);
		eid = 0;
	}
	void link( int u, int v, int w ) {
		to[eid] = v, len[eid] = w;
		nxt[eid] = head[u], head[u] = eid++;
	}
}

ll dis[N];
bool done[N];

struct Node {
	int u;
	ll d;
	Node() {}
	Node( int uu, ll dd ) {
		u = uu, d = dd;
	}
	bool operator<( const Node &rhs ) const {
		return d > rhs.d;
	}
};

priority_queue<Node> pq;

void dijkstra( int s ) {
	memset(dis, 0x3f, sizeof dis);
	memset(done, false, sizeof done);
	dis[s] = 0, pq.push( Node(s, 0) );
	while( !pq.empty() ) {
		Node o = pq.top(); pq.pop();
		int u = o.u;
		if( done[u] ) continue;
		done[u] = true;
		using namespace G;
		for( int i = head[u]; ~i; i = nxt[i] ) {
			int v = to[i], w = len[i];
			if( dis[u] + w < dis[v] ) {
				dis[v] = dis[u] + w;
				pq.push( Node(v, dis[v]) );
			}
		}
	}
}

bool cmpx( int i, int j ) {
	return px[i] < px[j];
}

bool cmpy( int i, int j ) {
	return py[i] < py[j];
}

map<int,vector<int> > mpx, mpy;

void solve() {
	for( int i = 1; i <= n; ++i ) {
		mpx[px[i]].push_back(i);
		mpy[py[i]].push_back(i);
	}
	G::init();
	for( auto it : mpx ) {
		vector<int> vec = it.second;
		sort(vec.begin(), vec.end(), cmpy);
		int last = 0;
		for( int id : vec )
			if( dir[id] == 'U' ) {
				G::link(last, id, py[id] - py[last]);
				last = id;
			} else {
				G::link(last, id, py[id] - py[last]);
			}
		last = 0;
		for( auto it = vec.rbegin(); it != vec.rend(); ++it ) {
			int id = *it;
			if( dir[id] == 'D' ) {
				G::link(last, id, py[last] - py[id]);
				last = id;
			} else {
				G::link(last, id, py[last] - py[id]);
			}
		}
	}
	for( auto it : mpy ) {
		vector<int> vec = it.second;
		sort(vec.begin(), vec.end(), cmpx);
		int last = 0;
		for( int id : vec )
			if( dir[id] == 'R' ) {
				G::link(last, id, px[id] - px[last]);
				last = id;
			} else {
				G::link(last, id, px[id] - px[last]);
			}
		last = 0;
		for( auto it = vec.rbegin(); it != vec.rend(); ++it ) {
			int id = *it;
			if( dir[id] == 'L' ) {
				G::link(last, id, px[last] - px[id]);
				last = id;
			} else {
				G::link(last, id, px[last] - px[id]);
			}
		}
	}
	dijkstra(1);
	for( int i = 1; i <= n; ++i ) {
		ll run = max(0LL, maxt - dis[i]);
		int dx = 0, dy = 0;
		if( dir[i] == 'L' ) dx = -1;
		else if( dir[i] == 'R' ) dx = 1;
		else if( dir[i] == 'D' ) dy = -1;
		else dy = 1;
		printf( "%lld %lld\n", px[i] + dx * run, py[i] + dy * run );
	}
}

int main() {
	_w = scanf( "%d%lld", &n, &maxt );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d%d %c", px+i, py+i, dir+i );
	solve();
	return 0;
}
