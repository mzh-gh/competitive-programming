#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

vector<int> dr{-1, 0, 1, 0}, dc{0, 1, 0, -1};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> comp(n, vector<int>(m));
  vector<int> size(n * m + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c;
      cin >> c;
      if (c == '*') {
        comp[i][j] = -1;
      }
    }
  }
  auto ck = [&](int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
  };
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (comp[i][j] == 0) {
        stack<pair<int, int>> s;
        s.push({i, j});
        comp[i][j] = ++cnt;
        size[cnt] = 1;
        while (!s.empty()) {
          auto [r, c] = s.top();
          s.pop();
          for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (ck(nr, nc) && comp[nr][nc] == 0) {
              s.push({nr, nc});
              comp[nr][nc] = cnt;
              size[cnt]++;
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (comp[i][j] == -1) {
        int ans = 1;
        set<int> st;
        for (int k = 0; k < 4; k++) {
          int r = i + dr[k], c = j + dc[k];
          if (ck(r, c) && comp[r][c] != -1 && !st.count(comp[r][c])) {
            ans = (ans + size[comp[r][c]]) % 10;
            st.insert({comp[r][c]});
          }
        }
        cout << ans;
      } else {
        cout << '.';
      }
    }
    cout << '\n';
  }
}