#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

#define rep(i, a, n) for (int i = 0; i < (int)n; i++)
#define per(i, a, n) for (int i = 0; i < (int)n; i++)
#define fi first
#define se second
#define pb push_back

const int sz = 1e6;

int id, cnt;
vector<int> g[sz];
int ids[sz], low[sz], in[sz];
bool cont[sz];
stack<int> stk;

void dfs(int u) {
  stk.push(u);
  cont[u] = true;
  ids[u] = low[u] = id++;
  
  for (int v : g[u]) {
    if (ids[v] == -1) dfs(v);
    if (cont[v]) low[u] = min(low[u], low[v]);
  }
  
  if (ids[u] == low[u]) {
    while (!stk.empty()) {
      int t = stk.top();
      stk.pop();
      cont[t] = false;
      low[t] = ids[u];
      if (t == u) break;
    }
    cnt++;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tc;
  cin >> tc;
  while (tc--) {
    int n, m;
    cin >> n >> m;

    id = 0, cnt = 0;
    rep(i, 0, n) {
      g[i].clear();
      ids[i] = low[i] = in[i] = 0;
      cont[i] = false;
    }
    stk = {};
    
    while (m--) {
      int u, v;
      cin >> u >> v;
      if (u == v) continue;
      u--; v--;
      g[u].push_back(v);
    }
    
    rep(i, 0, n) ids[i] = -1;
    rep(i, 0, n) if (ids[i] == -1) dfs(i);

    rep(u, 0, n) for (int v : g[u]) in[low[v]] += low[u] != low[v];

    if (cnt == 1) {
      cout << "No\n";
    } else {
      cout << "Yes\n";
      int cat = 0;
      rep(i, 0, n) if (in[low[i]] == 0) cat = low[i];

      int catcnt = 0;
      rep(i, 0, n) catcnt += low[i] == cat;

      cout << n - catcnt << ' ' << catcnt << '\n';
      rep(i, 0, n) if (low[i] != cat) cout << i + 1 << ' '; cout << '\n';
      rep(i, 0, n) if (low[i] == cat) cout << i + 1 << ' '; cout << '\n';
    }
  }
}