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

const int N = 1e5 + 10;
const int SQRT = sqrt(N);

struct Query {
    int l, r, bl, ix;

    Query () {};
    Query (int _l, int _r, int _ix) : l(_l), r(_r), bl(_l / SQRT), ix(_ix) {};

    bool operator< (const Query& x) const {
        return bl == x.bl ? (r < x.r) ^ (bl & 1) : bl < x.bl;
    }
};

int a[N], ans[N], cnt[N], cntOfCnt[N], cur = 0;

void add(int x) {
    int val = a[x];
    --cntOfCnt[cnt[val]];
    ++cnt[val];
    ++cntOfCnt[cnt[val]];
    if (cnt[val] > cur)
        ++cur;
}

void rem(int x) {
    int val = a[x];
    --cntOfCnt[cnt[val]];
    if (cnt[val] == cur && cntOfCnt[cur] == 0)
        --cur;
    --cnt[val];
    ++cntOfCnt[cnt[val]];
}

void getAns(int i) {
    ans[i] = cur;
}

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    int n, q;
    scanf("%d %d", &n, &q);
    forn(i, 0, n) scanf("%d", &a[i]);
    vector<Query> qs(q);
    forn(i, 0, q) {
        int l, r;
        scanf("%d %d", &l, &r);
        qs[i] = Query(l, ++r, i);
    }
    sort(all(qs));
    int l = 0, r = 0;
    cntOfCnt[0] = N;
    for (auto p : qs) {
        while (l > p.l) add(--l);
        while (r < p.r) add(r++);
        while (l < p.l) rem(l++);
        while (r > p.r) rem(--r);
        getAns(p.ix);
    }
    forn(i, 0, q) printf("%d\n", ans[i]);
}
