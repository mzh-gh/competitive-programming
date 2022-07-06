#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

int sz;
vector<vector<int>> t;

void init(int n) {
  sz = 1;
  while (sz < n) {
    sz *= 2;
  }
  t.resize(2 * sz);
}

void build(vector<int> &a, int x, int l, int r) {
  if (l + 1 == r) {
    if (l < (int)a.size()) {
      t[x] = {a[l]};
    }
    return;
  }
  int mid = l + (r - l) / 2;
  build(a, 2 * x + 1, l, mid);
  build(a, 2 * x + 2, mid, r);
  merge(all(t[2 * x + 1]), all(t[2 * x + 2]), back_inserter(t[x]));
}

void build(vector<int> &a) {
  build(a, 0, 0, sz);
}

int query(int l, int r, int v, int x, int lx, int rx) {
  if (lx >= r || rx <= l) {
    return 0;
  }
  if (lx >= l && rx <= r) {
    return upper_bound(all(t[x]), 1) - t[x].begin();
  }
  int mid = lx + (rx - lx) / 2;
  return query(l, r, v, 2 * x + 1, lx, mid) + query(l, r, v, 2 * x + 2, mid, rx);
}

int query(int l, int r, int v) {
  return query(l, r, v, 0, 0, sz);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
}