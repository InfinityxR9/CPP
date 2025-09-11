#include <iostream>

/*
Euclid's Algorithm to find the gcd of two numbers.

Theorem:
    *gcd(a, b) = gcd(a - b, b) if a > b
    *gcd(a, b) = gcd(a, b - a) if a < b
    *gcd(a, 0) = a

Since, repeated subtraction is nothing but Division, we can optimise it as:
Theorem:
    *gcd(a, b) = gcd(a % b, b) if a > b
    *gcd(a, b) = gcd(a, b % a) if a < b
    *gcd(a, 0) = a

*/

using namespace std;

int euclid_gcd(int a, int b)    // Taking the assumption that a > b
{
    if (b == 0)
        return a;

    return euclid_gcd(b, a % b);
}

int main()
{
    cout << euclid_gcd(4, 1) << endl;
    cout << euclid_gcd(4, 4) << endl;
    cout << euclid_gcd(4, 2) << endl;
    cout << euclid_gcd(4, 0) << endl;
    cout << euclid_gcd(3, 2) << endl;

    return 0;
}