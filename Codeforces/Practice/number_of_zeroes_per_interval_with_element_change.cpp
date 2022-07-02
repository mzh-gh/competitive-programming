#include <bits/stdc++.h>
using namespace std;

struct segtree {
  int sz;
  vector<long long> t;

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
        t[x] = a[l];
      }
      return;
    }
    int mid = l + (r - l) / 2;
    build(a, 2 * x + 1, l, mid);
    build(a, 2 * x + 2, mid, r);
    t[x] = t[2 * x + 1] + t[2 * x + 2];
  }

  void build(vector<int> &a) {
    build(a, 0, 0, sz);
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

  long long query(int l, int r, int x, int lx, int rx) {
    if (lx >= r || l >= rx) {
      return 0;
    }
    if (lx >= l && rx <= r) {
      return t[x];
    }
    int mid = lx + (rx - lx) / 2;
    return query(l, r, 2 * x + 1, lx, mid) + query(l, r, 2 * x + 2, mid, rx);
  }

  long long query(int l, int r) {
    return query(l, r, 0, 0, sz);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> is_zero(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    is_zero[i] = x == 0;
  }
  segtree st;
  st.init(n);
  st.build(is_zero);
  int m;
  cin >> m;
  while (m--) {
    char c;
    cin >> c;
    if (c == 'u') {
      int i, v;
      cin >> i >> v;
      i--;
      st.set(i, v == 0);
    } else {
      int l, r;
      cin >> l >> r;
      l--;
      cout << st.query(l, r) << ' ';
    }
  }
}