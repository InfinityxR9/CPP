#include <iostream>

using namespace std;

int main()
{
    cout << "This is the tut 11" << endl;
    // for (int i = 0; i <= 4; i++)
    // {
    //     if (i == 2)
    //     {
    //         continue;   // continue keyword will skip the present the iteration and go out of the entire loop
    //     }
    //     cout << i << endl;
    // }

    for (int i = 0; i <= 4; i++)
    {
        if (i == 2)
        {
            break;  // Break keyword will break the loop and go out of the entire loop
        }
        cout << i << endl;
    }

    return 0;
}