#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;

    while (t--)
    {
        int x, k;
        cin >> x >> k;

        if ((x < k) || (x % k))
        {
            cout << 1 << endl;
            cout << x << endl;
        }
        else
        {
            cout << 2 << endl;
            cout << 1 << " " << (x - 1) << endl;
        }
    }

    return 0;
}