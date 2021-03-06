#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

struct Vertex {
    int val, toPush, lc, rc;

    Vertex() {
        val = 0;
        toPush = -1;
    };
};

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
    }

    void push(int i, int sz) {
        if (a[i].toPush != -1) {
            if (a[i].lc != -1) {
                a[a[i].lc].toPush = a[i].toPush;
                a[a[i].rc].toPush = a[i].toPush;
            }
            a[i].val = a[i].toPush * sz;
            a[i].toPush = -1;
        }
    }

    void relax(int i, int lb, int rb) {
        if (a[i].lc == -1) return;
        int mid = (lb + rb) / 2;
        push(a[i].lc, mid - lb);
        push(a[i].rc, rb - mid);
        a[i].val = a[a[i].lc].val + a[a[i].rc].val;
    }

    int _get(int i, int l, int r, int lb, int rb) {
        push(i, rb - lb);
        l = max(l, lb);
        r = min(r, rb);
        if (l >= r) return 0;
        if (l == lb && r == rb)
            return a[i].val;
        int mid = (lb + rb) / 2;
        int rez =  _get(a[i].lc, l, r, lb, mid)
            + _get(a[i].rc, l, r, mid, rb);
        relax(i, lb, rb);
        return rez;
    }

    int get(int l, int r) {
        return _get(0, l, r, 0, n);
    }

    void _set(int i, int l, int r, int lb, int rb, int v) {
        push(i, rb - lb);
        l = max(l, lb);
        r = min(r, rb);
        if (l >= r) return;
        if (l == lb && r == rb) {
            a[i].toPush = v;
            return;
        }
        int mid = (lb + rb) / 2;
        _set(a[i].lc, l, r, lb, mid, v);
        _set(a[i].rc, l, r, mid, rb, v);
        relax(i, lb, rb);
    }

    void set(int l, int r, int v) {
        _set(0, l, r, 0, n, v);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
