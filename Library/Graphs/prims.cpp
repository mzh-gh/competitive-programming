#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--; v--;
    g[u].push_back({w, v});
    g[v].push_back({w, u});
  }
  // O((V + E) * log(V))
  int ans = 0;
  vector<int> cost(n, 1e9);
  vector<int> vis(n);
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
  cost[0] = 0;
  q.push({0, 0});
  while (!q.empty()) {
    auto [w, u] = q.top();
    q.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = true;
    ans += w;
    for (auto [edge_w, v] : g[u]) {
      if (!vis[v] && edge_w < cost[v]) {
        cost[v] = edge_w;
        q.push({edge_w, v});
      }
    }
  }
  cout << ans;
}