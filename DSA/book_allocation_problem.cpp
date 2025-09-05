#include <iostream>
#include <vector>

using namespace std;

/*
Book Allocation Problem using Binary Search
*You have to allocate books to M students so that the maximum number of pages allocated to a student is minimum (Out of all possible distributions)

Constrains:
    *Each Book should be allocated to a student
    *Each Student has to be allocated atleast one book
    *Allotment should be based on contiguous manner

Example: [2,1,3,4] N = 2, M = 2     (Here, the elements is the number of pages)
Possible distributions:
    *[2], [1,3,4] => max(number of pages) = 8
    *[2,1], [3,4] => max(number of pages) = 7
    *[2,1,3], [4] => max(number of pages) = 6 (Minimum!)

    return -1 if no such arrangement is possible (eg: when m > n)

Approach using Binary Search:
    *Take the total pages (sum of array) and initialise a binary search on the possible solution values ranging from 0 to sum
    *We do search space selection on the basis of validity of the mid value.
    *If the mid value can be a valid possible answer of the problem, then search in the LEFT SPACE (to search for the minimum possible)
    *If the mid value is not possible as an answer of the problem, search in the RIGHT SPACE (to search for higher, possible answer)

    *We initialise a variable "answer" to keep track of the minimum answer and if the new possible mid value is smaller than the previous, we update the answer (or by simply using the min() function)

Check validity of an answer:    --> O(n)
    *We run a loop over the array, first assume that the number of students is 1, and we keep on giving the books to the student in the contiguous manner, and if the total pages get more than the proposed answer, we reset the value of pages and start giving the subsequent books to new student.
    *At last, if the number of students required for this allocation exceeds the number of students asked in the question (M), the proposed answer would be invalid, otherwise Valid.
    *We can also give a check in every iteration whether the individual pages of a book is less than the maximum allowed pages or not.

Time Complexity:    O(n * lg N) (n --> total books, N --> total pages)
Space Complexity:   O(1)
*/

bool isValid(vector<int> &arr, int m, int maxAllowed) // --> O(n)
{
    int student = 1, pages = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > maxAllowed)
            return false;

        if (pages + arr[i] <= maxAllowed)
            pages += arr[i];
        else
        {
            student++;
            pages = arr[i];
        }
    }

    return student > m ? false : true;
}

int allocateBooks(vector<int> &arr, int m) // --> O(n * lg N) (N -> sum/total pages)
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
    vector<int> arr = {15, 17, 20};
    int m = 2;

    cout << allocateBooks(arr, m) << endl;

    return 0;
}