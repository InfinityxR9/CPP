#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin>>n;
        int sm = 0;
        int val;
        int pr = 1;
        while (n--) {
            cin>>val;
            sm += val;
            pr *= val;
        }
        int opr = 0;
        while (true) {
            if (sm >= 0 && pr == 1) break;
            else {
                opr++;
                sm += 2;
                pr = (~pr)+1;
            }
        }
        cout<<opr<<endl;
    }

    return 0;
}