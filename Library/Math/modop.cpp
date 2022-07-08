#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

const int mod = 998244353;

int madd(int a, int b) {
  return (a + b) % mod;
}

int msub(int a, int b) {
  return (((a - b) % mod) + mod) % mod;
}

int mmul(int a, int b) {
  return ((a % mod) * (b % mod)) % mod;
}

int mpow(int base, int exp) {
  // O(log(exp))
  int res = 1;
  while (exp) {
    if (exp % 2 == 1) {
      res = (res * base) % mod;
    }
    exp >>= 1;
    base = (base * base) % mod;
  }
  return res;
}

int minv(int base) {
  return mpow(base, mod - 2);
}

int mdiv(int a, int b) {
  return mmul(a, minv(b));
}

vector<int> fact, ifact;

void genfact(int n) {
  fact.resize(n + 1);
  ifact.resize(n + 1);
  fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
  for (int i = 2; i <= n; i++) {
    fact[i] = (i * fact[i - 1]) % mod;
  }
  ifact[n] = minv(fact[n]);
  for (int i = n - 1; i >= 2; i--) {
    ifact[i] = ((i + 1) * ifact[i + 1]) % mod;
  }
}

int nck(int n, int k) {
  if (k < 0 || n < k) {
    return 0;
  }
  int den = (ifact[k] * ifact[n - k]) % mod;
  return (den * fact[n]) % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
}