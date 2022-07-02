#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<int, ll> orig;
map<ll, int> ind;

struct segtree {
  int sz;
  vector<ll> t;

  void init(int n) {
    sz = 1;
    while (sz < n) {
      sz *= 2;
    }
    t.resize(2 * sz);
  }

  // Just set using compressed indices
  void set(int i, int v, int x, int l, int r) {
    if (l + 1 == r) {
      t[x] = v;
      return;
    }
    int mid = l + (r - l) / 2;
    if (orig[i] < orig[mid]) {
      set(i, v, 2 * x + 1, l, mid);
    } else {
      set(i, v, 2 * x + 2, mid, r);
    }
    t[x] = t[2 * x + 1] + t[2 * x + 2];
  }

  void set(int i, int v) {
    set(i, v, 0, 0, sz);
  }

  // Here, l and r are positions
  // lx and rx are indices in t
  ll query(ll l, ll r, int x, int lx, int rx) {
    if (orig[lx] >= r || l >= orig[rx]) {
      return 0;
    }
    if (orig[lx] >= l && orig[rx] <= r) {
      return t[x];
    }
    int mid = lx + (rx - lx) / 2;
    return query(l, r, 2 * x + 1, lx, mid) + query(l, r, 2 * x + 2, mid, rx);
  }

  ll query(ll l, ll r) {
    return query(l, r, 0, 0, sz);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, t;
  cin >> n >> t;
  vector<ll> pref(n);
  for (int i = 0; i < n; i++) {
    cin >> pref[i];
  }
  for (int i = 1; i < n; i++) {
    pref[i] += pref[i - 1];
  }

  vector<ll> unq = pref;
  sort(unq.begin(), unq.end());
  unq.erase(unique(unq.begin(), unq.end()), unq.end());
  int m = unq.size();
  for (int i = 0; i < m; i++) {
    orig[i] = unq[i];
    ind[unq[i]] = i;
  }

  int ans = 0;
  segtree st;
  st.init(m);
  for (int r = 0; r < n; r++) {
    // pref[r] - pref[l] < t
    // pref[r] + t < pref[l]
    // +1 to ans for each element in the range [pref[r] + t + 1 ... INF)
    ans += st.query(pref[r] + t + 1, 2e18);
    st.set(ind[pref[r]], ind[pref[r]] + 1);
  }
  cout << ans;
}