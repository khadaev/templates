#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define forn(i, a, n) for (int i = (int)(a); i < (int)(n); ++i)
#define ford(i, a, n) for (int i = (int)(n - 1); i >= (int)(a); --i)
#define fore(i, a, n) for (int i = (int)(a); i <= (int)(n); ++i)
#define all(a) (a).begin(), (a).end()
#define fs first
#define sn second
#define trace(a)\
    for (auto i : a) cerr << i << ' ';\
    cerr << '\n'
#define eb emplace_back

#ifndef M_PI
const ld M_PI = acos(-1.0);
#endif

const ld eps = 1e-9;
const int INF = 2000000000;
const ll LINF = 1ll * INF * INF;
const ll MOD = 1000000007;

struct FenwickTree {
    vector<int> bit;
    int n;

    FenwickTree () {};
    FenwickTree (int _n) {
        n = _n;
        bit.resize(n);
    }

    int get(int r) {
        int ans = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ans += bit[r];
        return ans;
    }

    void add(int pos, int val) {
        for (; pos < n; pos |= (pos + 1))
            bit[pos] += val;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
