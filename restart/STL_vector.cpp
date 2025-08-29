#include <iostream>
#include <vector>

// Equivalent to ADT Arrays (Advanced)

/*
*How vectors in C++ STL work?

First, an empty vector is created (if)
When first push_back, single element is inserted, the size goes to 1
if you try to push again. The size will go to 2 and insert
** Whenever, the vector is fulled and a push operation is executed, the size of the vector is doubled!
*/

using namespace std;

template <class T>
void print_arr(vector<T> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        // cout << v[i] << " ";
        cout << v.at(i) << " ";
    }

    cout << endl;
}

int main()
{
    vector<int> vec1;        // empty vector
    vector<char> vec2(4);    // character vector of 4 elements
    vector<char> vec3(vec2); // 4 element character vector from vec2
    vector<int> vec4(6, 3);  // 6 element vector of 3s
    print_arr(vec4);
    int ele, size;

    cout << "Enter the size of vector: ";
    cin >> size;

    for (int i = 0; i < size; i++)
    {
        cout << "Enter the element ";
        cin >> ele;
        vec1.push_back(ele);
    }

    print_arr(vec1);
    vector<int>::iterator iter = vec1.begin();
    iter = vec1.insert(iter, 2, 56); // inserts 56 2 times
    print_arr(vec1);

    // iter = vec1.erase(iter); // removes the element at given iterator
    // print_arr(vec1);
    // iter = vec1.erase(iter, iter + 3); // removes the element from given iterator to the given iterator (excluding the end iterator position)

    // Erase or clear methods only changes the size of the vector, not capacity
    print_arr(vec1);

    vector<int> vec5 = {4, 5, 6, 7, 69};
    vec5.push_back(56);
    for (int i : vec5)
    {
        cout << i << " ";
    }

    cout << "\nThe size of the vec5 is " << vec5.size() << endl;
    cout << "The capacity of the vec5 is " << vec5.capacity() << endl;
    cout<<"The end value of vec5 "<<*(vec5.end()-1)<<endl;  // *the end iterator points to the block next to the last block of vector (not the last block itself!)

    // rbegin : (reverse_iterator) point at the last element (incrementing it actually decreases over the vector)
    // rend : (reverse_iterator) point at the element preceeding the first element

    // To get the vector in reverse order
    for (vector<int>::reverse_iterator i = vec5.rbegin(); i != vec5.rend(); i++)
    {
        cout<<*i<<" ";
    }

    cout<<endl;
    
    // The auto keyword
    for (auto i = vec5.rbegin(); i != vec5.rend(); i++)
    {
        cout<<*i<<" ";
    }

    // print_arr(vec5);

    pair <int, int> p1 = {5,6};
    cout<<"first element "<<p1.first<<endl;
    cout<<"second element "<<p1.second<<endl;
    
    // A pair of pairs (or pair or T)
    pair <char, pair<char, int>> p2 = {'a', {'z', 69}};
    cout<<"first element "<<p2.first<<endl;
    cout<<"second element first "<<(p2.second).first<<endl;
    cout<<"second element second "<<(p2.second).second<<endl;

    // A vector of pairs
    vector<pair<int, int>> vec6 = {{1,2}, {4,5}, {6,7}, {8,9}};

    vec6.push_back({10,11});    // only inserts the given object
    vec6.emplace_back(12,13);   // creates in-place objects and insert
    // vec6.emplace_back({12,13});   // Error due to definition of vector

    for (pair<int, int> p:vec6) cout<<"{"<<p.first<<","<<p.second<<"}"<<endl;
    
    // using the auto keyword
    for (auto p:vec6) cout<<"{"<<p.first<<","<<p.second<<"}"<<endl;
    
    cout<<endl;

    return 0;
}