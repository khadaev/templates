#include <bits/stdc++.h>

using ld = long double;

struct Vector {
    ld x, y;

    Vector () {}
    Vector (ld _x, ld _y) : x(_x), y(_y) {}

    Vector operator+ (Vector rhs) {
        return Vector(x + rhs.x, y + rhs.y);
    }

    Vector operator- (Vector rhs) {
        return Vector(x - rhs.x, y - rhs.y);
    }

    void operator+= (Vector rhs) {
        x += rhs.x, y += rhs.y;
    }

    void operator-= (Vector rhs) {
        x -= rhs.x, y -= rhs.y;
    }

    Vector operator* (ld c) {
        return Vector(x * c, y * c);
    }

    Vector operator/ (ld c) {
        return Vector(x / c, y / c);
    }

    void operator*= (ld c) {
        x *= c, y *= c;
    }

    void operator/= (ld c) {
        x /= c, y /= c;
    }

    Vector rotate (ld phi) {
        return Vector(x * cosl(phi) - y * sinl(phi), x * sinl(phi) + y * cosl(phi));
    }

    ld norm() {
        return sqrtl(x * x + y * y);
    }

    ld operator* (Vector rhs) {
        return x * rhs.x + y * rhs.y;
    }

    ld operator^ (Vector rhs) {
        return x * rhs.y - y * rhs.x;
    }
};

int main() {
}
