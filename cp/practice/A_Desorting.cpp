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
        int prev = 0;
        int ans = INT_MAX;
        int val;
        bool flag = true;
        while (n--){
            cin>>val;
            if (!flag)
                ans = min(ans, val-prev);
            else flag = false;
            prev = val;
        }
        if (ans == 0) cout<<1<<endl;
        else if (ans < 0) cout<<0<<endl;
        else cout<<ans/2+1<<endl;
    }

    return 0;
}