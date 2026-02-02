#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        long long N;
        cin>>N;

        int decimal = 0;
        long long no = N;

        while (no > 0) {
            if (no % 10 != 0) {
                decimal++;
            }
            no /= 10;
        }

        int binary = 0;
        no = N;

        while (no > 0) {
            if (no%2 != 0) {
                binary++;
            }

            no /= 2;
        }
        binary++;

        if (binary > decimal) {
            cout<<decimal<<endl;
        }
        else {
            cout<<binary<<endl;
        }
    }

    return 0;
}