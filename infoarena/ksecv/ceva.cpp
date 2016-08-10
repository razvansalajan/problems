#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

char getNewChar(char c) {
	c = c - 29;

	return c;
}

char getPrevChar(char c) {
	c += 29;
	return c;
}

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
	#endif

	string s = "A_a_i_S_F_i_b_l_R";
	string s2 = "";
	for (int i = 0; i < s.size(); ++i) {
		s2 += getNewChar(s[i]);
	}
	cout << s2 << "\n";
	string s3 = "";
	for (int i = 0; i < s2.size(); ++i) {
		s3 += getPrevChar(s2[i]);
	}
	cout << s3 << "\n";
	return 0;
}