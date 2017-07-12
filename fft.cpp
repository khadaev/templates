#include <bits/stdc++.h>
using namespace std;

using base = complex<double>;
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

    vector<int> multiply(vector<int> a, vector<int> b) {
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
            _c[i] = _a[i] * _b[i];
        fft(_c, n, true);
        vector<int> ans(n);
        for (int i = 0; i < n; ++i)
            ans[i] = int(_c[i].real() + 0.5);
        return ans;
    }
}
using fft::multiply;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
