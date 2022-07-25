#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  vector<int> in(n);
  for (int i = 0; i < n; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    g[u].push_back(v);
    g[v].push_back(u);
    in[u]++;
    in[v]++;
  }
  vector<bool> cycle(n, true);
  queue<int> q1;
  for (int i = 0; i < n; i++) {
    if (in[i] == 1) {
      q1.push(i);
      cycle[i] = false;
    }
  }
  while (!q1.empty()) {
    int u = q1.front();
    q1.pop();
    for (int v : g[u]) {
      if (--in[v] == 1) {
        q1.push(v);
        cycle[v] = false;
      }
    }
  }
  queue<int> q2;
  vector<int> dist(n, -1);
  for (int i = 0; i < n; i++) {
    if (cycle[i]) {
      q2.push(i);
      dist[i] = 0;
    }
  }
  while (!q2.empty()) {
    int u = q2.front();
    q2.pop();
    for (int v : g[u]) {
      if (dist[v] == -1) {
        q2.push(v);
        dist[v] = dist[u] + 1;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    cout << dist[i] << ' ';
  }
}