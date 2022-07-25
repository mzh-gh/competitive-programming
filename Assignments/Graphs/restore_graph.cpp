#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define fi first
#define se second

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  vector<pair<int, int>> d(n);
  for (int i = 0; i < n; i++) {
    cin >> d[i].fi;
    d[i].se = i;
  }
  sort(all(d));

  bool valid = true;
  vector<pair<int, int>> res;
  vector<int> deg(n);
  queue<int> prev, cur;

  cur.push(d[0].se);
  valid &= d[0].fi == 0;

  for (int i = 1; i < n; i++) {
    if (d[i].fi != d[i - 1].fi) {
      prev = cur;
      cur = {};
    }

    if (abs(d[i].fi - d[i - 1].fi) > 1 || prev.empty()) {
      valid = false;
      break;
    }

    int prev_v = prev.front(), cur_v = d[i].se;
    res.push_back({prev_v, cur_v});
    deg[prev_v]++;
    deg[cur_v]++;

    if (deg[prev_v] > k || deg[cur_v] > k) {
      valid = false;
      break;
    }

    prev.push(prev_v);
    prev.pop();
    cur.push(cur_v);
  }

  if (!valid) {
    cout << -1;
    return 0;
  }

  cout << sz(res) << '\n';
  for (int i = 0; i < sz(res); i++) {
    cout << res[i].fi + 1 << ' ' << res[i].se + 1 << '\n';
  }
}