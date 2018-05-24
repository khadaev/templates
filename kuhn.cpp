#include <bits/stdc++.h>
using namespace std;

namespace Kuhn {
    int n, k;
    vector<vector<int>> g;
    vector<int> mt;
    vector<char> used;


    bool try_kuhn (int v) {
        if (used[v])
            return false;
        used[v] = true;
        for (int i = 0; i < (int)g[v].size(); ++i) {
            int to = g[v][i];
            if (mt[to] == -1 || try_kuhn(mt[to])) {
                mt[to] = v;
                return true;
            }
        }
        return false;
    }

    void init(int _n, int _k) {
        n = _n, k = _k;
        g.resize(n);
        mt.assign(k, -1);
    }

    void add_edge(int i, int j) {
        g[i].push_back(j);
    }

    int run_kuhn() {
        int ans = 0;
        for (int v = 0; v < n; ++v) {
            used.assign(n, false);
            if (try_kuhn(v)) ++ans;
        }
        return ans;
    }

    void clear() {
        g.clear();
        mt.clear();
        used.clear();
    }
}
using Kuhn::add_edge;
using Kuhn::run_kuhn;
using Kuhn::init;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
