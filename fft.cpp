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

using base = complex<double>;
const int MAXN = 1 << 18;
namespace fft {
    int rev[MAXN];
    base wlen_pw[MAXN];
    
    void fft (base a[], int n, bool invert) {
        for (int i = 0; i < n; ++i)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
    
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * M_PI / len * (invert ? -1 : 1);
            int len2 = len >> 1;
    
            base wlen(cos(ang), sin(ang));
            wlen_pw[0] = base(1, 0);
            for (int i = 1; i < len2; ++i)
                wlen_pw[i] = wlen_pw[i - 1] * wlen;
    
            for (int i = 0; i < n; i += len) {
                base t,
                    *pu = a + i,
                    *pv = a + i + len2, 
                    *pu_end = a + i + len2,
                    *pw = wlen_pw;
                for (; pu != pu_end; ++pu, ++pv, ++pw) {
                    t = *pv * *pw;
                    *pv = *pu - t;
                    *pu += t;
                }
            }
        }
    
        if (invert)
            for (int i = 0; i < n; ++i)
                a[i] /= n;
    }
    
    void calc_rev (int n, int log_n) {
        for (int i = 0; i < n; ++i) {
            rev[i] = 0;
            for (int j = 0; j < log_n; ++j)
                if (i & (1 << j))
                    rev[i] |= 1 << (log_n - 1 - j);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
