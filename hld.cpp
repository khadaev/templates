//SPOJ QTREE

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define forn(i, a, n) for (int i = (int)(a); i < (int)(n); ++i)
#define ford(i, a, n) for (int i = (int)(n) - 1; i >= (int)(a); --i)
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

template<typename T>
inline void setmax(T& a, T b) {
    if (a < b) a = b;
}

template<typename T>
inline void setmin(T& a, T b) {
    if (a > b) a = b;
}

template<typename T, typename S>
istream& operator>> (istream& in, pair<S, T>& p) {
    in >> p.fs >> p.sn;
    return in;
}
template<typename T, typename S>
ostream& operator<< (ostream& out, pair<S, T>& p) {
    out << p.fs << ' ' << p.sn << ' ';
    return out;
}

template<typename T>
istream& operator>> (istream& in, vector<T>& v) {
    for (T& x : v) in >> x;
    return in;
}
template<typename T>
ostream& operator<< (ostream& out, vector<T>& v) {
    for (T& x : v) out << x << ' ';
    return out;
}

const ld eps = 1e-9;
const int INF = 2000000000;
const ll LINF = 1ll * INF * INF;
const ll MOD = 1000000007;

const int N = 1 << 14;

using T = ll;
inline T combine(T a, T b) {
    return max(a, b);
}
T DEFAULT = LLONG_MIN;
#define COMMUTE

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


vector<pair<int, T>> e[N];
int in[N], out[N], sz[N], top[N], par[N], address[N], timer = -1;
SegmentTreeBottomUp Tree; 

void dfs_sz(int u, int p) {
    par[u] = p;
    sz[u] = 1;
    for (auto& _ : e[u]) {
        int v = _.fs;
        if (v == p) continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
        if (e[u][0].fs == p || sz[v] >= sz[e[u][0].fs])
            swap(_, e[u][0]);
    }
}

void dfs(int u, int p, T value) {
    in[u] = ++timer;
    Tree.set(in[u], value);
    for (auto& _ : e[u]) {
        int v = _.fs;
        T val = _.sn;
        if (v == p) continue;
        if (_ == e[u][0])
            top[v] = top[u];
        else
            top[v] = v;
        dfs(v, u, val);
    }
    out[u] = timer;
}

bool ancestor(int u, int v) { // is u the ancestor of v?
    return in[u] <= in[v] && out[v] <= out[u];
}

void solve() {
    int n;
    cin >> n;
    forn(i, 0, n) e[i].clear();
    vector<pair<int, int>> eds;
    forn(i, 1, n) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        --u, --v;
        e[u].eb(v, c);
        e[v].eb(u, c);
        eds.eb(u, v);
    }
    timer = -1;
    dfs_sz(0, -1);
    dfs(0, -1, DEFAULT);
    int ix = 0;
    for (auto _ : eds) {
        int u = _.fs, v = _.sn;
        if (ancestor(u, v))
            address[ix] = v;
        else
            address[ix] = u;
        ++ix;
    }
    while (1) {
        char tp[10];
        scanf("%s", tp);
        if (string(tp) == "DONE") return;
        if (string(tp) == "CHANGE") {
            int pos, val;
            scanf("%d %d", &pos, &val);
            Tree.set(in[address[--pos]], val);
        }
        if (string(tp) == "QUERY") {
            int u, v;
            scanf("%d %d", &u, &v);
            --u, --v;
            T ans = DEFAULT;
            while (!ancestor(top[u], v)) {
                ans = combine(ans, Tree.get(in[top[u]], in[u] + 1));
                u = par[top[u]];
            }
            while (!ancestor(top[v], u)) {
                ans = combine(ans, Tree.get(in[top[v]], in[v] + 1));
                v = par[top[v]];
            }
            assert(top[u] == top[v]);
            if (!ancestor(u, v)) {
                swap(u, v);
                assert(ancestor(u, v));
            }
            ans = combine(ans, Tree.get(in[u] + 1, in[v] + 1));
            printf("%lld\n", ans);
        }
    }
}

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0); 
    srand((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
    int t;
    scanf("%d", &t);
    while (t--) solve();
}
