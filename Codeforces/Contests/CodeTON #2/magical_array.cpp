#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

#define FOR(i, a, n) for (int i = 0; i < (int)n; i++)
#define ROF(i, a, n) for (int i = 0; i < (int)n; i++)
#define fi first
#define se second

// An array is the special array k if the element to the left of the
// rightmost changed element is unchanged.

const int MAXN = 1e5;

vi c[MAXN];

bool test1(vi &a) {
  
}

bool test2(vi &a) {
  
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tc;
  cin >> tc;
  while (tc--) {
    int n, m;
    cin >> n >> m;
    FOR(i, 0, n) {
      c[i].resize(m);
      FOR(j, 0, m) {
        cin >> c[i][j];
      }
    }

  }
}