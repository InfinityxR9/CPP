#include <iostream>
#include <vector>

/*
The DUTCH NATIONAL FLAG ALGORITHM (DNF ALGO)
*Given an array of 0s, 1s and 2s. Symbolically, representing colors Red, Blue and Black of balls.
*We have to sort the array such that the same color balls are adjacent. (Without using any in-built sort function)

*Three Pass Approach (Brute Force):
    *We count the number of occurences of 0s, 1s and 2s
    *Redefine the array elements accordingly

*DNF Three Pointers-Single Pass Approach:
    *We create three pointers, namely, low, mid, high
    *We assign the unsorted array part ranging from mid to high pointer values.
    *We sort untill mid == high (i.e., the unsorted part vanishes)
    *The part of 0 to low - 1 is includes all the 0s, low to mid - 1 all the 1s, high + 1 to size - 1 all the 2s.
    *The remaining part of mid to high includes the unsorted elements, which ultimately vanishes. (Base condition)

    *Initialse low = 0, mid = 0, high = size - 1
    *If we encounter mid val = 0, swap(low val, mid val), low++, mid++
    *If we encounter mid val = 1, mid++
    *If we encounter mid val = 0, swap(high val, mid val), high--

Time Complexity:    O(n)
Space Complexity:   O(1)

Leetcode Reference https://leetcode.com/problems/sort-colors/description/
*/

using namespace std;

void dnf_sort(vector<int> &arr)
{
    int mid = 0, high = arr.size() - 1, low = 0, temp;

    while (mid <= high)
    {
        if (arr[mid] == 0)
        {
            temp = arr[mid];
            arr[mid] = arr[low];
            arr[low] = temp;
            mid++;
            low++;
        }
        else if (arr[mid] == 1)
            mid++;
        else
        {
            temp = arr[mid];
            arr[mid] = arr[high];
            arr[high] = temp;
            high--;
        }
    }
}

void display(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main()
{
    vector<int> arr = {2, 0, 2, 1, 1, 0};
    dnf_sort(arr);
    display(arr);

    return 0;
}