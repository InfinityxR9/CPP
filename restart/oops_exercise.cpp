#include <iostream>
#include <cmath>

using namespace std;

// After incorporating the Ambiguity resolution in Inheritance
// PRO TIP: Local methods are always on par priority in times of ambiguity in Inheritance

// Simple calculator
class Simple_Calculator
{
protected:
    float num_1, num_2;

public:
    Simple_Calculator()
    {
        cout << "Enter number 1 (simple): ";
        cin >> num_1;
        cout << "Enter number 2 (simple): ";
        cin >> num_2;
    }

    void display_result()
    {
        cout << "Addition result: " << num_1 + num_2 << endl;
        cout << "Multiplication result: " << num_1 * num_2 << endl;
        cout << "Subtraction result: " << num_1 - num_2 << endl;
        cout << "Division result: " << num_1 / num_2 << endl;
    }
};

// Scientific Calculator
class Scientific_Calculator
{
protected:
    float num_1, num_2;

public:
    Scientific_Calculator()
    {
        cout << "Enter number 1 (scientific): ";
        cin >> num_1;
        cout << "Enter number 2 (scientific): ";
        cin >> num_2;
    }

    void display_result()
    {
        cout << "sine of number 1 result: " << sinf(num_1) << endl;
        cout << "sine of number 2 result: " << sinf(num_2) << endl;
        cout << "Square root of number 1 result: " << sqrtf(num_1) << endl;
        cout << "Square root of number 2 result: " << sqrtf(num_2) << endl;
        cout << "Cube Root of number 1 result: " << cbrtf(num_1) << endl;
        cout << "Cube Root of number 2 result: " << cbrtf(num_2) << endl;
        cout << "Power of number 1 to number 2 result: " << powl(num_1, num_2) << endl;
    }
};

// Hybrid Calculator (Child from Simple and Scientific Calculator)
class Hybrid_Calculator : public Simple_Calculator, public Scientific_Calculator
{
public:
    Hybrid_Calculator()
    {
        Simple_Calculator::display_result();
        Scientific_Calculator::display_result();
    }
};

int main()
{
    // Simple_Calculator sc = Simple_Calculator();
    // sc.display_result();

    // Scientific_Calculator sc = Scientific_Calculator();
    // sc.display_result();

    Hybrid_Calculator sc = Hybrid_Calculator();

    return 0;
}