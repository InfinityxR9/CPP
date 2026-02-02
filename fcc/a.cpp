#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        long long N;
        long long max;
        long long min;

        cin >> N;

        if (N == 1)
        {
            max = min = 1;
        }
        else
        {
            if (N % 2 == 0)
            {
                max = N / 2;
            }
            else
            {
                max = (N + 1) / 2;
            }
            long long rem = N % 3;
            if (rem == 0)
            {
                min = (N / 3);
            }
            else {
                min = (N/3) +1;
            }
        }

        cout << min << " " << max << endl;
    }

    return 0;
}