#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

vector<bool> isprime;
vector<int> primes, mnfactor;

void sieve(int n) {
    isprime.resize(n + 1);;
    fill(all(isprime), 1);
    isprime[0] = isprime[1] = false;
    mnfactor.resize(n + 1);
    // Runs in O(n * log(log(n))).
    for (int i = 2; i <= n; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            mnfactor[i] = i;
            for (int j = i * i; j <= n; j += i) {
                isprime[j] = false;
                mnfactor[j] = i;
            }
        }
    }
}

bool ckprime(int n) {
    // O(1) if we've run sieve up to n.
    if (n <= sz(isprime) - 1) {
        return isprime[n];
    }
    // O(sqrt(n) / log(n)) otherwise. Sieve must be run until at least sqrt(n).
    for (int p : primes) {
        if (p * p > n) {
            break;
        }
        if (n % p == 0) {
            return false;
        }
    }
    return true;
}

vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> res;
    // O(log(n)) if we've run sieve up to n.
    if (n <= sz(isprime) - 1) {
        while (n != 1) {
            int f = mnfactor[n];
            int exp = 0;
            while (n % f == 0) {
                n /= f;
                exp++;
            }
            res.push_back({f, exp});
        }
    }
    // O(sqrt(n) / log(n)) otherwise. Sieve must be run until at least sqrt(n).
    for (int p : primes) {
        if (p * p > n) {
            break;
        }
        if (n % p == 0) {
            int exp = 0;
            while (n % p == 0) {
                n /= p;
                exp++;
            }
            res.push_back({p, exp});
        }
    }
    if (n > 1) {
        res.push_back({n, 1});
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}