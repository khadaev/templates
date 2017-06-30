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

const int N = 1 << 20;
using T = int;
inline T combine(T a, T b) {
    return a + b;
}
T DEFAULT = 0;

T a[2 * N];
struct SegmentTreeBottomUp {

    SegmentTreeBottomUp () {
        forn(i, 0, 2 * N)
            a[i] = DEFAULT;
    };

    SegmentTreeBottomUp (vector<T> _a) {
        forn(i, 0, (int)_a.size())
            a[i + N] = _a[i];
        forn(i, (int)_a.size(), N)
            a[i + N] = DEFAULT;
        ford(i, 1, N)
            a[i] = combine(a[2 * i], a[2 * i + 1]);
    }

    T get(int l, int r) {
        T res = DEFAULT;
        l += N, r += N;
        while (l < r) {
            if (l % 2)
                res = combine(a[l++], res);
            if (r % 2)
                res = combine(res, a[--r]);
            l /= 2;
            r /= 2;
        }
        return res;
    }

    void set(int pos, T val) {
        pos += N;
        a[pos] = val;
        pos /= 2;
        while (pos) {
            a[pos] = combine(a[2 * pos], a[2 * pos + 1]);
            pos /= 2;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
