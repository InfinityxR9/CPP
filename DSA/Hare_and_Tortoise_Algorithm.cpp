#include <iostream>
#include <vector>

using namespace std;

/*
Hare and Tortoise Alogrithm is used to detect a cycle in Linked List.
It is also known as Slow and Fast Pointer Algorithm and Floyd's Cycle-Finding Algorithm.

Here we use two pointers, one "slow" and one "fast"

We initialise slow and fast pointers at the root/head node.
    *Slow pointer always increases (runs) with a pace of 1 node
    *Fast pointer increses (runs) with a pace of 2 nodes
    *We run them till slow and fast pointers are equal
    *Once, they are met, we reinitialise slow to root/head.
    *Now we run both the slow and fast pointers with a pace of 1 node.

The node at which the two pointers meet is the joint Node of the cycle.

Eg:  0 --> 3 --> 4 --> 2
           ^           |
           |<----------|

We initialise slow and fast pointers at 0. They both meet at node with value 2.
Reinitialise slow to head (Node with value 0), now increase both by 1. After single increment, both will meet again at 3, which is joint node.

This Algorithm is Mathematically proven and if a cycle exists in a Linked List, the two pointers are bound to meet, otherwise the fast pointer would eventually fall into the nullptr.

References:
    https://medium.com/@ekelman3/a-complete-mathematical-proof-of-floyds-cycle-finding-algorithm-f1ab765dc99a
    https://cp-algorithms.com/others/tortoise_and_hare.html

A common problem to demonstrate Hare and Tortoise Algorithm:

Find Duplicate Problem
Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and using only constant extra space.

Approach:
    *Imagine a Linked list as the index as the Node value and next node as the Node with value as the value at that index in array.
        *eg: [3, 1, 3, 4, 2] with index [0, 1, 2, 3, 4], the linked list would be 0 -> 3 -> 4 -> 2 --> to 3 again

    *In case of duplicates in the array, A cycle in linked list is bound to form and thus by using the slow and fast pointers, we can detect the duplicate element

Time Complexity:    O(n)
Space Complexity:   O(1)

Leetcode Reference: https://leetcode.com/problems/find-the-duplicate-number/description/
*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Classic Slow and Fast Pointers Algorithm
bool hasCycle(ListNode *head)
{
    if (head == NULL)
        return false;
    if (head->next == NULL)
        return false;

    ListNode *slow = head;
    ListNode *fast = head;

    do
    {
        slow = slow->next; // +1
        if (fast->next == NULL)
            return false;
        fast = (fast->next)->next; // +2
    } while (slow != fast && fast != NULL && slow != NULL);

    if (fast == NULL)
        return false;
    return true;
}

int findDuplicate(vector<int> &nums)
{
    int slow, fast;
    slow = fast = 0;

    do
    {
        slow = nums[slow];       // +1
        fast = nums[nums[fast]]; // +2
    } while (slow != fast);

    slow = 0;

    while (slow != fast)
    {
        slow = nums[slow]; // +1
        fast = nums[fast]; // +1
    }

    return slow;
}

int main()
{
    vector<int> nums = {1, 3, 4, 2, 2};
    cout << findDuplicate(nums) << endl;

    nums = {3, 1, 3, 4, 2};
    cout << findDuplicate(nums) << endl;

    nums = {3, 3, 3, 3, 3};
    cout << findDuplicate(nums) << endl;

    return 0;
}