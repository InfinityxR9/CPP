#include <iostream>

using namespace std;

int main()
{
    int num1, num2;
    cout << "Enter the value of num1: "; // This is called insertion operator
    cin >> num1;                         // Extraction operator
    cout << "Enter the value of num2: ";
    cin >> num2;
    int sum = num1 + num2;
    cout << "The sum is: " << sum;
    return 0;
}
