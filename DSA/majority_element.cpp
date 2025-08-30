#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// To find the majority element in a given unsorted array (The element which appears more than size/2 times in the array), Majority element, if exists, is unique!

// Optimised than Brute Force, using Sorting (O(n lg n))
int majority_element(vector<int> &arr)
{
    sort(arr.begin(), arr.end());

    int key = arr[0], frequency = 1;

    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] == arr[i - 1])
            frequency++;
        else
        {
            frequency = 1;
            key = arr[i];
        }

        if (frequency > (arr.size()) / 2)
            return key;
    }

    return -1;
}

// The most optimised Algorithm *Moore's Voting Algorithm (O(n))
int majority_element_moore(vector<int> &arr)
{
    int key = 0, frequency = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        if (frequency == 0)
            key = arr[i];

        if (key == arr[i])
            frequency++;
        else
            frequency--;
    }

    int count = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == key)
            count++;
    }

    if (count > arr.size() / 2)
        return key;
    return -1;
}

int main()
{
    vector<int> arr = {1, 2, 2, 1, 1, 2};
    int maj_elem = majority_element_moore(arr);
    cout << "Majority element is " << maj_elem << endl;

    return 0;
}