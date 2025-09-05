#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Aggresive Cows Problem
*There are stalls at the given positions where cows are placed, the cows are very aggresive and thus tend to fight with each other.
*We have to arrange the M cows at specified positions (Array elements) such that the maximum distance between any two cows is minimum among all the possible arrangements.
*This problem is very similar to the "Book Allocation Problem"

Time Complexity:    O(n * lg N) (n --> total stalls, N --> Distance between the first and last occuring stall)
Space Complexity:   O(1)

REFERENCE: https://www.spoj.com/problems/AGGRCOW/
*/

bool isValid(vector<int> &arr, int m, int mid) // --> O(n)
{
    int cows = 1, lastStallPos = arr[0];

    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] - lastStallPos >= mid) {
            cows++;
            lastStallPos = arr[i];
        }

        if (cows == m)
            return true;
    }

    return false;
}

int getDistance(vector<int> &arr, int m) // --> O(n * lg N) (N --> Distance between the first and last occuring stall)
{
    int n = arr.size();
    sort(arr.begin(), arr.end());

    if (m > n)
        return -1;

    int low = 1, high = arr[n-1] - arr[0]; // Range of possible answers
    int ans = -1, mid;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (isValid(arr, m, mid))
        {
            ans = mid;
            low = mid + 1;
        }
        else
            high = mid - 1;
    }

    return ans;
}

int main()
{
    vector<int> arr = {1,8,4,2,9};
    int m = 3;

    cout << getDistance(arr, m) << endl;

    return 0;
}