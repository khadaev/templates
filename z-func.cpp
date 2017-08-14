#include <bits/stdc++.h>

using namespace std;

vector<int> z(string s) {
    int n = s.size();
    vector<int> a(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r)
            a[i] = min(r - i + 1, a[i - l]);
        while (i + a[i] < n && s[a[i]] == s[i + a[i]])
            ++a[i];
        if (i + a[i] - 1 > r) {
            l = i;
            r = i + a[i] - 1;
        }
    }
    return a;
}

int main() {
    string s;
    cin >> s;
    for (int x : z(s)) cout << x << ' ';
}
