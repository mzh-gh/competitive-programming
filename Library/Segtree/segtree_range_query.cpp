#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

int sz;
vector<long long> t;

void init(int n) {
  sz = 1;
  while (sz < n) {
    sz *= 2;
  }
  t.resize(2 * sz);
}

void upd(int i, int v, int x, int l, int r) {
  if (l + 1 == r) {
    t[x] = v;
    return;
  }
  int mid = l + (r - l) / 2;
  if (i < mid) {
    upd(i, v, 2 * x + 1, l, mid);
  } else {
    upd(i, v, 2 * x + 2, mid, r);
  }
  t[x] = t[2 * x + 1] + t[2 * x + 2];
}

void upd(int i, int v) {
  upd(i, v, 0, 0, sz);
}

void build(vector<int> &a, int x, int l, int r) {
  if (l + 1 == r) {
    if (l < sz(a)) {
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

long long query(int L, int R, int x, int l, int r) {
  if (l >= R || r <= L) {
    return 0;
  }
  if (l >= L && r <= R) {
    return t[x];
  }
  int mid = l + (r - l) / 2;
  return query(L, R, 2 * x + 1, l, mid) + query(L, R, 2 * x + 2, mid, r);
}

long long query(int l, int r) {
  return query(l, r, 0, 0, sz);
}

int main() {}