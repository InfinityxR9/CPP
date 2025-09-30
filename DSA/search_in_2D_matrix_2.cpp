#include <iostream>
#include <vector>

using namespace std;

/*
Search a 2D matrix II:

Write an efficient algorithm that searches for a value target in an m x n integer matrix. This matrix has the following properties:
    *Integers in each row are sorted in ascending from left to right.
    *Integers in each column are sorted in ascending from top to bottom.

Given an integer target, return true if target is in matrix or false otherwise.

Approach:
    *In simple terms, the whole matrix is sorted in both column and row wise
    *Initialse the column to be the last column and the row to be the first row
    *If the value is greater than the target, we need to look up for a smaller value, decrease column
    *If the value is lesser than the target, we need to look up for a greater value, increase row

This same algorithm can also be used to search in a matrix I

Time Complexity:    O(m*n) (m --> number of rows and n --> number of columns)
Space Complexity:   O(1)

Leetcode Reference: https://leetcode.com/problems/search-a-2d-matrix-ii/
*/

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int row = 0, col = matrix[0].size() - 1;

    while (row < matrix.size() && col >= 0)
    {
        if (matrix[row][col] == target)
            return true;
        if (matrix[row][col] > target)
            col--;
        else
            row++;
    }

    return false;
}

int main()
{
    vector<vector<int>> matrix = {{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}};
    int target = 5;

    cout << searchMatrix(matrix, target) << endl;

    return 0;
}