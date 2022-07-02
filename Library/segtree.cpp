#include <bits/stdc++.h>
using namespace std;

struct segtree {
  int sz;
  vector<int> t;

  void init(int n) {
    sz = 1;
    while (sz < n) {
      sz *= 2;
    }
    t.resize(sz);
  }

  void set(int i, int v, int x, int l, int r) {
    if (l + 1 == r) {
      t[x] = v;
      return;
    }
    int mid = l + (r - l) / 2;
    if (i < mid) {
      set(i, v, 2 * x + 1, l, mid);
    } else {
      set(i, v, 2 * x + 2, mid, r);
    }
    t[x] = t[2 * x + 1] + t[2 * x + 2];
  }

  void set(int i, int v) {
    set(i, v, 0, 0, sz);
  }

  void build(vector<int> a, int x, int l, int r) {
    if (l + 1 == r) {
      if (l < (int)a.size()) {
        t[x] = a[l];
      }
      return;
    }
    int mid = l + (r - l) / 2;
    build(a, 2 * x + 1, l, mid);
    build(a, 2 * x + 2, mid, r);
    t[x] = t[2 * x + 1] + t[2 * x + 2];
  }

  void build(vector<int> a) {
    build(a, 0, 0, sz);
  }

  int query(int l, int r, int x, int lx, int rx) {
    if (lx >= r || rx < l) {
      return 0;
    }
    if (lx >= l && rx <= r) {
      return t[x];
    }
    int mid = lx + (rx - lx) / 2;
    return query(l, r, 2 * x + 1, lx, mid) + query(l, r, 2 * x + 1, mid, rx);
  }

  int query(int l, int r) {
    return query(l, r, 0, 0, sz);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
}