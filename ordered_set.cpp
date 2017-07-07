#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ordered_set S;
    S.insert(1);
    S.insert(3);
    cout << S.order_of_key(2) << '\n';
    cout << *S.find_by_order(1) << '\n';
}
