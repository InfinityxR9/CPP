#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, m, k;
        cin >> n >> m >> k;

        vector<int> a;
        for (int i = 0; i < n; i++)
        {
            int val;
            cin >> val;
            a.push_back(val);
        }

        set<int> b;
        for (int i = 0; i < m; i++)
        {
            int val;
            cin >> val;
            b.insert(val);
        }

        string str;
        cin>>str;

        set<int> exclude;
        for (int i = 0; i < k; i++)
        {
            int dead_counter = 0;
            if (str[i] == 'L')
            {
                for (int j = 0; j < n; j++)
                {
                    if (exclude.find(j) == exclude.end())
                    {
                        a[j]--;
                    }
                }
            }
            else
            {
                for (int j = 0; j < n; j++)
                {
                    if (exclude.find(j) == exclude.end())
                    {
                        a[j]++;
                    }
                }
            }
            for (int z = 0; z < n; z++)
            {
                if ((b.find(a[z]) != b.end()) && (exclude.find(z) == exclude.end()))
                {
                    cout<<"here";
                    dead_counter++;
                    exclude.insert(z);
                }
            }

            cout << dead_counter << " ";
        }

        cout << endl;
    }

    return 0;
}