#include <bits/stdc++.h>
using namespace std;

// Debug item
#define dbg(x) cerr << x.len << ' ' << x.op << ' ' << x.cl << '\n';

struct item {
  int len, op, cl;
};

int sz;
vector<item> t;

void init(int n) {
  sz = 1;
  while (sz < n) {
    sz *= 2;
  }
  t.resize(2 * sz);
}

item single(char c) {
  return {0, c == '(', c == ')'};
}

item merge(item a, item b) {
  int mn = min(a.op, b.cl);
  return {
    a.len + b.len + 2 * mn,
    a.op - mn + b.op,
    b.cl - mn + a.cl
  };
}

void build(string &s, int x, int l, int r) {
  if (l + 1 == r) {
    if (l < (int)s.size()) {
      t[x] = single(s[l]);
    }
    return;
  }
  int mid = l + (r - l) / 2;
  build(s, 2 * x + 1, l, mid);
  build(s, 2 * x + 2, mid, r);
  t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
}

void build(string &s) {
  build(s, 0, 0, sz);
}

item query(int l, int r, int x, int lx, int rx) {
  if (lx >= r || rx <= l) {
    return {0, 0, 0};
  }
  if (lx >= l && rx <= r) {
    return t[x];
  }
  int mid = lx + (rx - lx) / 2;
  return merge(query(l, r, 2 * x + 1, lx, mid), query(l, r, 2 * x + 2, mid, rx));
}

int query(int l, int r) {
  return query(l, r, 0, 0, sz).len;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  int m;
  cin >> s >> m;
  init(s.size());
  build(s);
  while (m--) {
    int l, r;
    cin >> l >> r;
    l--;
    cout << query(l, r) << '\n';
  }
}