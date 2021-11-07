#include <iostream>
#include <string>

using namespace std;

string repeat(string s, int n)
{
    string s1 = s;

    for (int i = 1; i < n; i++)
    {
        s += s1;
    }

    return s;
}

int main()
{
    int rows;
    string s = "* ";
    cout << "Enter the number of rows: ";
    cin >> rows;
    if (rows == 0)
    {
        cout << "You must enter the number of rows\n";
        main();
    }
    else
    {
        for (int i = 1; i <= rows; i++)
        {
            cout << repeat(s, i) << endl;
        }
        char exit;
        cout << "Press any key to exit: ";
        cin >> exit;
        if (exit != 'e') {
            main();
        }
    }

    return 0;
}