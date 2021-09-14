#include <iostream>

using namespace std;

/* // struct employee
typedef struct employee
{
    int eId;
    char favChar;
    float salary;
} ep;
// }; */

union money
{
    int rice;
    char car;
    float pounds;
};

int main()
{
    cout << "This is  tut 14" << endl;
    /* // struct employee harry;
    ep harry;
    harry.eId = 1;
    harry.favChar = 'h';
    harry.salary = 1200000;
    cout << "The value is: " << harry.salary << endl;
    cout << "The value is: " << harry.favChar << endl;
    cout << "The value is: " << harry.salary << endl;

    // struct employee aryan;
    ep aryan;
    aryan.eId = 2;
    aryan.favChar = 'a';
    aryan.salary = 9999999999999;
    cout << "The value is: " << aryan.salary << endl;
    cout << "The value is: " << aryan.favChar << endl;
    cout << "The value is: " << aryan.salary << endl; */

    // Unions
    // union money m1;
    // m1.rice = 21454;
    // m1.car = 'c';
    // cout << m1.rice;

    enum Meal
    {
        breakfast,
        lunch,
        dinner
    };

    Meal m1 = lunch;

    cout << m1;
    // cout << breakfast;
    // cout << lunch;
    // cout << dinner;

    return 0;
}