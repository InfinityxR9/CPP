#include <bits/stdc++.h>

using namespace std;

bool check(vector<int> changes, int size, int h)
{
    for (int i = 0; i < size; i++)
    {
        if (changes[i] > h)
            return false;
    }

    return true;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, m, h;
        cin >> n >> m >> h;
        
        vector<int> arr;
        for (int i = 0; i < n; i++)
        {
            int val;
            cin >> val;
            arr.push_back(val);
        }

        vector<int> changes = arr;

        while (m--)
        {
            int b, c;
            cin >> b >> c;
            changes[b-1] += c;

            if (check(changes, n, h) == false)
            {
                changes = arr;
            }
        }

        for (int i = 0; i < n; i++)
        {
            cout << changes[i] << " ";
        }
        cout << endl;
    }

    return 0;
}