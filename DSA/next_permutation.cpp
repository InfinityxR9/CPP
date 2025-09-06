#include <iostream>
#include <vector>

using namespace std;

/*
The Next Permutation Problem on Array of Positive integers
*To find the next permutation of the given number, in lexicographic order

Intuition:
    *When the next permutation is calculated, few starting characters are in-place (not swapped)
    *The end character of such a subarray is called pivot, whose right subarray is also sorted in decreasing order

Algorithm:
    *find pivot: A[i] < A[i + 1] for the first time from right
    *find the number just greater than pivot from the right sub array
    *swap the pivot and that number
    *reverse the right subarray of the old pivot index

If the next permutation doesn't exist, return the first permutation (Reversed array)

Time Complexity:    O(n)
Space Complexity:   O(1)

Leetcode Reference https://leetcode.com/problems/next-permutation/description/
*/

void display(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

void nextPermutation(vector<int> &arr)
{
    int pivot = -1, n = arr.size();

    for (int i = n - 2; i >= 0; i--)
    {
        if (arr[i] < arr[i + 1])
        {
            pivot = i;
            break;
        }
    }

    if (pivot == -1)
    {
        int str = 0, end = n - 1, temp;
        while (str < end)
        {
            temp = arr[str];
            arr[str++] = arr[end];
            arr[end--] = temp;
        }
        return;
    }

    for (int i = n - 1; i > pivot; i--)
    {
        if (arr[pivot] < arr[i])
        {
            int temp = arr[i];
            arr[i] = arr[pivot];
            arr[pivot] = temp;
            break;
        }
    }

    int str = pivot + 1, end = n - 1, temp;
    while (str < end)
    {
        temp = arr[str];
        arr[str++] = arr[end];
        arr[end--] = temp;
    }
}

int main()
{
    vector<int> arr = {5, 4, 3, 6};
    nextPermutation(arr);
    display(arr);
    nextPermutation(arr);
    display(arr);
    nextPermutation(arr);
    display(arr);
    nextPermutation(arr);
    display(arr);
    nextPermutation(arr);
    display(arr);
    nextPermutation(arr);
    display(arr);
    nextPermutation(arr);
    display(arr);
    nextPermutation(arr);
    display(arr);
    nextPermutation(arr);
    display(arr);
    nextPermutation(arr);
    display(arr);

    return 0;
}