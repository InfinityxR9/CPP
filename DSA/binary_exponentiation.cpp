#include <iostream>

using namespace std;

/*
Binary Exponentiation!
*To evaluate the value of pow(x, n) (Means x**n)
*Usually we might be requiring O(n) Time Complexity if we try to do it so by repetitive multiplication.
*However, in problem cases where the value of n can range to 2^31 - 1, it might give TLE Errors.
*In such a case, we use binary exponentiation

Algorithm:
    *We convert n into its binary form and then successively multiply x by its squared values.
    *1 refers to inclusion of the squared into answer, 0 represents exclusion.
    *In either case, we square the value of x and store it into itself

Example:
pow(3, 5) (Or, 3^5)
    *convert 5 into binary as (101)
    *Start from Rightmost bit, and successively multiply, squaring in each step.
    *Equivalent to, (((3^4)*1)*((3^2)*0)*((3^0)*1))

Time Complexity:    O(lg n)
Space Complexity:   O(1)

Leetcode Reference: https://leetcode.com/problems/powx-n/
*/

double pow(double x, long n)
{
    long binForm = n;
    double ans = 1;

    // Edge Cases for Optimisation
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    if (x == 0)
        return 0;
    if (x == -1 && (n % 2 == 0))
        return 1;
    if (x == -1 && (n % 2 == 1))
        return -1;

    // Case to handle Negative Values
    if (n < 0)
    {
        x = 1 / x;
        binForm = -binForm;
    }

    while (binForm > 0)
    {
        if (binForm % 2 == 1)
        {
            ans *= x;
        }

        x *= x;
        binForm /= 2;
    }

    return ans;
}

int main()
{
    cout << pow(4, 2) << endl;
    cout << pow(2.1, 3) << endl;
    cout << pow(2, -2) << endl;
    cout << pow(3, 254) << endl;

    return 0;
}