#include <bits/stdc++.h>

using namespace std;

ifstream f("maxpal.in");
ofstream g("maxpal.out");

#define pb push_back
#define ll long long
#define mp make_pair

const int nmax = 2005;
const int mod = 666013;

int dp[nmax][nmax];
int cnt[nmax][nmax];
int n, a[nmax];

void updateCnt(int &x, int y) {
	x += y;
	if (x >= 0) {
		x %= mod;
	} else {
		x += mod;
	}
}
void updateMax(int &x, int y) {
	x = max(x, y);
}
int main() {
	f >> n;
	for (int i = 1; i <= n; ++i) {
		f >> a[i];
	}

	// for (int lung = 1; lung <= n; ++lung) {
	// 	for (int i = 1; i + lung - 1 <= n; ++i) {
	// 		int j = i + lung - 1;
	int currLine = 1;
	for (int i = n; i >= 1; --i) {
		int prevLine = 1 ^ currLine;
		for (int j = i; j <= n; ++j) {
			int lung = (j - i + 1);
			if (lung == 1) {
				dp[currLine][j] = 1;
				cnt[currLine][j] = 1;
				continue;
			} else if (lung == 2) {
				if (a[i] == a[j]) {
					dp[currLine][j] = 2;
					cnt[currLine][j] = 1;
				} else {
					dp[currLine][j] = 1;
					cnt[currLine][j] = 2;
				}
				continue;
			}
			if (a[i] != a[j] ||
			        (a[i] == a[j] &&
			         dp[prevLine][j - 1] + 2 < max(dp[prevLine][j], dp[currLine][j - 1]))) {
				updateMax(dp[currLine][j], max(dp[prevLine][j], dp[currLine][j - 1]));
				if (dp[prevLine][j] == dp[currLine][j - 1]) {
					updateCnt(cnt[currLine][j], cnt[prevLine][j]);
					updateCnt(cnt[currLine][j], cnt[currLine][j - 1]);
					if (dp[prevLine][j] == dp[prevLine][j - 1]) updateCnt(cnt[currLine][j], -cnt[prevLine][j - 1]);
				} else if (dp[prevLine][j] > dp[currLine][j - 1]) {
					updateCnt(cnt[currLine][j], cnt[prevLine][j]);
				} else {
					updateCnt(cnt[currLine][j], cnt[currLine][j - 1]);
				}
				continue;
			}
			updateMax(dp[currLine][j], dp[prevLine][j - 1] + 2); // dp[i][j] = dp[i + 1][j - 1] + 2;
			updateCnt(cnt[currLine][j], cnt[prevLine][j - 1]); // cnt[i][j] = cnt[i + 1][j - 1];
			if (dp[currLine][j] == dp[prevLine][j]) {
				updateCnt(cnt[currLine][j], cnt[prevLine][j]);
			}
			if (dp[currLine][j] == dp[currLine][j - 1]) {
				updateCnt(cnt[currLine][j], cnt[currLine][j - 1]);
			}
		}
		currLine = prevLine;
		for (int j = 1; j <= n; ++j) {
			dp[currLine][j] = 0;
			cnt[currLine][j] = 0;
		}
	}
	//cout << dp[2][5] << " " << cnt[2][4] << "\n";
	g << dp[1 ^ currLine][n] << " " << cnt[1 ^ currLine][n] << "\n";
	return 0;
}