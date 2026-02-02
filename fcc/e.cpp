#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        long long X;

        cin >> n;
        cin >> X;

        vector<int> arr;

        while (n--)
        {
            int element;
            cin >> element;
            arr.push_back(element);
        }

        long long sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += arr[i];
        }

        if (sum <= X)
        {
            cout << n << endl;
            for (int i = 1; i <= n; i++)
            {
                cout << i << " ";
            }
        }
        else
        {
            long long delta = X - sum;
            vector<int> original = arr;

            sort(arr.begin(), arr.end());
            vector<int> exclude;

            for (int i = n - 1; ((i >= 0) && (delta > 0)); i--)
            {
                if (arr[i] >= delta)
                {
                    exclude.push_back(arr[i]);
                    break;
                }
                else if (arr[i] < delta)
                {
                    exclude.push_back(arr[i]);
                    delta = delta - arr[i];
                }
            }

            cout << n - exclude.size() << endl;
            unordered_set<int> original_index;
            for (int i = 0; i < exclude.size(); i++)
            {
                auto index = find(original.begin(), original.end(), exclude[i]);
                original_index.insert(index+1);
            }

            for (int i=1; i <= n; i++) {
                if (original_index.find(i) == original_index.end()) {
                    cout<<i<< " ";
                }
            }
        }
    }

    return 0;
}