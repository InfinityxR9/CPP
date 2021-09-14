#include <iostream>

using namespace std;

int main()
{
    // int marks[4] = {23, 57, 34, 354};
    int marks[] = {23, 57, 34, 354};
    int mathMarks[2];
    mathMarks[0] = 45;
    mathMarks[1] = 354;
    cout << mathMarks[0] << endl;
    cout << mathMarks[1] << endl;
    cout << "These marks are: " << endl;
    cout << marks[0] << endl;
    cout << marks[1] << endl;
    cout << marks[2] << endl;
    marks[2] = 6546;
    cout << "The new value of marks[2] is " << marks[2] << endl;
    cout << marks[3] << endl;

    // This is how you can loop over an array
    cout << "This is how you can loop over an array" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << marks[i] << endl;
    }

    // Quiz solution
    cout << "--------------------------------------------------------\nQuiz solution: " << endl;
    int i = 0;

    while (i < 4)
    {
        cout << marks[i] << endl;
        i++;
    }

    // using do while loop
    cout << "Using do while loop" << endl;
    int y = 0;
    do
    {
        cout << marks[y] << endl;
        y++;
    } while (y < 4);

    cout << "Quiz solved!\n----------------------------------------------------" << endl;
    char x;
    cout << "Press any key to proceed!: ";
    cin >> x;
    // Quiz solved! : run tut13.exe to check if it works or not!

    // marks --> address of first block
    // &marks --> wrong

    // Pointers arithmetic or using pointers using arrays
    // Basic formula
    // pointer address / address + i * sizeof(datatype)

    int *p = marks;
    cout << "The value of *(p) is " << *(p) << endl;
    cout << "The value of *(p + 1) is " << *(p + 1) << endl;
    cout << "The value of *(p + 2) is " << *(p + 2) << endl;
    cout << "The value of *(p + 3) is " << *(p + 3) << endl;

    return 0;
}