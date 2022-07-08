#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tc;
  cin >> tc;
  while (tc--) {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;
    vector<int> pref(n), suf(n); // Prefix/suffix of t as a substring in the first (i + 1) chars of s
    int idx = 0;
    for (int i = 0; i < n; i++) {
      if (idx < m && s[i] == t[idx]) {
        idx++;
      }
      pref[i] = idx;
    }
    idx = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (idx < m && s[i] == t[m - idx - 1]) {
        idx++;
      }
      suf[i] = idx;
    }
    int ans = 1e9;
    int finl = 0, finr = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int cost = (i + 1) + (n - j) + 1;
        if (pref[i] + suf[j] >= m && cost < ans) {
          ans = cost;
          finl = i + 1;
          finr = j + 1;
        }
      }
    }
    cerr << finl << ' ' << finr << '\n';
    cout << (ans == 1e9 ? -1 : ans) << '\n';
  }
}