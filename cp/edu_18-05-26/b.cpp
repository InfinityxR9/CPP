#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        string str;
        cin >> str;
        int len_4 = 0;
        for (char c : str)
        {
            if (c == '4')
                len_4++;
        }

        bool flag = false;
        int two = 0;
        for (char c : str)
        {
            if (c == '1' || c == '3')
                flag = true;
            if (c == '2' && flag)
                two++;
        }
        flag = false;
        int ones = 0;
        for (int i = str.length() - 1; i >= 0; i--)
        {
            if (str[i] == '2')
                flag = true;
            if (flag && (str[i] == '1' || str[i] == '3'))
                ones++;
        }

        cout << len_4 + min(two, ones) << endl;
    }

    return 0;
}