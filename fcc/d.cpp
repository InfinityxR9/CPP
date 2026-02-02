#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int N;
        cin >> N;

        vector<int> work;
        vector<int> deadline;

        while (N--)
        {
            long long a;
            cin >> a;
            long long b;
            cin >> b;
            work.push_back(a);
            deadline.push_back(b);
        }

        long long sum = 0;
        for (int i = 0; i < work.size(); i++)
        {
            sum += work[i];
        }

        long long max = deadline[0];
        for (int i = 0; i < deadline.size(); i++)
        {
            if (deadline[i] > max)
            {
                max = deadline[i];
            }
        }

        if (sum > max) {
            cout<<"NO"<<endl;
        }
        else {
            int i = 0;
            int j = 0;

            bool flag = true;
            while ((i < work.size()) && (j < deadline.size())) {
                if (work[i] > deadline[j]) {
                    cout<<"NO"<<endl;
                    flag = false;
                    break;
                }
                else {
                    i++; j++;
                }
            }

            if (flag) {
                cout<<"YES"<<endl;
            }
        }
    }

    return 0;
}