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

const int sz = 1e5;

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

  // Input graph, etc
  int n = sz;
  
  rep(i, 0, n) ids[i] = -1;
  rep(i, 0, n) if (ids[i] == -1) dfs(i);

  // low[i] = SCC of vertex i
}