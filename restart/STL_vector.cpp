#include <iostream>
#include <vector>

// Equivalent to ADT Arrays (Advanced)

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
    vector<int> vec1;   // empty vector
    vector<char> vec2(4);   // character vector of 4 elements
    vector<char> vec3(vec2);    // 4 element character vector from vec2
    vector<int> vec4(6,3); // 6 element vector of 3s
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
    vector <int> :: iterator iter = vec1.begin();
    vec1.insert(iter, 2, 56);
    print_arr(vec1);

    return 0;
}