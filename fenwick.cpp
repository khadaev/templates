#include <bits/stdc++.h>
using namespace std;

struct FenwickTree {
    vector<int> bit;
    int n;

    FenwickTree () {};
    FenwickTree (int _n) {
        n = _n;
        bit.resize(n);
    }

    int get(int r) {
        int ans = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ans += bit[r];
        return ans;
    }

    void add(int pos, int val) {
        for (; pos < n; pos |= (pos + 1))
            bit[pos] += val;
    }

    int kth(int k) { // k from zero
        int pw = 1 << 21, pos = 0;
        while (pw > 1) {
            pw >>= 1;
            int x = pos + pw - 1;
            if (x < n && bit[x] <= k) {
                k -= bit[x];
                pos += pw;
            }
        }
        return pos;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
