#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Kadane's Algorithm for finding the maximum subarray sum in Array
int max_sum(vector<int> &arr)
{
    int currSum = 0, maxSum = INT_MIN;

    for (int i = 0; i < arr.size(); i++)
    {
        currSum += arr[i];
        maxSum = max(currSum, maxSum);

        if (currSum < 0)
            currSum = 0;
    }

    return maxSum;
}

int main()
{
    vector<int> arr = {3, -4, 5, 4, -1, 7, -8};
    cout << max_sum(arr) << endl;

    return 0;
}