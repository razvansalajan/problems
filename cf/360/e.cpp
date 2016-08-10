#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int nmax = 505;

int n, K;
int a[nmax];
int dp[2][nmax][nmax];

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
	#endif

	cin >> n >> K;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	int curr = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < nmax; ++j) {
			for (int k = 0; k < nmax; ++k) {
				dp[i][j][k] = 0;
			}
		}
	}
	int prev = 1 ^ curr;
	dp[prev][0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < nmax; ++j) {
			for (int k = 0; k <= j; ++k) {
				dp[curr][j][k] = dp[prev][j][k];
				if (j - a[i] >= 0) {
					dp[curr][j][k] |= dp[prev][j - a[i]][k];
				}
				if (k - a[i] >= 0) {
					dp[curr][j][k] |= dp[prev][j - a[i]][k - a[i]];
				}
			}
		}
		curr = 1 ^ curr;
		prev = 1 ^ prev;
	}

	vector<int> ans;
	for (int j = 0; j <= K; ++j) {
		if (dp[prev][K][j]) {
			ans.pb(j);
		}
	}
	cout << ans.size() << "\n";
	for (auto i : ans) {
		cout << i << " ";
	}

	return 0;
}