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
        n--;
        while (n--)
        {
            cin>>val;
            sm += val;
        }
        cout<<((~sm)+1)<<endl;
    }

    return 0;
}