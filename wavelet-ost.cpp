#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_map = tree<int,int,less<int>,rb_tree_tag,tree_order_statistics_node_update>;

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

struct Vertex {
    int l, r;
    ordered_map m;

    Vertex () : l(-1), r(-1) {};
};

const int N = 1e5 + 10;

Vertex v[2 * N];
struct WaveletTree {
    vector<int> a;
    vector<char> active;
    int n, ix;

    WaveletTree () {};

    WaveletTree (vector<int> _a) {
        a = _a;
        n = (int)a.size();
        active = vector<char> (n, 1);
        ix = 0;
        for (int i = 0; i < n; ++i)
            v[0].m[i] = a[i];
        build(0, 0, n);
    }

    void build(int i, int lb, int rb) {
        if (lb + 1 == rb) return;
        int mid = (lb + rb) / 2;
        v[i].l = ++ix;
        v[i].r = ++ix;
        for (auto p : v[i].m)
            v[p.second < mid ? v[i].l : v[i].r].m[p.first] = p.second;
        build(v[i].l, lb, mid);
        build(v[i].r, mid, rb);
    }

    int _count(int i, int l, int r, int lb, int rb, int k) {
        if (lb + 1 == rb)
            return int(v[i].m.order_of_key(r) - v[i].m.order_of_key(l));
        int mid = (lb + rb) / 2;
        if (k < mid)
            return _count(v[i].l, l, r, lb, mid, k);
        else
            return _count(v[i].r, l, r, mid, rb, k);
    }

    int count(int l, int r, int k) {
        return _count(0, l, r, 0, n, k);
    }

    void _erase(int i, int lb, int rb, int pos, int k) {
        v[i].m.erase(pos);
        if (lb + 1 == rb) return;
        int mid = (lb + rb) / 2;
        if (k < mid)
            _erase(v[i].l, lb, mid, pos, k);
        else
            _erase(v[i].r, mid, rb, pos, k);
    }

    void erase(int pos, int k) {
        _erase(0, 0, n, pos, k);
    }

    void _insert(int i, int lb, int rb, int pos, int k) {
        v[i].m[pos] = k;
        if (lb + 1 == rb) return;
        int mid = (lb + rb) / 2;
        if (k < mid)
            _insert(v[i].l, lb, mid, pos, k);
        else
            _insert(v[i].r, mid, rb, pos, k);
    }

    void insert(int pos, int k) {
        _insert(0, 0, n, pos, k);
    }

    void toggle(int pos) {
        if (active[pos]) {
            active[pos] = 0;
            erase(pos, a[pos]);
        } else {
            active[pos] = 1;
            insert(pos, a[pos]);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
