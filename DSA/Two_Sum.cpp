#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
Two Sum Problem:
Given a target sum, find two values in the given array without using the same element twice such that the sum is equal to the target. It is given that such unique pair exists.

Approach:
    *Brute Force: Find all the pairs and match the sum (O(n^2))
    *Better: Sort the array and then find the pair using two pointers (O(lg n))
    *Optimum: Using Hashing (Unordered Map in STL)

Hashing (Maps and Sets in STL, for quick searching)
    *Create an unordered map of value and index
    *Run a loop and assume that the arr[i] is the first num, if it is, then search if the assumed-second number is in the unordered map, if it is not, then store the assumed first number with the index.

Time Complexity:    O(n)
Space Complexity:   O(n)

Leetcode reference: https://leetcode.com/problems/two-sum/
*/

vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> map;
    int comp, iNum, i;

    for (i = 0; i < nums.size(); i++)
    {
        iNum = nums[i];
        comp = target - iNum;

        if (map.find(comp) != map.end())
            break;
        map[iNum] = i;
    }

    vector<int> ans = {map[comp], i};
    return ans;
}

void display(vector<int> arr){
    cout<<"{";
    for (int i = 0; i < arr.size(); i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<"}\n";
    
}

int main()
{
    vector<int> nums = {2,7,11,15};
    int target = 9;
    display(twoSum(nums, target));

    return 0;
}