#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    int t;
    cin >> t;

    while (t--) {
        ll n,a,b;
        cin>>n>>a>>b;

        if (n == 1) cout<<min(a,b)<<endl;
        else if (n == 2) cout<<min(2*a, b)<<endl;
        else if (n == 3) cout<< min(3*a, b)<<endl;
        else {
            ll cost;
            if (3*a > b) {
                cost = (n / 3)*b + min((n % 3)*a, b);
            } else {
                cost = (n / 3)*3*a + min((n % 3)*a, b);
            }
            cout<<cost<<endl;
        }
    }

    return 0;
}