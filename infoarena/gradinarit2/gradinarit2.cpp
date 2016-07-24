#include <bits/stdc++.h>

using namespace std;

ifstream f("gradinarit2.in");
ofstream g("gradinarit2.out");

#define pb push_back
#define ll long long
#define mp make_pair

const int nmax = 61;
const int inf = (1 << 29);

int n, m;
string s;
int dp[nmax][nmax][nmax];
int a[nmax];

void update(int &x, int y) {
	x = min(x, y);
}

int bagaDp() {
	// dp[i][j][k] = nr minim de doze pt intervalul [i..j] stiind ca ultima doza e k
	int n = m;
	int lim = 26;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 0; k < 26; ++k) {
				dp[i][j][k] = inf;
			}
		}
		for (int k = 0; k < lim; ++k) {
			if (a[i] == k) {
				dp[i][i][k] = 1;
			} else {
				dp[i][i][k] = 2;
			}
		}
	}
	for (int lung = 2; lung <= n; ++lung) {
		for (int i = 1; i <= n; ++i) {
			int j = i + lung - 1;
			if (j > n) {
				break;
			}
			for (int k = 0; k < lim; ++k) {
				for (int t = i; t < j; ++t) {
					int minDreapta = inf;
					for (int k2 = 0; k2 < lim; ++k2) {
						if (k2 == k) {
							minDreapta = min(minDreapta, dp[t + 1][j][k2] - 1);
						} else {
							minDreapta = min(minDreapta, dp[t + 1][j][k2]);
						}
					}
					update(dp[i][j][k], dp[i][t][k] + minDreapta);
				}
				//cout << k << " " << i << " " << j << " " << dp[i][j][k] << "\n";
			}
		}
	}

	int minT = inf;
	for (int k = 0; k < lim; ++k) {
		minT = min(minT, dp[1][n][k]);
	}
	return minT;

}

int main() {
	f >> n >> m;
	int ans = 0;
	f.get();
	for (int i = 1; i <= n; ++i) {
		getline(f, s);
		int j2 = 1;
		for (int j = 0; j < s.size(); ++j) {
			if (j % 2 == 0) {
				a[j2] = s[j] - 'A';
				++j2;
			}
		}
		// for (int j = 1; j <= m; ++j) {
		// 	cout << a[j] << " ";
		// }
		// //cout << "\n";
		ans += bagaDp();
	}
	cout << ans << "\n";
	g << ans << "\n";
	return 0;
}