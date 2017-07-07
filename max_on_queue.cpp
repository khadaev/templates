#include <bits/stdc++.h>
using namespace std;

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
        a.emplace_back(x, combine(val, x));
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
