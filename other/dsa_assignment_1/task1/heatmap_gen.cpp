#include <iostream>
#include <fstream>

using namespace std;

#define SIZE 200

int matrix[SIZE][SIZE];

char intensityToAscii(int val)
{
    if (val <= 30)
        return ' ';
    else if (val <= 60)
        return '.';
    else if (val <= 100)
        return ':';
    else if (val <= 140)
        return '*';
    else if (val <= 180)
        return 'O';
    else
        return '#';
}

int main()
{
    int cx1 = 60, cy1 = 60, r1 = 30;
    int cx2 = 130, cy2 = 50, r2 = 20;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if ((i - cx1) * (i - cx1) + (j - cy1) * (j - cy1) <= r1 * r1)
                matrix[i][j] = 120;

            if ((i - cx2) * (i - cx2) + (j - cy2) * (j - cy2) <= r2 * r2)
                matrix[i][j] = 170;
        }
    }

    /* Write ASCII heatmap visualization */
    ofstream vis("new_input.in");

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            vis << intensityToAscii(matrix[i][j]);
        vis << endl;
    }

    vis.close();

    return 0;
}