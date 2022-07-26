#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define fi first
#define se second
#define pb push_back

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  vector<vector<int>> rev(n);
  rep(i, m) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    g[u].pb(v);
    rev[v].pb(u);
  }
  int k;
  cin >> k;
  vector<int> p(k);
  rep(i, k) {
    cin >> p[i];
    p[i]--;
  }

  queue<int> q;
  vector<int> dist(n, -1);
  q.push(p[k - 1]);
  dist[p[k - 1]] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : rev[u]) {
      if (dist[v] == -1) {
        q.push(v);
        dist[v] = dist[u] + 1;
      }
    }
  }

  int mn = 0, mx = 0;
  rep(i, k - 1) {
    mn += dist[p[i + 1]] != dist[p[i]] - 1;
    int u = p[i];
    bool flag = false;
    for (int v : g[u]) {
      if (v != p[i + 1] && dist[v] == dist[u] - 1) {
        flag = true;
        break;
      }
    }
    mx += flag;
  }
  cout << mn << ' ' << mx << '\n';
}