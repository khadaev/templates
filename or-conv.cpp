#include <bits/stdc++.h>

using namespace std;

template<typename T>
vector<T> or_conv(vector<T> a, int n, bool inv) {
    assert((int)a.size() == (1 << n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < (1 << n); ++j)
            if (j & (1 << i))
                a[j] += (inv ? -1 : 1) * a[j ^ (1 << i)];
    return a;
}

int main() {

}
