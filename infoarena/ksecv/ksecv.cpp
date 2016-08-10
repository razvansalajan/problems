#include <bits/stdc++.h>

using namespace std;

ifstream f("ksecv.in");
ofstream g("ksecv.out");

#define pb push_back
#define ll long long
#define mp make_pair

struct MyStruct {
	MyStruct() {}
	MyStruct(int x, int y) {
		pos = x;
		val = y;
	}
	int pos, val;
};

const int nmax = 1e5 + 5;
const int inf = (1 << 30);
const int kmax = 1e3 + 5;

int dp[2][nmax];
int n, K;
int a[nmax];
MyStruct st[nmax];

void update(int &x, int y) {
	x = min(x, y);
}

int main() {
	f >> n >> K;
	for (int i = 1; i <= n; ++i) {
		f >> a[i];
		assert(a[i] >= 0 && a[i] <= 10000000);
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j <= n; ++j) {
			dp[i][j] = inf;
		}
	}
	a[0] = inf;
	int currLine = 0;
	dp[1 ^ currLine][0] = 0;
	for (int i = 1; i <= K; ++i) {
		//stack<MyStruct> st;
		//st.push(MyStruct(0, 0));
		int index = 0;
		st[ ++index] = MyStruct(0, 0);

		int prevLine = 1 ^ currLine;
		for (int j = 0; j <= n; ++j) {
			dp[currLine][j] = inf;
		}
		for (int j = 1; j <= n; ++j) {
			int minn = inf;
			while (index > 0 &&
			        a[j] >= a[ st[index].pos ]) {
				int val = st[index].val;
				update(minn, val);
				--index;
			}
			int pos = st[index].pos;
			//cout << i << " " << j << " " << minn << " " << minn << "\n";
			if (minn == inf) {
				update(dp[currLine][j], dp[prevLine][pos] + a[j]);
			} else {
				update(dp[currLine][j], minn + a[j]);
			}
			update(minn, dp[prevLine][j]);
			st[++index] = MyStruct(j, minn);
			update(dp[currLine][j], dp[currLine][pos]);
			//cout << i << " " << j << " " << dp[i][j] << " " << minn << "\n";
		}
		currLine = prevLine;
	}
	cout << dp[1 ^ currLine][n] << "\n";
	g << dp[1 ^ currLine][n] << "\n";

	return 0;
}