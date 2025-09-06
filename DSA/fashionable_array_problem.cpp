#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Fashionable Array Problem
*We will call an array of integers A fashionable if min(A) + max(A) is divisible by 2 without a remainder, where
    *min(A) — the value of the minimum element of the array a
    *max(A) — the value of the maximum element of the array a

*You are given an array of integers a1,a2,…,an. In one operation, you can remove any element from this array. Your task is to determine the minimum number of operations required to make the array A fashionable.

Time Complexity:    O(n lg n)
Space Complexity:   O(1)

Codeforces Reference https://codeforces.com/problemset/problem/2110/A
*/

int ans(vector<int> &nums)
{
    int start = 0, end = nums.size() - 1, operations = 0;
    sort(nums.begin(), nums.end());

    while (start <= end)
    {
        if ((nums[start] + nums[end]) % 2 == 0)
            return operations;

        operations++;
        if ((nums[start] + nums[start + 1]) % 2 != 0)
            start++;
        else if ((nums[end] + nums[end - 1]) % 2 != 0)
            end--;
        else
            start++;
    }

    return -1;
}

int main()
{
    vector<int> arr = {2, 11, 4, 5, 6, 9, 7};
    vector<int> arr1 = {5, 2};
    vector<int> arr2 = {3, 1, 4, 1, 5, 9, 2};
    vector<int> arr3 = {2, 7, 4, 6, 9, 11, 5};
    vector<int> arr4 = {1, 2, 1};
    vector<int> arr5 = {2, 1};
    vector<int> arr6 = {8, 6, 3, 6, 4, 1, 1, 6};
    cout << "minimum operations: " << ans(arr) << endl;
    cout << "minimum operations: " << ans(arr1) << endl;
    cout << "minimum operations: " << ans(arr2) << endl;
    cout << "minimum operations: " << ans(arr3) << endl;
    cout << "minimum operations: " << ans(arr4) << endl;
    cout << "minimum operations: " << ans(arr5) << endl;
    cout << "minimum operations: " << ans(arr6) << endl;

    return 0;
}