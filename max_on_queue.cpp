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

using T = int;

inline T combine(T a, T b) {
    return a & b;
}
T DEFAULT = INT_MAX;

struct Stack {
    vector<pair<T, T>> a;
    T val;

    Stack () : val(DEFAULT) {};

    void relax() {
        val = a.empty() ? DEFAULT : a.back().second;
    }

    void push(T x) {
        a.eb(x, combine(val, x));
        relax();
    }

    void pop() {
        assert(!a.empty());
        a.pop_back();
        relax();
    }

    T top() {
        assert(!a.empty());
        return a.back().first;
    }

    bool empty() {
        return a.empty();
    }
};

struct Queue {
    Stack l, r;

    Queue () {};

    void push(T x) {
        l.push(x);
    }

    void go() {
        while (!l.empty()) {
            r.push(l.top());
            l.pop();
        }
    }

    void pop() {
        if (r.empty()) go();
        assert(!r.empty());
        r.pop();
    }

    T front() {
        if (r.empty()) go();
        assert(!r.empty());
        return r.top();
    }

    bool empty() {
        return l.empty() && r.empty();
    }

    T get() {
        return combine(l.val, r.val);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
