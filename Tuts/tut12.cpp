#include <iostream>

using namespace std;

int main()
{
    cout << "This is  tut 12 about pointers" << endl;
    // Pointers = data type that holds the address of other variables

    int a = 3;
    int *b = &a;
    cout << b << endl;

    // & --> (address of) operator
    cout << "The address of a is: " << &a << endl;
    cout << "The address of a is: " << b << endl;

    // * --> deference operator
    cout << "The value at adress b is: " << *b << endl;

    // Pointer to pointer   --> optional for now
    int **c = &b;
    cout << c;

    return 0;
}