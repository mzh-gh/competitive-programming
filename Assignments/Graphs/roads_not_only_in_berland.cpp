#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<pair<int, int>> e(n - 1);
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    e[i] = {u, v};
    g[u].push_back(v);
    g[v].push_back(u);
  }

  vector<pair<int, int>> rem;
  for (auto [ex_u, ex_v] : e) {
    stack<int> s;
    vector<bool> conn(n);
    s.push(ex_u);
    conn[ex_u] = true;
    while (!s.empty()) {
      int u = s.top();
      s.pop();
      for (int v : g[u]) {
        if (!conn[v] && !((u == ex_u && v == ex_v) || (u == ex_v && v == ex_u))) {
          s.push(v);
          conn[v] = true;
        }
      }
    }
    if (conn[ex_u] == conn[ex_v]) {
      g[ex_u].erase(find(g[ex_u].begin(), g[ex_u].end(), ex_v));
      g[ex_v].erase(find(g[ex_v].begin(), g[ex_v].end(), ex_u));
      rem.push_back({ex_u, ex_v});
    }
  }

  cout << rem.size() << '\n';

  int cnt = 0;
  vector<int> comp(n, -1);
  for (int i = 0; i < n; i++) {
    if (comp[i] == -1) {
      stack<int> s;
      s.push(i);
      comp[i] = cnt++;
      while (!s.empty()) {
        int u = s.top();
        s.pop();
        for (int v : g[u]) {
          if (comp[v] == -1) {
            s.push(v);
            comp[v] = comp[u];
          }
        }
      }
    }
  }

  vector<int> merge(n);
  iota(merge.begin(), merge.end(), 0);
  for (int u = 0; u < n; u++) {
    for (int v = u + 1; v < n; v++) {
      if (merge[comp[u]] != merge[comp[v]]) {
        merge[comp[v]] = merge[comp[u]];

        auto [ex_u, ex_v] = rem.back();
        rem.pop_back();
        cout << ex_u + 1 << ' ' << ex_v + 1 << ' ' << u + 1 << ' ' << v + 1 << '\n';
      }
    }
  }
}