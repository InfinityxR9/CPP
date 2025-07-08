#include <iostream>

using namespace std;

int &reference_var_check(int &x, int y)
{
    x++;
    y++;

    return x;
}

int main()
{
    int a = 5;
    int b = 10;
    int c;

    reference_var_check(a, b) = 56;

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    return 0;
}