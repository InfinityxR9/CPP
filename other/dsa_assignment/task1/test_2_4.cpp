#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define SIZE 180

void clearMatrix(int matrix[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            matrix[i][j] = 0;
}

void writeToFile(int matrix[SIZE][SIZE])
{
    ofstream fout("input.in");
    fout << SIZE << " " << SIZE << "\n";

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            fout << matrix[i][j] << " ";
        fout << "\n";
    }

    fout.close();
    cout << "input.in generated.\n";
}

int main()
{
    int matrix[SIZE][SIZE];
    clearMatrix(matrix);

    int testCase = 4;   // Change this 1–4 to switch cases

    // ===============================
    // TEST CASE 1
    // Large Rectangle + Large Circle
    // ===============================
    if (testCase == 1)
    {
        // Rectangle
        for (int i = 20; i <= 100; i++)
            for (int j = 30; j <= 120; j++)
                matrix[i][j] = 90;

        // Circle
        int cx = 130, cy = 130, r = 25;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if ((i - cx)*(i - cx) + (j - cy)*(j - cy) <= r*r)
                    matrix[i][j] = 150;
    }

    // ===============================
    // TEST CASE 2
    // Two Circles (Different Sizes)
    // ===============================
    if (testCase == 2)
    {
        int cx1 = 60, cy1 = 60, r1 = 30;
        int cx2 = 130, cy2 = 50, r2 = 20;

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if ((i - cx1)*(i - cx1) + (j - cy1)*(j - cy1) <= r1*r1)
                    matrix[i][j] = 120;

                if ((i - cx2)*(i - cx2) + (j - cy2)*(j - cy2) <= r2*r2)
                    matrix[i][j] = 170;
            }
        }
    }

    // ===============================
    // TEST CASE 3
    // Multiple Rectangles
    // ===============================
    if (testCase == 3)
    {
        // Big rectangle
        for (int i = 30; i <= 90; i++)
            for (int j = 40; j <= 140; j++)
                matrix[i][j] = 100;

        // Smaller rectangle
        for (int i = 110; i <= 150; i++)
            for (int j = 20; j <= 70; j++)
                matrix[i][j] = 140;
    }

    // ===============================
    // TEST CASE 4
    // Circle touching Rectangle (edge stress)
    // ===============================
    if (testCase == 4)
    {
        // Rectangle
        for (int i = 40; i <= 110; i++)
            for (int j = 50; j <= 130; j++)
                matrix[i][j] = 80;

        // Circle touching right edge of rectangle
        int cx = 110, cy = 140, r = 30;

        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if ((i - cx)*(i - cx) + (j - cy)*(j - cy) <= r*r)
                    matrix[i][j] = 160;
    }

    writeToFile(matrix);

    return 0;
}