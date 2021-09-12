#include <iostream>

using namespace std;

int c = 45;

int main()
{
    // int a, b, c;
    // cout << "Enter the value of a: " << endl;
    // cin >> a;
    // cout << "Enter the value of b: " << endl;
    // cin >> b;
    // c = a + b;
    // cout << "The value of global c is: " << ::c << endl; // :: is called as scope resolution operator
    // cout << "The value of local c is: " << c << endl;
    // // cout << a << b << c;

    float d = 3.14;
    long double e = 3.14159654564;  // will be estimated as 3.146
    cout << "The value of d is: " << d << " The value of e is: " << e << endl;

    return 0;
}