#include <iostream>

using namespace std;

int add(int a, int b)
{
    cout << "using function with 2 arguments!" << endl;
    return a + b;
}

int add(int a, int b, int c)
{
    cout << "using function with 3 arguments!" << endl;
    return a + b + c;
}

int volume(double r, int h)
{
    return (3.14 * r * r * h);
}

int volume(int a)
{
    return (a * a * a);
}

int volume(int a, int b, int h)
{
    return (a * b * h);
}

int main()
{
    cout << "The sum of 4 and 5 is " << add(4, 5) << endl;
    cout << "The sum of 4, 5 and 6 is " << add(4, 6, 5) << endl;
    return 0;
}