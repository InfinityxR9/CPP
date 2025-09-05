#include <iostream>
#include <vector>

using namespace std;

/*
Painters Partition Problem
*There is a given list of the length of boards, and each painter takes 1 unit of time to paint 1 unit of board
*If we are given M painters, what is the minimum time in which complete length of all the boards is to be painted, Given painters can paint the boards in contiguous manner only
*This problem is very similar to the "Book Allocation Problem"


Time Complexity:    O(n * lg N) (n --> total boards, N --> total length)
Space Complexity:   O(1)
*/

bool isValid(vector<int> &arr, int m, int maxAllowed) // --> O(n)
{
    int board = 1, length = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > maxAllowed)
            return false;

        if (length + arr[i] <= maxAllowed)
            length += arr[i];
        else
        {
            board++;
            length = arr[i];
        }
    }

    return board > m ? false : true;
}

int partition(vector<int> &arr, int m) // --> O(n * lg N) (N -> sum/total length)
{
    int n = arr.size();
    int sum = 0;

    if (m > n)
        return -1;

    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    int low = 0, high = sum; // Range of possible answers
    int ans = -1, mid;

    while (low <= high) // --> O(n * lg N) (N = range = high - low)
    {
        mid = low + (high - low) / 2;

        if (isValid(arr, m, mid))
        {
            ans = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }

    return ans;
}

int main()
{
    vector<int> arr = {40,30,10,20};
    int m = 2;

    cout << partition(arr, m) << endl;

    return 0;
}