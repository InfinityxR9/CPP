#include <iostream> // This is a system header file

// There are two types of header files
// System header files - comes with the compiler
// user defined header files - header files defined by the programmer
// For example
// #include<demoHeaderFile.h>
// or
// #include "demoHeaderFile.h"
// Note: Do not use semi colon while including the header file and {file must be there in the current directory (for user defined header files)}

using namespace std;

int main()
{
    cout << "This is hello world program" << endl;
    cout << "Let's learn operators in C++\n";
    cout << "Following are the types of the operators in C++\n";
    // Arithmetic Operators
    int a = 4, b = 5;
    cout << "the sum is: " << a + b << endl;
    cout << "the difference is: " << a - b << endl;
    cout << "the product is: " << a * b << endl;
    cout << "the quotient is: " << a / b << endl;
    cout << "the modulus is: " << a % b << endl;
    cout << "the post increment operator of a is: " << a++ << endl;
    cout << "the pre increment operator of a is: " << ++a << endl;
    cout << "the pre decrement operator of a is: " << --a << endl;
    cout << "the post decrement operator of a is: " << a-- << endl;

    // Assigment operators (=) - used to assign the values of the variables

    // Comparsion Operators - compares and return true or false in the form of 1 or 0 respectively, operants are (<,>,==,!=, <=,>=) and they  must be enclosed in brackets

    cout << "The value of a == b " << (a == b) << endl; // a==b returns 0 (false)
    cout << "The value of a != b " << (a != b) << endl; // a==b returns 0 (false)

    // Logical Operators (!, ||, &&)  - all the operants takes two or more statements
    // called as logical not, logical or and (logical and) operators respectively
    // ! returns the inverse of the overall value - if a returns true then !a returns false
    // && returns true if all the statements return true
    // || returns true if any one of the statements return true
    // Examples over there
    cout << "The value of (a == b || a != b) " << (a == b || a != b) << endl; //returns 1 (true)
    cout << "The value of (a == b && a != b) " << (a == b && a != b) << endl; //returns 0(false)
    cout << "The value of (!(a==b)) " << (!(a == b)) << endl;                 //returns 1(true)

    // This is the demo alarm or beep sound
    cout << "The sound of the alarm or Beep is this \a";
    return 0;
}