#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(a) (a).begin(), (a).end()

struct FenwickTree {
    vector<ll> bit;
    int n;

    FenwickTree () {};
    FenwickTree (int _n) {
        n = _n;
        bit.resize(n);
    }

    ll get(int r) {
        ll ans = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ans += bit[r];
        return ans;
    }

    void add(int pos, int val) {
        for (; pos < n; pos |= (pos + 1))
            bit[pos] += val;
    }
};

const int N = 1 << 17;
FenwickTree T[2 * N];
vector<int> ys[2 * N];

void fakeAdd(int x, int y) {
    x += N;
    while (x) {
        ys[x].push_back(y);
        x /= 2;
    }
}

void prepare() {
    for (int i = 1; i < 2 * N; ++i) {
        sort(all(ys[i]));
        ys[i].resize(unique(all(ys[i])) - ys[i].begin());
        T[i] = FenwickTree(ys[i].size());
    }
}

ll _get(int x, int yl, int yr) {
    int posl = lower_bound(all(ys[x]), yl) - ys[x].begin();
    int posr = lower_bound(all(ys[x]), yr) - ys[x].begin();
    return T[x].get(posr - 1) - T[x].get(posl - 1);
}

ll get(int xl, int xr, int yl, int yr) {
    ll ans = 0;
    xl += N, xr += N;
    while (xl < xr) {
        if (xl % 2)
            ans += _get(xl++, yl, yr);
        if (xr % 2)
            ans += _get(--xr, yl, yr);
        xl /= 2;
        xr /= 2;
    }
    return ans;
}

void _add(int x, int y, int val) {
    int pos = lower_bound(all(ys[x]), y) - ys[x].begin();
    assert(ys[x][pos] == y);
    T[x].add(pos, val);
}

void add(int x, int y, int val) {
    x += N;
    while (x) {
        _add(x, y, val);
        x /= 2;
    }
}

int main() {
    // run fakeAdd(x, y) for all 'add' queries
    // run prepare()
    // use 'add' and 'get' queries
}
