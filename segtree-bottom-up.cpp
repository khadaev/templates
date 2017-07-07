#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 20;
using T = int;
inline T combine(T a, T b) {
    return a + b;
}
T DEFAULT = 0;

T a[2 * N];
struct SegmentTreeBottomUp {

    SegmentTreeBottomUp () {
        for (int i = 0; i < 2 * N; ++i)
            a[i] = DEFAULT;
    };

    SegmentTreeBottomUp (vector<T> _a) {
        for (int i = 0; i < (int)_a.size(); ++i)
            a[i + N] = _a[i];
        for (int i = 0; i < N; ++i)
            a[i + N] = DEFAULT;
        for (int i = N - 1; i >= 0; --i)
            a[i] = combine(a[2 * i], a[2 * i + 1]);
    }

#ifdef COMMUTE
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
#else
    T get(int l, int r) {
        T res_l = DEFAULT, res_r = DEFAULT;
        l += N, r += N;
        while (l < r) {
            if (l % 2)
                res_l = combine(res_l, a[l++]);
            if (r % 2)
                res_r = combine(a[--r], res_r);
            l /= 2;
            r /= 2;
        }
        return combine(res_l, res_r);
    }
#endif // COMMUTE

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
