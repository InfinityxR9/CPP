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
        cin >> n;
        if (n == 1)
        {
            cout << "YES" << endl;
            continue;
        }
        vector<ll> arr;
        for (int i = 0; i < n; i++)
        {
            ll val;
            cin >> val;
            arr.push_back(val);
        }

        vector<pair<ll, ll>> subs;
        ll mx = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            ll a = arr[i];
            mx = max(mx, a);
            if (a < mx)
            {
                ll fist = arr[i-1] - arr[i];
                ll sec = i + 1 < n ? arr[i + 1] - arr[i] : INT_MAX;
                subs.push_back({fist, sec});
            }
        }

        if (subs.empty())
        {
            cout << "YES" << endl;
            continue;
        }

        ll l = INT_MIN;
        ll r = INT_MAX;
        for (int i = 0; i < subs.size(); i++)
        {
            l = max(l, subs[i].first);
            r = min(r, subs[i].second);
        }
        if (l <= r)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}