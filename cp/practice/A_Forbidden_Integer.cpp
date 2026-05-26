#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;

    while (t--) {
        int n,k,x;
        cin>>n>>k>>x;
        if (x != 1) {
            cout<<"YES"<<endl;
            cout<<n<<endl;
            while (n--) cout<<1<<" ";
            cout<<endl;
        } else {
            if (k == 1) cout<<"NO"<<endl;
            else if (k == 2) {
                if (n%2) cout<<"NO"<<endl;
                else {
                    cout<<"YES"<<endl;
                    cout<<n/2<<endl;
                    for (int i = 0; i < n/2; i++)
                    {
                        cout<<2<<" ";
                    }
                    cout<<endl;
                }
            }
            else {
                cout<<"YES"<<endl;
                cout<<n/2<<endl;
                if (n%2) {
                    for (int i = 0; i < n/2-1; i++)
                    {
                        cout<<2<<" ";
                    }
                    cout<<3<<endl;
                } else {
                    for (int i = 0; i < n/2; i++)
                    {
                        cout<<2<<" ";
                    }
                    cout<<endl;
                }
            }
        }
    }

    return 0;
}