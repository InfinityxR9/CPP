#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// The custom sort comparator
bool comparator(pair<int, int> p1, pair<int, int> p2)
{
    if (p2.second > p1.second)
        return true;
    if (p2.second < p1.second)
        return false;
    if (p2.first > p1.first)
        return true;
    else
        return false;
}

int main()
{
    vector<pair<int, int>> vec = {{3, 1}, {2, 1}, {7, 1}, {5, 2}};

    // sort(vec.begin(), vec.end());   // Sorts the vector (pair: comparison basis of first element of pair)

    for (auto i : vec)
        cout << i.first << " " << i.second << endl;

    cout << "----\n";

    sort(vec.begin(), vec.end(), greater()); // Sorts the vector (pair: comparison basis of first element of pair) in descending order

    for (auto i : vec)
        cout << i.first << " " << i.second << endl;

    cout << "----\n";

    // To create a custom sorting pattern for pairs, eg: sort on basis of second element and if they are equal check for first element
    sort(vec.begin(), vec.end(), comparator);

    for (auto i : vec)
        cout << i.first << " " << i.second << endl;

    return 0;
}