#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
unordered_map<string, int> M;
char ss[20];
int cnt_n;
int getname() {
	scanf("%s", ss);
	string s = ss;
	int &x = M[s];
	if (!x) x = ++ cnt_n;
	return x;
}
const int N = 1005, P = 305;
vector<pair<int, int>> doc[N];
bool done[N], v[P][P];
vector<int> st[P][P];
bool d[P][P];
int main() {
	int s, t;
	s = getname();
	t = getname();
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		int mi;
		scanf("%d", &mi);
		for (int j = 1; j <= mi; ++ j) {
			int x = getname();
			int y = getname();
			doc[i].push_back(make_pair(x, y));
			st[x][y].push_back(i);
		}
	}
	queue<pair<int, int>> q;
	q.push(make_pair(s, t));
	v[s][t] = 1;
	while (!q.empty()) {
		auto p = q.front(); q.pop();
		//d[p.first][p.second] = 1;
		for (int x : st[p.first][p.second]) {
			if (done[x]) continue;
			done[x] = 1;
			for (auto u : doc[x]) {
				if (!v[u.first][u.second]) {
					for (int i = 1; i <= cnt_n; ++ i) {
						if (v[i][u.first]) if (!v[i][u.second]) {
							v[i][u.second] = 1;
							q.push(make_pair(i, u.second));
						}
						if (v[u.second][i]) if (!v[u.first][i]) {
							v[u.first][i] = 1;
							q.push(make_pair(u.first, i));
						}
					}
					q.push(u);
					v[u.first][u.second] = 1;
				}
			}
		}
	}
	for (int k = 1; k <= cnt_n; ++ k) {
		for (int i = 1; i <= cnt_n; ++ i) {
			for (int j = 1; j <= cnt_n; ++ j) {
				v[i][j] |= v[i][k] && v[k][j];
			}
		}
	}
	//for (int i = 1; i <= cnt_n; ++ i) if (d[i][i]) return 0 * puts("No");
	for (int i = 1; i <= cnt_n; ++ i) {
		for (int j = 1; j <= cnt_n; ++ j) {
			//if (d[i][j] && d[j][i]) return 0 * puts("No");
			if (v[i][j] && v[j][i]) return 0 * puts("No");
		}
	}
	puts("Yes");
}

