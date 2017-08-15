#include <bits/stdc++.h>
using namespace std;

using T = int;
const int DEFAULT = 0;
const int OFF = 0;

inline int combine(int a, int b) {return a + b;}

struct Vertex {
    T val;
    int lc, rc;

    Vertex() {
        val = OFF;
    };
};

const int N = 1e5 + 10;
const int LOG = 17;
const int SZ = N * LOG * 4;
Vertex a[SZ];

struct SegmentTreeTopDown {
    Vertex* a;
    int ix, n;

    SegmentTreeTopDown () {};

    SegmentTreeTopDown (int _n, Vertex* _a) {
        a = _a;
        ix = 0;
        n = _n;
        build(0, 0, n);
    }

    void relax(int i) {
        if (a[i].lc == -1) return;
        a[i].val = combine(a[a[i].lc].val, a[a[i].rc].val);
    }

    void build(int i, int lb, int rb) {
        if (lb + 1 == rb) {
            a[i].lc = a[i].rc = -1;
            return;
        }
        int mid = (lb + rb) / 2;
        a[i].lc = ++ix;
        build(ix, lb, mid);
        a[i].rc = ++ix;
        build(ix, mid, rb);
        relax(i);
    }

    T _get(int i, int l, int r, int lb, int rb) {
        l = max(l, lb);
        r = min(r, rb);
        if (l >= r) return DEFAULT;
        if (l == lb && r == rb)
            return a[i].val;
        int mid = (lb + rb) / 2;
        return  combine(_get(a[i].lc, l, r, lb, mid),
            _get(a[i].rc, l, r, mid, rb));
    }

    T get(int i, int l, int r) {
        return _get(i, l, r, 0, n);
    }

    void _set(int i, int pos, int lb, int rb, T value) {
        if (lb + 1 == rb) {
            if (lb == pos) a[i].val = value;
            else assert(false);
            return;
        }
        int mid = (lb + rb) / 2;
        if (pos < mid) {
            int u = ++ix;
            a[u] = a[a[i].lc];
            a[i].lc = u;
            _set(u, pos, lb, mid, value);
        } else {
            int u = ++ix;
            a[u] = a[a[i].rc];
            a[i].rc = u;
            _set(u, pos, mid, rb, value);
        }
        relax(i);
    }

    int set(int i, int pos, T v) {
        int u = ++ix;
        a[u] = a[i];
        _set(u, pos, 0, n, v);
        return u;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
