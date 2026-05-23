#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin>>n;
        vector<int> arr;
        while (n--) {
            int val;
            cin>>val;
            arr.push_back(val);
        }
        if (arr[0] == 1) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }

    return 0;
}