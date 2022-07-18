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
    if (l < sz(a)) {
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
    // (values <= v) + (values > v) = sz
    // sz - (values <= v) = (values > v)
    return rx - lx - (upper_bound(all(t[x]), v) - t[x].begin());
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
  int n;
  cin >> n;
  vector<int> A(n);
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }
  init(n);
  build(A);
  int q;
  cin >> q;
  int last = 0;
  while (q--) {
    int a, b, c;
    cin >> a >> b >> c;
    int l = last ^ a, r = last ^ b, k = last ^ c;
    l--;
    // Invalid queries in the problem
    l = max(0, l);
    r = min(n, r);
    if (l >= r) {
      last = 0;
    } else {
      last = query(l, r, k);
    }
    cout << last << '\n';
  }
}