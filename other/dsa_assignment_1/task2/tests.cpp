#include <iostream>
#include <fstream>

using namespace std;

#define MAX 200

void writeMatrix(int matrix[MAX][MAX], int M, int N)
{
    ofstream fout("input.in");
    fout << M << " " << N << endl;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            fout << matrix[i][j] << " ";
        fout << endl;
    }

    fout.close();
}

int main()
{
    int matrix[MAX][MAX] = {0};
    int M, N;

    int choice = 7;

    switch (choice)
    {

    /* ============================================================
       TEST 1: Single Solid Rectangle
       ============================================================ */
    case 1:
        M = 30; N = 30;

        for (int i = 5; i < 15; i++)
            for (int j = 5; j < 20; j++)
                matrix[i][j] = 1;

        break;

    /* ============================================================
       TEST 2: Two Separate Rectangles
       ============================================================ */
    case 2:
        M = 40; N = 40;

        for (int i = 3; i < 12; i++)
            for (int j = 3; j < 15; j++)
                matrix[i][j] = 1;

        for (int i = 20; i < 35; i++)
            for (int j = 18; j < 30; j++)
                matrix[i][j] = 1;

        break;

    /* ============================================================
       TEST 3: Hollow Square
       ============================================================ */
    case 3:
        M = 35; N = 35;

        for (int j = 10; j <= 25; j++)
        {
            matrix[10][j] = 1;
            matrix[25][j] = 1;
        }

        for (int i = 10; i <= 25; i++)
        {
            matrix[i][10] = 1;
            matrix[i][25] = 1;
        }

        break;

    /* ============================================================
       TEST 4: Mixed Scene (Rect + Hollow + Noise)
       ============================================================ */
    case 4:
        M = 50; N = 50;

        // rectangle
        for (int i = 5; i < 20; i++)
            for (int j = 5; j < 25; j++)
                matrix[i][j] = 1;

        // hollow square
        for (int j = 30; j <= 45; j++)
        {
            matrix[10][j] = 1;
            matrix[30][j] = 1;
        }

        for (int i = 10; i <= 30; i++)
        {
            matrix[i][30] = 1;
            matrix[i][45] = 1;
        }

        // noise pixels
        matrix[40][10] = 1;
        matrix[42][12] = 1;
        matrix[45][3]  = 1;

        break;

    /* ============================================================
       TEST 5: Snake Pattern (Stack Stress)
       Long thin connected path
       ============================================================ */
    case 5:
        M = 100; N = 100;

        for (int i = 0; i < 100; i++)
        {
            if (i % 2 == 0)
                for (int j = 0; j < 100; j++)
                    matrix[i][j] = 1;
            else
                matrix[i][99] = 1;
        }

        break;

    /* ============================================================
       TEST 6: Checkerboard (Max Components Stress)
       Every alternate pixel is isolated object
       ============================================================ */
    case 6:
        M = 60; N = 60;

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                if ((i + j) % 2 == 0)
                    matrix[i][j] = 1;

        break;

    /* ============================================================
       TEST 7: Massive Dense Block (Memory Stress)
       ============================================================ */
    case 7:
        M = 150; N = 150;

        for (int i = 10; i < 140; i++)
            for (int j = 10; j < 140; j++)
                matrix[i][j] = 1;

        break;

    default:
        cout << "Invalid choice.\n";
        return 0;
    }

    writeMatrix(matrix, M, N);

    cout << "input.in generated successfully.\n";
    return 0;
}