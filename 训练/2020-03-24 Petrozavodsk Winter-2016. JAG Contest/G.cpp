#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 20010;
int _w;

int A, B, C, n, px[N], py[N], pz[N];

struct Triple {
	int x, y, z;
	
	Triple() {}
	Triple( int xx, int yy, int zz ) {
		x = xx, y = yy, z = zz;
	}
	Triple( ll h ) {
		z = h % int(1e6);
		h /= int(1e6);
		y = h % int(1e6);
		h /= int(1e6);
		x = h;
	}
	
	bool operator<( const Triple &rhs ) const {
		if( x == rhs.x ) {
			if( y == rhs.y ) {
				return z < rhs.z;
			} else {
				return y < rhs.y;
			}
		} else {
			return x < rhs.x;
		}
	}
	
	operator ll() {
		return 1LL * x * ll(1e12) + 1LL * y * ll(1e6) + z;
	}
};

unordered_map<ll,int> mp;

bool inside( Triple p ) {
	return p.x >= 0 && p.x < A && p.y >= 0 && p.y < B && p.z >= 0 && p.z < C;
}

namespace DSU {
	const int dx[] = {1, -1, 0, 0, 0, 0};
	const int dy[] = {0, 0, 1, -1, 0, 0};
	const int dz[] = {0, 0, 0, 0, 1, -1};
	
	int pa[N*27], m;

	int find( int u ) {
		return pa[u] == u ? u : pa[u] = find( pa[u] );
	}
	void link( int u, int v ) {
		pa[find(u)] = find(v);
	}
	int solve() {
		m = (int)mp.size();
		// printf( "m = %d\n", m );
		for( int i = 1; i <= m; ++i )
			pa[i] = i;
		for( auto it : mp ) {
			Triple p = it.first;
			int u = it.second;
			for( int d = 0; d < 6; ++d ) {
				Triple q = p;
				q.x += dx[d];
				q.y += dy[d];
				q.z += dz[d];
				if( mp.count(q) )
					DSU::link(u, mp[q]);
			}
		}
		for( int i = 1; i <= m; ++i ) find(i);
		sort(pa+1, pa+m+1);
		return int(unique(pa+1, pa+m+1) - pa);
	}
}

int solve1() {
	mp.clear();
	int id = 0;
	for( int i = 1; i <= n; ++i ) {
		for( int dx = -1; dx <= 1; ++dx ) {
			for( int dy = -1; dy <= 1; ++dy ) {
				for( int dz = -1; dz <= 1; ++dz ) {
					int x = px[i] + dx;
					int y = py[i] + dy;
					int z = pz[i] + dz;
					Triple p(x, y, z);
					// printf( "x = %d, y = %d, z = %d\n", x, y, z );
					if( !mp.count(p) && inside(p) ) {
						mp[p] = ++id;
						// printf( "x = %d, y = %d, z = %d\n", x, y, z );
					}
				}
			}
		}
	}
	return DSU::solve();
}

int solve2() {
	mp.clear();
	int id = 0;
	set<Triple> ban;
	for( int i = 1; i <= n; ++i )
		ban.insert( Triple( px[i], py[i], pz[i] ) );
	for( int i = 1; i <= n; ++i ) {
		for( int dx = -1; dx <= 1; ++dx ) {
			for( int dy = -1; dy <= 1; ++dy ) {
				for( int dz = -1; dz <= 1; ++dz ) {
					int x = px[i] + dx;
					int y = py[i] + dy;
					int z = pz[i] + dz;
					Triple p(x, y, z);
					if( !mp.count(p) && !ban.count(p) && inside(p) )
						mp[p] = ++id;
				}
			}
		}
	}
	return DSU::solve();
}

int main() {
	_w = scanf( "%d%d%d%d", &A, &B, &C, &n );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d%d%d", px+i, py+i, pz+i );
	int ans = solve1();
	// printf( "ans = %d\n", ans );
	ans -= solve2();
	printf( "%d\n", -ans+1 );
	return 0;
}
