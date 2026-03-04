#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define SIZE 150

int main()
{
    ofstream fout("input.in");

    int M = SIZE;
    int N = SIZE;

    fout << M << " " << N << "\n";

    int matrix[SIZE][SIZE];

    // Initialize background to 0
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            matrix[i][j] = 0;

    // ---------- LARGE RECTANGLE ----------
    // Rectangle from rows 20–80 and cols 30–100
    for (int i = 20; i <= 80; i++)
        for (int j = 30; j <= 100; j++)
            matrix[i][j] = 100;

    // ---------- LARGE CIRCLE ----------
    // Center at (110, 110), radius = 25
    int cx = 110;
    int cy = 110;
    int r = 25;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int dx = i - cx;
            int dy = j - cy;

            if (dx * dx + dy * dy <= r * r)
                matrix[i][j] = 150;
        }
    }

    // Write matrix to file
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            fout << matrix[i][j] << " ";
        fout << "\n";
    }

    fout.close();

    cout << "input.in generated successfully.\n";

    return 0;
}