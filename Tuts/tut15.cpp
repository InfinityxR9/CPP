#include <iostream>

using namespace std;

// Function prototype
// type function-name (parameters)

// If you want some function not to return something you can declare the function as follows
/* void func-name (arguments) {
    // code
} */
// example
void greet(void); // or void greet()

int sum(int a, int b);

int main()
{
    // Do once use forever = functions
    // cout << sum(4, 6);
    greet();
    int num1, num2;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;
    cout << "The sum is: " << sum(num1, num2);

    // num1 and num2 are actual params

    return 0; // returing 0 to the os means the program is excuted successfully
}

int sum(int a, int b)
{
    // a and b are formal params that will be taking values from the actual params that are to be given when the functions is called!
    int c = a + b;
    return c;
}

// Example
void greet()
{
    cout << "Hello, Welcome to Application Aryan Official\n";
}