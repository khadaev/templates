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

namespace SuffixArray {
    const int maxlen = 1e5 + 10;
    const int alphabet = 256;
    int p[maxlen], cnt[maxlen], c[maxlen], pn[maxlen], cn[maxlen];
    int* build(string s) {
        s += "$";
        int n = (int)s.size();
        memset(cnt, 0, alphabet * sizeof(int));
        for (int i = 0; i < n; ++i)
            ++cnt[(int)s[i]];
        for (int i = 1; i < alphabet; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; ++i)
            p[--cnt[(int)s[i]]] = i;
        int classes = 0;
        c[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (s[p[i]] != s[p[i - 1]])
                ++classes;
            c[p[i]] = classes;
        }
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; ++i) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            memset(cnt, 0, (classes + 1) * sizeof(int));
            for (int i = 0; i < n; ++i)
                ++cnt[c[pn[i]]];
            for (int i = 1; i <= classes; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i)
                p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 0;
            for (int i = 1; i < n; ++i) {
                int m1 = p[i] + (1 << h), m2 = p[i - 1] + (1 << h);
                if (m1 >= n) m1 -= n;
                if (m2 >= n) m2 -= n;
                if (c[p[i]] != c[p[i - 1]] || c[m1] != c[m2])
                    ++classes;
                cn[p[i]] = classes;
            }
            memcpy(c, cn, n * sizeof(int));
        }
        return p;
    }
}
using SuffixArray::build;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
