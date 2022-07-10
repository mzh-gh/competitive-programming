#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

struct mergetree {
  int sz;
  vector<vector<int>> tree;

  void init(int n) {
    sz = 1;
    while (sz < n) {
      sz *= 2;
    }
    tree.resize(2 * sz);
  }

  void build(vector<int> &a, int x, int l, int r) {
    if (l + 1 == r) {
      if (l < sz(a)) {
        tree[x] = {a[l]};
      }
      return;
    }
    int mid = l + (r - l) / 2;
    build(a, 2 * x + 1, l, mid);
    build(a, 2 * x + 2, mid, r);
    merge(all(tree[2 * x + 1]), all(tree[2 * x + 2]), back_inserter(tree[x]));
  }

  void build(vector<int> &a) {
    build(a, 0, 0, sz);
  }

  int query(int L, int R, int v, int x, int l, int r) {
    if (l >= R || r <= L) {
      return 0;
    }
    if (l >= L && r <= R) {
      return lower_bound(all(tree[x]), v) - tree[x].begin(); // Elements < v
    }
    int mid = l + (r - l) / 2;
    return query(L, R, v, 2 * x + 1, l, mid) + query(L, R, v, 2 * x + 2, mid, r);
  }

  int query(int l, int r, int v) {
    return query(l, r, v, 0, 0, sz);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
}