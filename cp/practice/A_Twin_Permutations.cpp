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
        int val;
        for (int i=0;i<n;i++)
        {
            cin>>val;
            cout<<(n+1-val)<<" ";
        }
        cout<<endl;
    }

    return 0;
}