#include <bits/stdc++.h>
using namespace std;

struct Vertex {
    int l, r;
    vector<int> vals, goL;

    Vertex () : l(-1), r(-1) {};
};

const int N = 1e5 + 10;
Vertex v[2 * N];

struct WaveletTree {
    vector<int> a;
    int n, ix;

    WaveletTree () {};
    WaveletTree (vector<int> _a) {
        a = _a;
        n = (int)a.size();
        ix = 0;
        v[0].vals = a;
        build(0, 0, n);
    }

    void build(int i, int lb, int rb) {
        assert(i < 2 * N);
        if (lb + 1 == rb) return;
        int mid = (lb + rb) / 2;
        int ls = v[i].l = ++ix;
        int rs = v[i].r = ++ix;
        int sz = (int)v[i].vals.size();
        v[i].goL.resize(sz + 1);
        v[i].goL[0] = 0;
        for (int j = 0; j < sz; ++j) {
            v[v[i].vals[j] < mid ? ls : rs].vals.push_back(v[i].vals[j]);
            v[i].goL[j + 1] = (int)v[ls].vals.size();
        }
        build(ls, lb, mid);
        build(rs, mid, rb);
    }

    int _kth(int i, int r, int k) {
        if (v[i].l == -1) return v[i].vals[0];
        if (v[i].goL[r] > k)
            return _kth(v[i].l, v[i].goL[r], k);
        else
            return _kth(v[i].r, r - v[i].goL[r], k - v[i].goL[r]);
    }

    int kth(int r, int k) { // kth number in [0, r)
        return _kth(0, r, k);
    }

    int _kth(int i, int l, int r, int k) {
        if (v[i].l == -1) return v[i].vals[0];
        if (v[i].goL[r] - v[i].goL[l] > k)
            return _kth(v[i].l, v[i].goL[l], v[i].goL[r], k);
        else
            return _kth(v[i].r, l - v[i].goL[l], r - v[i].goL[r], k - v[i].goL[r] + v[i].goL[l]);
    }

    int kth(int l, int r, int k) { // kth number from [l, r)
        return _kth(0, l, r, k);
    }

    int _less_than(int i, int x, int r, int lb, int rb) {
        if (v[i].l == -1) {
            if (v[i].vals.empty() || v[i].vals[0] >= x) return 0;
            else return r;
        }
        int mid = (lb + rb) / 2;
        if (x <= mid)
            return _less_than(v[i].l, x, v[i].goL[r], lb, mid);
        else
            return v[i].goL[r] +
                _less_than(v[i].r, x, r - v[i].goL[r], mid, rb);
    }

    int less_than(int x, int r) { // number of values less than x in [0, r)
        return _less_than(0, x, r, 0, n);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
