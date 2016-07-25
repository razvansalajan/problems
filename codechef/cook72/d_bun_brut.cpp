#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int nmax = 1e5 + 5;
int n, q;
int a[nmax];

vector<int> getDig(int x) {
	vector<int> v;
	for (; x; x /= 10) {
		v.pb(x % 10);
	}
	reverse(v.begin(), v.end());
	return v;
}

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
	#endif

	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	for (; q; --q) {
		int tip, x, y;
		cin >> tip >> x >> y;
		if (tip == 1) {
			a[x] = y;
		} else {
			int mat[11][11];
			for (int i = 0; i < 11; ++i) {
				for (int j = 0; j < 11; ++j) {
					mat[i][j] = 0;
				}
			}
			for (int i = x; i <= y; ++i) {
				vector<int> digits = getDig(a[i]);
				for (int j = 0; j < digits.size(); ++j) {
					//cout << digits[j] << " ";
					++mat[j + 1][digits[j]];
				}
				//cout << "\n";
			}
			int nr = 0;
			bool foundGlobal = true;
			int len = (y - x + 1) / 2;
			vector<int>possible;
			for (int i = 1; i < 11; ++i) {
				int found = 0;
				for (int cifra = 0; cifra < 10; ++cifra) {
					//cout << i << " " << mat[i][cifra] << " " << cifra  << len <<  "\n";
					if (mat[i][cifra] > len) {
						//cout << "muie";
						found = 1;
						nr = nr * 10 + cifra;
						break;
					}
				}
				if (found) {
					possible.pb(nr);
				} else {
					break;
				}
			}
			//cout << nr << "\n";
			foundGlobal = false;
			for (int i = x; i <= y; ++i) {
				for (int j = 0; j < possible.size(); ++j) {
					if (a[i] == possible[j]) {
						foundGlobal = true;
						break;
					}
				}
			}
			if (!foundGlobal) {
				cout << "No\n";
			} else {
				cout << "Yes\n";
			}
		}
	}

	return 0;
}