#include <iostream>
#include <vector>

using namespace std;

/*
Search a 2D matrix I:

*You are given an m x n integer matrix with the following two properties:
    *Each row is sorted in non-decreasing order.
    *The first integer of each row is greater than the last integer of the previous row.

Given an integer target, return true if target is in matrix or false otherwise.

Approach:
    *In simple terms, the whole matrix is sorted in zigzag pattern
    *Search the matrix's row's first values to find in which row the target lies
    *Then search in the row to finally find the target
    *Both searches to be done using the Binary Search Algorithm
    
Time Complexity:    O(lg (m*n)) (m --> number of rows and n --> number of columns)
Space Complexity:   O(1)

Leetcode Reference: https://leetcode.com/problems/search-a-2d-matrix/
*/

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int sRow = 0, eRow = matrix.size() - 1, sMid;

    while (sRow <= eRow)
    {
        sMid = sRow + (eRow - sRow) / 2;

        if (matrix[sMid][0] <= target &&
            matrix[sMid][matrix[sMid].size() - 1] >= target)
            break;
        else if (matrix[sMid][0] < target &&
                 matrix[sMid][matrix[sMid].size() - 1] < target)
            sRow = sMid + 1;
        else
            eRow = sMid - 1;
    }

    int low = 0, high = matrix[sMid].size() - 1, mid;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (matrix[sMid][mid] == target)
            return true;
        else if (matrix[sMid][mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return false;
}

int main()
{
    vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target = 3;

    cout << searchMatrix(matrix, target) << endl;

    return 0;
}