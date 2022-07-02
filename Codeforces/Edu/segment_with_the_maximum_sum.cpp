#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct segment {
  ll mx, sum, pref, suf;
};

struct segtree {
  int sz;
  vector<segment> t;

  void init(int n) {
    sz = 1;
    while (sz < n) {
      sz *= 2;
    }
    t.resize(2 * sz);
  }

  segment single(int v) {
    int x = max(v, 0);
    return {x, v, x, x};
  }

  segment comb(segment a, segment b) {
    segment c;
    c.mx = max({a.mx, b.mx, a.suf + b.pref});
    c.sum = a.sum + b.sum;
    c.pref = max(a.pref, a.sum + b.pref);
    c.suf = max(b.suf, b.sum + a.suf);
    return c;
  }

  void set(int i, int v, int x, int l, int r) {
    if (l + 1 == r) {
      t[x] = single(v);
      return;
    }
    int mid = l + (r - l) / 2;
    if (i < mid) {
      set(i, v, 2 * x + 1, l, mid);
    } else {
      set(i, v, 2 * x + 2, mid, r);
    }
    t[x] = comb(t[2 * x + 1], t[2 * x + 2]);
  }

  void set(int i, int v) {
    set(i, v, 0, 0, sz);
  }

  void build(vector<int> a, int x, int l, int r) {
    if (l + 1 == r) {
      if (l < (int)a.size()) {
        t[x] = single(a[l]);
      }
      return;
    }
    int mid = l + (r - l) / 2;
    build(a, 2 * x + 1, l, mid);
    build(a, 2 * x + 2, mid, r);
    t[x] = comb(t[2 * x + 1], t[2 * x + 2]);
  }

  void build(vector<int> a) {
    build(a, 0, 0, sz);
  }

  segment query(int l, int r, int x, int lx, int rx) {
    if (lx >= r || rx < l) {
      return single(0);
    }
    if (lx >= l && rx <= r) {
      return t[x];
    }
    int mid = lx + (rx - lx) / 2;
    return comb(query(l, r, 2 * x + 1, lx, mid), query(l, r, 2 * x + 2, mid, rx));
  }

  int query(int l, int r) {
    return query(l, r, 0, 0, sz).mx;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  segtree st;
  st.init(n);
  st.build(a);
  cout << st.query(0, n) << '\n';
  while (m--) {
    int i, v;
    cin >> i >> v;
    st.set(i, v);
    cout << st.query(0, n) << '\n';
  }
}