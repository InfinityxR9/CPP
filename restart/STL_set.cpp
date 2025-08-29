#include <iostream>
#include <set>

using namespace std;

// Set is just like a map, it has unique values sorting in a specific manner

// Set also uses a Self-Balancing Binary Tree, hence all the operations as insert, count, erase, find takes O(lg n)

// In the same manner, mutli_set and unordered_set also exist whose complexities are similar to maps equivalent

int main()
{
    set<int> s;

    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);

    cout << "The size of the set is " << s.size() << endl;
    
    // Duplicates not allowed
    s.insert(1);
    s.insert(2);
    s.insert(3);
    cout << "The size of the set is " << s.size() << endl;

    for (auto val : s)
        cout << val << " ";
    cout << endl;

    // lower_bound function gives the lowest upper bound (iterator) of a value which is present in the set (Not defined for unordered_set)
    cout<<"The lower bound of 3.5 is "<<*(s.lower_bound(3.5))<<endl;
    cout<<"The lower bound of 3 is "<<*(s.lower_bound(3))<<endl;   // 3 is present in the set

    return 0;
}