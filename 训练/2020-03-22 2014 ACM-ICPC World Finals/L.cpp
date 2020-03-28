#include <cstdio>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;
const double eps = 1e-12, inf = 110000;
const int N = 20010, M = 100010;
int n, m, w, q, cnt, cur, i, j, x;
int idx[N], g[N], v[M], nxt[M], ed, d[N], que[N];
int h, t, S, T;
inline int sgn( double x ) {
	if( fabs(x) < eps ) return 0;
	return x > 0 ? 1 : -1;
}
struct P {
	double x, y;
	P() {}
	P(double _x, double _y) {
		x = _x, y = _y;
	}
	P operator+(P b) {
		return P(x + b.x, y + b.y);
	}
	P operator-(P b) {
		return P(x - b.x, y - b.y);
	}
	P operator*(double b) {
		return P(x*b, y*b);
	}
	P operator/(double b) {
		return P(x/b, y/b);
	}
	double operator*(P b) {
		return x * b.x + y * b.y;
	}
} a[N], b[N], st[N], en[N], pool[N];
inline bool cmpP( const P &a, const P &b ) {
	return !sgn(a.x-b.x) ? a.y < b.y : a.x < b.x;
}
inline double cross(P a, P b) {
	return a.x*b.y - a.y*b.x;
}
inline bool point_on_segment(P p, P a, P b) {
	return sgn(cross(b-a, p-a)) == 0 && sgn((p-a)*(p-b)) <= 0;
}
inline int has_intersection(P a, P b, P p, P q ) {
	int d1 = sgn(cross(b-a, p-a));
	int d2 = sgn(cross(b-a, q-a));
	int d3 = sgn(cross(q-p, a-p));
	int d4 = sgn(cross(q-p, b-p));
	return d1*d2 < 0 && d3*d4 < 0;
}
inline P line_intersection( P a, P b, P p, P q ) {
	double U = cross(p-a, q-p);
	double D = cross(b-a, q-p);
	return a+(b-a)*(U/D);
}
struct E {
	int x, y;
	double o;
	E(){}
	E( int _x, int _y ) {
		x = _x, y = _y;
		o = atan2(a[y].x - a[x].x, a[y].y - a[x].y);
	}
} e[M];
bool del[M], ex[M];
int from[M], id[N];
struct EV {
	double x;
	int y, t;
	EV() {}
	EV( double _x, int _y, int _t ) {
		x = _x, y = _y, t = _t;
	}
} ev[M<<1];
inline bool cmpEV( const EV&a, const EV&b ) {
	if( sgn(a.x-b.x) ) return a.x < b.x;
	return a.t < b.t;
}
namespace GetArea {
	struct cmp {
		bool operator()(int a, int b) {
			return e[a].o < e[b].o;
		}
	};
	set<int,cmp> g[N];
	set<int,cmp>::iterator k;
	int i, j, q[M], t;
	void work() {
		for( i = 0; i < m+m; i++ )
			if( !del[i] && !ex[i] ) {
				for( q[t=1]=j=i;;q[++t]=j=*k ) {
					k = g[e[j].y].find(j^1);
					++k;
					if( k == g[e[j].y].end() )
						k = g[e[j].y].begin();
					if( *k == i ) break;
				}
				double s = 0;
				for( j = 1; j <= t; ++j )
					s += cross(a[e[q[j]].x],a[e[q[j]].y]), del[q[j]] = 1;
				if( sgn(s) < 0 ) continue;
				for( cnt++, j = 1; j <= t; ++j )
					from[q[j]] = cnt;
			}
	}
}
namespace ScanLine {
	struct cmp {
		bool operator()( int A, int B ) {
			if( e[A].x == e[B].x )
				return e[A].o > e[B].o;
			double x = min(a[e[A].x].x, a[e[B].x].x);
			double yA = (a[e[A].x].y - a[e[A].y].y) * (x-a[e[A].y].x) / (a[e[A].x].x - a[e[A].y].x) + a[e[A].y].y;
			double yB = (a[e[B].x].y - a[e[B].y].y) * (x-a[e[B].y].x) / (a[e[B].x].x - a[e[B].y].x) + a[e[B].y].y;
			return yA > yB;
		}
	};
	set<int,cmp> T;
	int cnt, i, j, k, g[M], v[M], nxt[M], ed, vis[N], t, tmp[N];
	inline bool cmpC( int x, int y ) {
		return a[x].x < a[y].x;
	}
	inline void add( int x, int y ) {
		v[++ed] = y; nxt[ed] = g[x]; g[x] = ed;
	}
	void dfs( int x ) {
		vis[x] = 1;
		if( a[x].y > a[t].y ) t = x;
		for( int i = g[x];i;i=nxt[i] )
			if( !vis[v[i]] )
				dfs( v[i] );
	}
	inline double cal( int A, double x ) {
		return(a[e[A].x].y-a[e[A].y].y)*(x-a[e[A].y].x)/(a[e[A].x].x-a[e[A].y].x) + a[e[A].y].y;
	}
	void connect() {
		for( i = 0; i < m+m; ++i )
			add( e[i].x, e[i].y );
		for( i = 1; i <= n; ++i )
			if( !vis[i] )
				dfs(t=i), ev[cnt++]=EV(a[t].x, t, 2);
		for( i = 0; i < m+m; ++i )
			if( sgn(a[e[i].x].x-a[e[i].y].x) > 0 ) {
				ev[cnt++] = EV(a[e[i].y].x, i, 1);
				ev[cnt++] = EV(a[e[i].x].x, i, 0);
			}
		sort(ev, ev+cnt, cmpEV);
		a[n+1] = P(inf, inf);
		a[n+2] = P(-inf, inf);
		e[m+m] = E(n+1, n+2);
		T.insert(m+m);
		e[m+m+1] = E(n+2, n+1);
		n += 2, m++;
		for( ed=0,i=1; i <= n; ++i ) g[i] = 0;
		for( i = 0; i < cnt; ++i ) {
			if( ev[i].t == 0 ) T.erase(ev[i].y);
			if( ev[i].t == 1 ) T.insert(ev[i].y);
			if( ev[i].t == 2 ) {
				a[n+1] = P(ev[i].x, a[ev[i].y].y+eps);
				a[n+2] = P(ev[i].x-1, a[ev[i].y].y+eps);
				e[m+m] = E(n+1, n+2);
				T.insert(m+m);
				set<int,cmp>::iterator j = T.find(m+m);
				j--, add(*j, ev[i].y);
				T.erase(m+m);
			}
		}
		int newm = m+m;
		for( i = 0; i < m+m; ++i ) {
			for( cnt = 0, j=g[i];j;j=nxt[j] ) {
				if( !sgn(a[v[j]].x-a[e[i].x].x) ) {
					e[newm++] = E(v[j], e[i].x);
					e[newm++] = E(e[i].x, v[j]);
					continue;
				}
				if( !sgn(a[v[j]].x-a[e[i].y].x) ) {
					e[newm++] = E(v[j], e[i].y);
					e[newm++] = E(e[i].y, v[j]);
					continue;
				}
				tmp[++cnt] = v[j];
			}
			if( !cnt ) continue;
			ex[i] = ex[i^1] = 1;
			sort(tmp+1, tmp+cnt+1, cmpC);
			for(k=e[i].y, j = 1; j <= cnt;k=n,j++ ) {
				a[++n] = P(a[tmp[j]].x, cal(i, a[tmp[j]].x));
				e[newm++] = E(k, n);
				e[newm++] = E(n, k);
				e[newm++] = E(tmp[j], n);
				e[newm++] = E(n, tmp[j]);
			}
			e[newm++] = E(n, e[i].x);
			e[newm++] = E(e[i].x, n);
		}
		m=newm/2;
	}
	void location() {
		for(i=cnt=0; i < m+m; ++i )
			if( !ex[i] && sgn(a[e[i].x].x - a[e[i].y].x) > 0 ) {
				ev[cnt++] = EV(a[e[i].y].x, i, 1);
				ev[cnt++] = EV(a[e[i].x].x, i, 0);
			}
		for( i = 0; i < q; ++i )
			ev[cnt++] = EV(b[i].x, i, 2);
		sort(ev, ev+cnt, cmpEV);
		T.clear();
		for(i=0;i<cnt;++i) {
			if( ev[i].t == 0 ) T.erase(ev[i].y);
			if( ev[i].t == 1 ) T.insert( ev[i].y );
			if( ev[i].t == 2 ) {
				a[n+1] = P(ev[i].x, b[ev[i].y].y);
				a[n+2] = P(ev[i].x-1, b[ev[i].y].y);
				e[m+m] = E(n+1, n+2);
				T.insert(m+m);
				set<int,cmp>::iterator j = T.find(m+m);
				if( j != T.begin() ) j--, id[ev[i].y] = from[*j];
				T.erase(m+m);
			}
		}
	}
}
inline int getid( P o ) {
	int l = 1, r = n, mid;
	while( l <= r ) {
		mid = (l+r)>>1;
		if( !sgn(o.x-a[mid].x) && !sgn(o.y-a[mid].y) ) return mid;
		if( sgn(o.x-a[mid].x) > 0 || !sgn(o.x-a[mid].x) && sgn(o.y-a[mid].y) > 0 )
			l = mid+1;
		else r=mid-1;
	}
}
inline void cal0( P a, P b, P c, P d ) {
	if( !has_intersection(a,b,c,d) ) return;
	::a[++n] = line_intersection(a,b,c,d);
}
inline void cal1( P a, P b, P c, P d ) {
	if( point_on_segment(c,a,b) ) {
		pool[++cur]=c;
		return;
	}
	if( point_on_segment(d,a,b) ) {
		pool[++cur]=d;
		return;
	}
	if( !has_intersection(a,b,c,d) ) return;
	pool[++cur] = line_intersection(a,b,c,d);
}
inline void add( int x, int y ) {
	v[++ed] = y; nxt[ed] = g[x]; g[x] = ed;
}
int main() {
	scanf("%d",&w);
	for( q=2;i<q;++i ) scanf( "%lf%lf", &b[i].x, &b[i].y );
	for( i = 0; i < w; ++i ) {
		scanf( "%lf%lf%lf%lf", &st[i].x, &st[i].y, &en[i].x, &en[i].y );
		a[++n] = st[i];
		a[++n] = en[i];
	}
	for( i = 0; i < w; ++i )
		for( j = 0; j < i; ++j )
			cal0(st[i], en[i], st[j], en[j]);
	sort(a+1, a+n+1, cmpP);
	int _=0;
	for( i = 1; i <= n; ++i )
		if( i == 1 || sgn(a[i].x - a[i-1].x) || sgn(a[i].y - a[i-1].y) ) a[++_] = a[i];
	n = _;
	for( i = 0; i < w; ++i ) {
		pool[1] = st[i];
		pool[cur=2] = en[i];
		for( j = 0; j < w; ++j )
			if( i != j ) cal1( st[i], en[i], st[j], en[j] );
		sort(pool+1, pool+cur+1, cmpP);
		for( j = 1; j <= cur; ++j )
			idx[j] = getid(pool[j]);
		for( j = 1; j < cur; ++j )
			if( idx[j] != idx[j+1] ) {
				e[m<<1] = E(idx[j], idx[j+1]);
				e[m<<1|1] = E(idx[j+1], idx[j]);
				m++;
			}
	}
	ScanLine::connect();
	for( i = 0; i < m+m; ++i )
		if( !ex[i] ) GetArea::g[e[i].x].insert(i);
	GetArea::work();
	ScanLine::location();
	for( i = 0; i < m+m; ++i )
		if( !ex[i] ) add( from[i], from[i^1] );
	d[que[h=t=1]=id[0]] = 1;
	while( h <= t )
		for( i = g[x=que[h++]];i;i=nxt[i] )
			if( !d[v[i]] )
				d[que[++t]=v[i]]=d[x]+1;
	return printf("%d", d[id[1]]-1), 0;
}
