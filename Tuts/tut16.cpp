#include <iostream>

using namespace std;

void swap(int a, int b) // this will not work
{
    int temp = a;
    a = b;
    b = temp;
}

int sum(int a, int b)
{
    int c = a + b;
    return c;
}

// Call by reference using pointers
void swapPointer(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Call by reference using C++ reference variables
int &swapReferenceVar(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
    return a;
}

int main()
{
    cout << "This is tut 16\n";
    int a = 4, b = 5;
    cout << "The sum of 4 and 5 is: " << sum(a, b) << endl;
    cout << "The value of a and b is: " << a << " " << b << endl;
    // swap(a, b);        // this will not swap
    // swapPointer(&a, &b); // This will swap
    swapReferenceVar(a, b) = 766; // Return by reference
    cout << "The value of a and b is: " << a << " " << b << endl;

    return 0;
}