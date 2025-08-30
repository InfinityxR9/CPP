#include <iostream>
#include <vector>

using namespace std;

// To find the pair of numbers in a sorted array with a given target sum using Two pointers approach (O(n))
pair<int, int> pair_sum(vector<int> &arr, int target)
{
    int i = 0, j = arr.size() - 1;
    int sum;

    while (i <= j)
    {
        sum = arr[i] + arr[j];

        if (sum > target)
            j--;
        else if (sum < target)
            i++;
        else
        {
            pair<int,int> ans = {arr[i], arr[j]};
            return ans;
        }
    }
}

int main()
{
    vector<int> arr = {2, 7, 11, 15};
    pair<int,int> ans = pair_sum(arr, 9);
    cout << "{" << ans.first << ", " << ans.second << "}\n";

    return 0;
}