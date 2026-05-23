#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin>>n;
        for (int i = 1; i <= 2*n; i += 2)
        {
            cout<<i<<" ";
        }
        cout<<endl;
    }
    
    return 0;
}