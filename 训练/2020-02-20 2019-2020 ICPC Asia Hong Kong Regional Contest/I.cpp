#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
const int N = 200010;
int _w;

int n, m, nid;

ll demand[N];
vector<pii> place[N];

ll have[N];
set<pii> st[N];

void init() {
	;
}

void insert( int y, vector<int> q ) {
	++nid;
	
	demand[nid] = y;
	for( int x : q )
		demand[nid] += have[x];
	
	int k = (int)q.size();
	int tmp = y / k + bool(y % k);
	for( int i = 0; i < k; ++i ) {
		st[q[i]].insert( pii(have[q[i]] + tmp, nid) );
		place[nid].push_back( pii(have[q[i]] + tmp, q[i]) );
	}
}

bool update( int id ) {
	int k = (int)place[id].size();
	for( int i = 0; i < k; ++i ) {
		pii now = place[id][i];
		int plc = (int)now.second;
		now.second = id;
		st[plc].erase(now);
	}
	
	ll collect = 0;
	for( int i = 0; i < k; ++i )
		collect += have[place[id][i].second];
	if( collect >= demand[id] ) {
		return true;
	} else {
		ll diff = demand[id] - collect;
		diff = diff / k + bool(diff % k);
		for( int i = 0; i < k; ++i ) {
			place[id][i].first = have[place[id][i].second] + diff;
			pii now = place[id][i];
			now.second = id;
			st[place[id][i].second].insert( now );
		}
		return false;
	}
}

vector<int> ans;

int inc( int x, int y ) {
	have[x] += y;
	ans.clear();
	while( st[x].size() && st[x].begin()->first <= have[x] ) {
		pii now = *st[x].begin();
		st[x].erase( st[x].begin() );
		if( update( (int)now.second ) )
			ans.push_back( (int)now.second );
	}
	printf( "%d", (int)ans.size() );
	sort( ans.begin(), ans.end() );
	for( int people : ans )
		printf( " %d", people );
	puts("");
	return (int)ans.size();
}

int main() {
	_w = scanf( "%d%d", &n, &m );
	init();
	int last = 0;
	while( m-- ) {
		int opt;
		_w = scanf( "%d", &opt );
		if( opt == 1 ) {
			int y, k;
			_w = scanf( "%d%d", &y, &k );
			y ^= last;
			vector<int> now;
			while( k-- ) {
				int q;
				_w = scanf( "%d", &q );
				q ^= last;
				now.push_back(q);
			}
			insert(y, now);
		} else {
			int x, y;
			_w = scanf( "%d%d", &x, &y );
			x ^= last;
			y ^= last;
			last = inc(x, y);
		}
	}
	return 0;
}
