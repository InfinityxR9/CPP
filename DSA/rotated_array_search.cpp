#include <iostream>
#include <vector>

using namespace std;

// Rotated Sorted Arrays are formed by rotating the entire array about a pivot, which was initially ascending sorting array
// *eg: A = {1,2,3,4,5,6}, then rot A about val 3 would be {5,6,1,2,3,4}

// *Either of the left or right half of a Rotated Sorted Array is always fully sorted, and it can be determined by doing comparison of low value and mid value

// *Time Complexity: O(lg n) (Binary Search Approach)
// For brute force approach, O(n) (Linear Search)

// *Space Complexity: O(1)

// Search in a Rotated Sorted Array using Binary Search
int search_rotated_array(vector<int> &nums, int target)
{
    int low = 0, high = nums.size() - 1, mid;

    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (nums[mid] == target)
            return mid;

        if (nums[mid] >= nums[low]) // Left sorted
        {
            if (nums[low] <= target && target <= nums[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        else // Right sorted
        {
            if (nums[mid] <= target && target <= nums[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }

    return -1;
}

int main()
{
    vector<int> A = {5, 6, 7, 1, 2, 3, 4};
    cout << search_rotated_array(A, 4) << endl;

    return 0;
}