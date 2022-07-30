#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, n) for (int i = 0; i < (int)n; i++)
#define per(i, a, n) for (int i = 0; i < (int)n; i++)

const int N = 1e6;
int n, m;
int id, cnt;
vector<int> g[N];
int ids[N], low[N];
bool inStk[N];
stack<int> stk;

void dfs(int u) {
  stk.push(u);
  inStk[u] = true;
  ids[u] = low[u] = id++;
  
  for (int v : g[u]) {
    if (ids[v] == -1) dfs(v);
    if (inStk[v]) low[u] = min(low[u], low[v]);
  }
  
  if (ids[u] == low[u]) {
    while (!stk.empty()) {
      int t = stk.top();
      stk.pop();
      inStk[t] = false;
      low[t] = ids[u];
      if (t == u) break;
    }
    cnt++;
  }
}

void getScc() {
  rep(i, 0, n) ids[i] = -1;
  rep(i, 0, n) if (ids[i] == -1) dfs(i);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tc;
  cin >> tc;
  while (tc--) {
    cin >> n >> m;

    id = 0, cnt = 0;
    rep(i, 0, n) {
      g[i].clear();
      ids[i] = 0;
      low[i] = 0;
      inStk[i] = false;
    }
    stk = {};
    
    while (m--) {
      int u, v;
      cin >> u >> v;
      if (u == v) continue;
      u--; v--;
      g[u].push_back(v);
    }
    
    getScc();

    if (cnt == 1) {
      cout << "No\n";
    } else {
      cout << "Yes\n";
      int jury = 0;
      rep(i, 0, n) jury += low[i] == 0;
      cout << jury << ' ' << n - jury << '\n';
      // rep(i, 0, n) if (low[i] == 0) cout << i + 1 << ' '; cout << '\n';
      // rep(i, 0, n) if (low[i] != 0) cout << i + 1 << ' '; cout << '\n';
      rep(i, 0, n) cout << low[i] << ' '; cout << '\n';
    }
  }
}