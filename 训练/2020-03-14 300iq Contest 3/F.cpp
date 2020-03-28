#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 300010;
int _w;

int n, a, b, h[N], wage[N], price[N];
priority_queue<int> pq;

int main() {
	_w = scanf( "%d%d%d", &n, &a, &b );
	for( int i = 1; i <= n; ++i ) {
		_w = scanf( "%d", h+i );
		wage[i] = h[i] / b + bool(h[i] % b);
		int tmp = h[i] - (wage[i] - 1) * b;
		price[i] = tmp / a + bool(tmp % a) + 1;
	}
	ll money = 1;
	int ans = 0;
	for( int i = 1; i <= n; ++i ) {
		money += wage[i];
		if( money >= price[i] ) {
			money -= price[i];
			pq.push( price[i] );
			++ans;
		} else {
			if( pq.empty() || pq.top() + money < price[i] || pq.top() < price[i] ) continue;
			else {
				money += pq.top();
				pq.pop();
				money -= price[i];
				pq.push( price[i] );
			}
		}
	}
	printf( "%d\n", ans );
	return 0;
}
