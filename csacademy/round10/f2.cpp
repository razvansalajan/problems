#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int nmax = 101;
const int kmax = 102;
const int mod = 1e9 + 7;
int n;
string s;
int a[nmax];
int K;

int addRight(int oldR, int digit) {
	int newR = (oldR * 10 + digit) % K;
	return newR;
}

int dp[nmax][kmax][nmax][nmax];
int getRest[nmax][kmax][10];

int update(int &x, int y) {
	x += y;
	x %= mod;
}

int addLeft(int rest, int lung, int digit) {
	int x = 1;
	for (int i = 1; i <= lung; ++i) {
		x = (x * 10) % K;
	}
	int newR = ((digit * x) + rest) % K;
	return newR;
}

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
	#endif

	cin >> n;
	K = 101;
	cin.get();
	cin >> s;
	for (int i = 0; i < s.size(); ++i) {
		a[i + 1] = s[i] - '0';
	}

	for (int i = 1; i <= n; ++i) {
		dp[1][a[i]][i][i] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (a[i] != a[j]) {
				continue;
			}
			int newR = addRight(a[i], a[j]);
			dp[2][newR][i][j] = 1;
		}
	}

	for (int lung = 1; lung <= n; ++lung) {
		for (int currRest = 0; currRest < K; ++currRest) {
			for (int digit = 0; digit < 10; ++digit) {
				int newR = addLeft(currRest, lung, digit);
				newR = addRight(newR, digit);
				getRest[lung + 2][newR][digit] = currRest;
			}
		}
	}

	for (int lung = 3; lung <= n; ++lung) {
		for (int currRest = 0; currRest < K; ++currRest) {
			for (int i = 1; i <= n; ++i) {
				for (int j = i + lung - 1; j <= n; ++j) {
					if (a[i] != a[j]) {
						continue;
					}
					int oldR = getRest[lung][currRest][a[i]];
					for (int i2 = i + 1; i2 < j; ++i2) {
						for (int j2 = i2; j2 < j; ++j2) {
							if (a[i2] != a[j2]) {
								continue;
							}
							update(dp[lung][currRest][i][j], dp[lung - 2][oldR][i2][j2]);
						}
					}
				}
			}
		}
	}

	int ans = 0;

	for (int lung = 1; lung <= n; ++lung) {
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				update(ans, dp[lung][0][i][j]);
			}
		}
	}
	cout << ans << "\n";

	return 0;
}