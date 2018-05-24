#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 998244353;
const ll g = 3;

ll Pow(ll a, ll b) {
    ll x = 1, y = a;
    while (b) {
        if (b % 2) (x *= y) %= MOD;
        (y *= y) %= MOD;
        b /= 2;
    }
    return x;
}

ll Inv(ll x) {
    return Pow(x, MOD - 2);
}

using base = ll;
const int MAXN = 1 << 18;
base _a[MAXN], _b[MAXN], _c[MAXN];
namespace fft {
    int rev[MAXN];
    base wlen_pw[MAXN];
    
    void fft (base a[], int n, bool invert) {
        for (int i = 0; i < n; ++i)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
    
        for (int len = 2; len <= n; len <<= 1) {
            int len2 = len >> 1;
            base wlen = Pow(g, (MOD - 1) / len);
            if (invert)
                wlen = Inv(wlen);
            wlen_pw[0] = 1;
            for (int i = 1; i < len2; ++i)
                wlen_pw[i] = wlen_pw[i - 1] * wlen % MOD;
    
            for (int i = 0; i < n; i += len) {
                base t,
                    *pu = a + i,
                    *pv = a + i + len2, 
                    *pu_end = a + i + len2,
                    *pw = wlen_pw;
                for (; pu != pu_end; ++pu, ++pv, ++pw) {
                    t = *pv * *pw % MOD;
                    *pv = *pu - t;
                    if (*pv < 0) *pv += MOD;
                    *pu += t;
                    if (*pu >= MOD) *pu -= MOD;
                }
            }
        }
        base inv_n = Inv(n);
        if (invert)
            for (int i = 0; i < n; ++i)
                (a[i] *= inv_n) %= MOD;
    }
    
    void calc_rev (int n) {
        int lg = 1;
        while ((1 << lg) < n) ++lg;
        for (int i = 0; i < n; ++i) {
            rev[i] = 0;
            for (int j = 0; j < lg; ++j)
                if (i & (1 << j))
                    rev[i] |= 1 << (lg - 1 - j);
        }
    }

    vector<ll> multiply(vector<ll> a, vector<ll> b) {
        int n = 1;
        while (n < max(a.size(), b.size()))
            n *= 2;
        n *= 2;
        calc_rev(n);
        for (int i = 0; i < n; ++i)
            _a[i] = 0, _b[i] = 0;
        for (int i = 0; i < (int)a.size(); ++i)
            _a[i] = a[i];
        for (int i = 0; i < (int)b.size(); ++i)
            _b[i] = b[i];
        fft(_a, n, false);
        fft(_b, n, false);
        for (int i = 0; i < n; ++i)
            _c[i] = _a[i] * _b[i] % MOD;
        fft(_c, n, true);
        vector<ll> ans(n);
        for (int i = 0; i < n; ++i)
            ans[i] = _c[i];
        return ans;
    }
}
using fft::multiply;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); 
    srand((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
}
