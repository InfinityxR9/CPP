#include <iostream>

using namespace std;

int sum(int a, int b) // you must use the inline functions when there is very small code inside the braces
{
    // static int c = 0; // this excutes only once and don't use the static with inline funcs
    // c++;
    return a * b;
}

float moneyRecieved(float initMoney, float factor = 1.04) // default parameters must be at the extereme right
{
    return initMoney * factor;
}

// void constant(const char *p) constant variables in c++
// { // code }

int main()
{
    // int a, b;
    // cout << "Enter the value of a and b: ";
    // cin >> a >> b;
    // cout << "The sum of a and b is: " << sum(a, b) << endl;
    int money = 100000;
    cout << "If you have " << money << " Rs in your bank account, you'll recieve " << moneyRecieved(money) << endl;
    cout << "For VIP: If you have " << money << " Rs in your bank account, you'll recieve " << moneyRecieved(money, 1.10);

    return 0;
}