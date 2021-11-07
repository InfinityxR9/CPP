#include <iostream>

using namespace std;

int factorial(int n)
{
    // n! = n * (n-1)!
    if (n == 1 || n == 0)
    {
        return 1;
    }

    return n * factorial(n - 1);
}

int fib(int n)
{
    if (n < 2)
    {
        return 1;
    }
    return fib(n - 2) + fib(n - 1);
}

int main()
{
    // cout << "This is tut 18\n";
    cout << "Enter a number: ";
    int num;
    cin >> num;
    // cout << "The factorial of " << num << " is: " << factorial(num) << endl;
    cout << "The number is " << fib(num) << endl;
    return 0;
}