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

void inc(int i, int x, int l, int r) {
  if (l + 1 == r) {
    t[x] = t[x] + 1;
    return;
  }
  int mid = l + (r - l) / 2;
  if (i < mid) {
    inc(i, 2 * x + 1, l, mid);
  } else {
    inc(i, 2 * x + 2, mid, r);
  }
  t[x] = t[2 * x + 1] + t[2 * x + 2];
}

void inc(int i) {
  inc(i, 0, 0, sz);
}

int query(int l, int r, int x, int lx, int rx) {
  if (lx >= r || rx <= l) {
    return 0;
  }
  if (lx >= l && rx <= r) {
    return t[x];
  }
  
  int mid = lx + (rx - lx) / 2;
  return query(l, r, 2 * x + 1, lx, mid) + query(l, r, 2 * x + 2, mid, rx);
}

int query(int l, int r) {
  return query(l, r, 0, 0, sz);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  long long n, k;
  cin >> n >> k;
  vector<long long> pref(n);
  for (int i = 0; i < n; i++) {
    cin >> pref[i];
    if (i > 0) {
      pref[i] += pref[i - 1];
    }
  }
  vector<long long> a = pref;
  a.push_back(0);
  sort(all(a));
  a.resize(unique(all(a)) - a.begin());
  init(sz(a));
  inc(lower_bound(all(a), 0) - a.begin());
  long long ans = 0;
  for (int r = 0; r < n; r++) {
    // pref[r] - pref[l] < t
    // pref[r] - t < pref[l]
    // pref[l] > pref[r] - t
    // All elements (pref[r] - k ... INF] work
    ans += query(upper_bound(all(a), pref[r] - k) - a.begin(), sz(a));
    inc(lower_bound(all(a), pref[r]) - a.begin());
  }
  cout << ans << '\n';
}