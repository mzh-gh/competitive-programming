#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct segtree {
  int sz;
  vector<int> t;

  void init(int n) {
    sz = 1;
    while (sz < n) {
      sz *= 2;
    }
    t.resize(2 * sz);
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

  int query(int l, int r, int x, int k) {
    if (l + 1 == r) {
      return l;
    }
    int mid = l + (r - l) / 2;
    if (t[2 * x + 1] < k) {
      return query(mid, r, 2 * x + 2, k - t[2 * x + 1]);
    }
    return query(l, mid, 2 * x + 1, k);
  }

  int query(int k) {
    return query(0, sz, 0, k);
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
  while (m--) {
    int op;
    cin >> op;
    if (op == 1) {
      int i;
      cin >> i;
      a[i] ^= 1;
      st.set(i, a[i]);
    } else {
      int k;
      cin >> k;
      k++;
      // Query k
      cout << st.query(k) << '\n';
    }
  }
}