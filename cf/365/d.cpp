#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long
#define bit(x) (x&(-x))

struct Inter {
	int initPos, x, y;
	Inter() {}
	Inter(int initPos, int x, int y): initPos(initPos), x(x), y(y) {}
};
const int nmax = 1e6 + 6;
int n, m, a[nmax];
Inter queries[nmax];
int urm[nmax];
int aib[nmax];
int ans[nmax];

bool cmp(Inter A, Inter B) {
	return A.x < B.x;
}
void update(int pos, int val) {
	if (pos == -1) {
		return;
	}
	for (; pos <= n; pos += bit(pos)) {
		aib[pos] ^= val;
	}
}

int query(int pos) {
	int sum = 0;
	for (; pos; pos -= bit(pos)) {
		sum ^= aib[pos];
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		int x, y;
		cin >> x >> y;
		queries[i] = Inter(i, x, y);
	}
	sort(queries + 1, queries + m + 1, cmp);

	map<int, int> myMap;
	for (int i = n; i >= 1; --i) {
		if (myMap.find(a[i]) == myMap.end()) {
			urm[i] = -1;
			myMap.insert(make_pair(a[i], i));
		} else {
			urm[i] = myMap[a[i]];
			myMap[a[i]] = i;
		}
	}

	for (int i = 1; i <= n; ++i) {
		update(urm[i], a[urm[i]]);
	}

	int index = 1;
	for (int i = 1; i <= m; ++i) {
		while (index <= n && index < queries[i].x) {
			update(urm[index], a[urm[index]]);
			++index;
		}
		// cout << queries[i].x << " " << queries[i].y << " " << queries[i].initPos << "\n";
		// for (int j = 1; j <= n; ++j) {
		// 	cout << aint[j] << " ";
		// }
		// cout << "\n";
		ans[queries[i].initPos] = query(queries[i].y);
	}

	for (int i = 1; i <= m; ++i) {
		cout << ans[i] << "\n";
	}
	return 0;
}