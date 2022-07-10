#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

struct segtree {
  int sz;
  vector<ll> tree;
  vector<ll> lazy;

  void init(int n) {
    sz = 1;
    while (sz < n) {
      sz *= 2;
    }
    tree.resize(n);
    lazy.resize(n);
  }

  void build(vector<int> &a, int x, int l, int r) {
    if (l == r - 1) {
      if (l < sz(a)) {
        tree[x] = a[l];
      }
    }
    int mid = l + (r - l) / 2;
    build(a, 2 * x + 1, l, mid);
    build(a, 2 * x + 2, mid, r);
    tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
  }

  void update(int L, int R, int x, int l, int r, int v) {
    if (lazy[x] != 0) {
      tree[x] += (r - l + 1) * lazy[x];
      if (l != r - 1) {
        lazy[2 * x + 1] += lazy[x];
        lazy[2 * x + 2] += lazy[x];
      }
      lazy[x] = 0;
    }
    if (l >= R || r <= L) {
      return;
    }
    if (l >= L && r <= R) {
      tree[x] += (r - l + 1) * v;
      if (l != r - 1) {
        lazy[2 * x + 1] += v;
        lazy[2 * x + 2] += v;
      }
      return;
    }
    int mid = l + (r - l) / 2;
    update(L, R, 2 * x + 1, l, mid, v);
    update(L, R, 2 * x + 2, mid, r, v);
    tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
  }

  ll query(int L, int R, int x, int l, int r) {
    if (lazy[x] != 0) {
      tree[x] += (r - l + 1) * lazy[x];
      if (l != r - 1) {
        lazy[2 * x + 1] += lazy[x];
        lazy[2 * x + 2] += lazy[x];
      }
      lazy[x] = 0;
    }
    if (l >= R || r <= L) {
      return 0;
    }
    if (l >= L && r <= R) {
      return tree[x];
    }
    int mid = l + (r - l) / 2;
    return query(L, R, 2 * x + 1, l, mid) + query(L, R, 2 * x + 2, mid, r);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
}

