#include <iostream>
#include <vector>

using namespace std;

/*
Traverse the Given 2D Matrix in a Spiral Fashion
Store the elements in a vector<int> and return the vector

Approach:
    *Start with considering boundaries starting row, ending row, starting column, ending column
    *Traverse the boundaries in order of starting row, ending column, ending row, starting column
    *Update the boundaries
    *Traverse with new boundaries
    *If both the boundaries become equal (either in row or column) traverse only once (Occurs in odd sized matrices)

Time Complexity:    O(m*n) (m --> number of rows, n --> number of columns)
Space Complexity:   O(1) (An vector is allowed as per problem and not counted in auxillary space)

Leetcode reference: https://leetcode.com/problems/spiral-matrix/
*/

vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    int srow = 0, erow = m - 1, scol = 0, ecol = n - 1;
    vector<int> trav;

    while (srow <= erow && scol <= ecol)
    {
        for (int i = scol; i <= ecol; i++)
            trav.push_back(matrix[srow][i]);
        for (int i = srow + 1; i < erow; i++)
            trav.push_back(matrix[i][ecol]);
        if (srow != erow)
        {
            for (int i = ecol; i >= scol; i--)
                trav.push_back(matrix[erow][i]);
        }
        if (scol != ecol)
        {
            for (int i = erow - 1; i > srow; i--)
                trav.push_back(matrix[i][scol]);
        }

        scol++;
        ecol--;
        srow++;
        erow--;
    }

    return trav;
}

void display(vector<int> &arr)
{
    cout << "{";
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << "}\n";
}

int main()
{
    vector<vector<int>> mat1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<int> ans1 = spiralOrder(mat1);
    vector<vector<int>> mat2 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    vector<int> ans2 = spiralOrder(mat2);
    display(ans1);
    display(ans2);

    return 0;
}