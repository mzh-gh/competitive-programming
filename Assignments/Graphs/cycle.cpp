#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

#define FOR(i, a, n) for (int i = 0; i < (int)n; i++)
#define ROF(i, a, n) for (int i = 0; i < (int)n; i++)
#define fi first
#define se second

// INCOMPLETE

const int MAXN = 5000;

int n;
bool adj[MAXN][MAXN];
bool vis[MAXN], in_path[MAXN];

vi st, cycle;

void dfs(int u) {
  if (!cycle.empty()) {
    return;
  }
  vis[u] = true;
  in_path[u] = true;
  st.push_back(u);
  FOR(v, 0, n) {
    if (!adj[u][v]) {
      continue;
    }
    if (in_path[v]) {
      int id = 0;
      while (st[id] != v) {
        id++;
      }
      FOR(i, id, st.size()) {
        cycle.push_back(st[i]);
      }
    } else if (!vis[v]) {
      dfs(v);
    }
  }
  in_path[u] = false;
  st.pop_back();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      char c;
      cin >> c;
      adj[i][j] = c == '1';
    }
  }
  FOR(i, 0, n) {
    if (!vis[i]) {
      dfs(i);
    }
  }
  if (cycle.empty()) {
    cout << -1;
  } else {

    // DEBUG
    FOR(i, 0, cycle.size()) {
      cout << cycle[i] + 1 << ' ';
    }
    cout << '\n';
    cout << adj[cycle.back()][cycle[0]] << '\n';
    
    
    FOR(i, 2, cycle.size()) {
      if (adj[cycle[i]][cycle[0]]) {
        cout << cycle[0] + 1 << ' ' << cycle[i - 1] + 1 << ' ' << cycle[i] + 1;
        return 0;
      }
    }
  }
}