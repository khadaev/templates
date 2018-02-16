#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll LINF = 4e18;

const int FROM = -(1 << 17), TO = 1 << 17;
const int SZ = 2 * (TO - FROM) + 100;
int vis[SZ];

struct line {
    ll k, b;
    line(ll _k = 0, ll _b = -LINF) {
        k = _k; b = _b;
    }
    ll get(ll x) {
        return k * x + b;
    }
} c[SZ];

//for rollbacks only
vector<int> used;
vector<pair<int, line>> changed;

void modify(int x, int l, int r, line v) {
    if (!vis[x]) {
        vis[x] = 1;
        c[x] = v;
        used.push_back(x);
        return;
    }
    if (c[x].get(l) > v.get(l) && c[x].get(r) > v.get(r))
        return;
    if (c[x].get(l) < v.get(l) && c[x].get(r) < v.get(r)) {
        changed.emplace_back(x, c[x]);
        c[x] = v;
        return;
    }
    if (l == r) return;
    int m = (l + r - 2 * FROM) / 2 + FROM;
    if (c[x].get(l) < v.get(l)) {
        changed.emplace_back(x, c[x]);
        swap(c[x], v);
    }
    if (c[x].get(m) > v.get(m))
        modify(2 * x + 1, m + 1, r, v);
    else {
        changed.emplace_back(x, c[x]);
        swap(c[x], v);
        modify(2 * x, l, m, v);
    }
}

ll get(int x, int l, int r, int pos) {
    if (l == r) return c[x].get(l);
    int m = (l + r - 2 * FROM) / 2 + FROM; ll ans = c[x].get(pos);
    if (pos <= m) ans = max(ans, get(2 * x, l, m, pos));
    else ans = max(ans, get(2 * x + 1, m + 1, r, pos));
    return ans;
}

int main() {    
}
