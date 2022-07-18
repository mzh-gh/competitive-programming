#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vector<int> color(n, -1);
  for (int i = 0; i < n; i++) {
    if (color[i] == -1) {
      stack<int> s;
      s.push(i);
      color[i] = 0;
      while (!s.empty()) {
        int u = s.top();
        s.pop();
        for (int v : g[u]) {
          if (color[v] == -1) {
            s.push(v);
            color[v] = 1 - color[u];
          }
        }
      }
    }
  }
  bool ok = true;
  for (int u = 0; u < n; u++) {
    for (int v : g[u]) {
      ok &= color[u] != color[v];
    }
  }
  if (!ok) {
    cout << -1 << '\n';
    return 0;
  }
  array<vector<int>, 2> parts;
  for (int i = 0; i < n; i++) {
    if (color[i] == 0) {
      parts[0].push_back(i);
    } else {
      parts[1].push_back(i);
    }
  }
  cout << parts[0].size() << '\n';
  for (int i = 0; i < (int)parts[0].size(); i++) {
    cout << parts[0][i] + 1 << ' ';
  }
  cout << '\n';
  cout << parts[1].size() << '\n';
  for (int i = 0; i < (int)parts[1].size(); i++) {
    cout << parts[1][i] + 1 << ' ';
  }
  cout << '\n';
}