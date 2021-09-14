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

    // float d = 3.14F;
    // long double e = 3.14159654564L; // will be estimated as 3.146
    // cout << "The size of 3.14l is " << sizeof(3.14l) << endl;
    // cout << "The size of 3.14L is " << sizeof(3.14L) << endl;
    // cout << "The size of 3.14f is " << sizeof(3.14f) << endl;
    // cout << "The size of 3.14F is " << sizeof(3.14F) << endl;
    // cout << "The size of 3.14 is " << sizeof(3.14) << endl;
    // cout << "The value of d is: " << d << " The value of e is: " << e << endl;

    // Reference Variables

    // float vari = 355;
    // float & vari2 = vari;   // vari2 is now a reference variable of vari
    // cout<<vari<<endl;
    // cout<<vari2<<endl;

    // TypeCasting VAriables
    int a = 45;
    float b = 45.62;
    cout << "The value of a is " << a << endl;
    cout << "The value of float a is " << (float)a << endl;
    cout << "The value of int b is " << (int)b << endl;

    // (int)a = int(a)
    int c = int(b);
    cout << c << endl;

    cout << a + b << endl;
    cout << a + int(b) << endl;
    cout << a + (int)b << endl;

    return 0;
}