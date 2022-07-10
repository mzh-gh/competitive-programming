#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

struct segtree {
  int sz;
  vector<long long> tree;

  void init(int n) {
    sz = 1;
    while (sz < n) {
      sz *= 2;
    }
    tree.resize(2 * sz);
  }

  void upd(int L, int R, int v, int x, int l, int r) {
    if (l >= R || r <= L) {
      return;
    }
    if (l >= L && r <= R) {
      tree[x] += v;
      return;
    }
    int mid = l + (r - l) / 2;
    upd(L, R, v, 2 * x + 1, l, mid);
    upd(L, R, v, 2 * x + 2, mid, r);
  }

  void upd(int l, int r, int v) {
    upd(l, r, v, 0, 0, sz);
  }

  void build(vector<int> &a, int x, int l, int r) {
    if (l + 1 == r) {
      if (l < sz(a)) {
        tree[x] = a[l];
      }
      return;
    }
    int mid = l + (r - l) / 2;
    build(a, 2 * x + 1, l, mid);
    build(a, 2 * x + 2, mid, r);
  }

  void build(vector<int> &a) {
    build(a, 0, 0, sz);
  }

  long long query(int i, int x, int l, int r) {
    if (l + 1 == r) {
      return tree[x];
    }
    long long ans = tree[x];
    int mid = l + (r - l) / 2;
    if (i < mid) {
      ans += query(i, 2 * x + 1, l, mid);
    } else {
      ans += query(i, 2 * x + 2, mid, r);
    }
    return ans;
  }

  long long query(int i) {
    return query(i, 0, 0, sz);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
}