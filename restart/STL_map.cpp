#include <iostream>
#include <map>
#include <string>

using namespace std;

// Map is an associative array, equivalent to Dictionary/Objects

int main()
{
    map<string, int> marksMap; // string for key, int for value
    marksMap["Aryan"] = 99;
    marksMap["Adi"] = 108;
    marksMap["Jala"] = 88;

    marksMap.insert({{"PJ", 80}, {"RP", 97}});

    map<string, int>::iterator iter = marksMap.begin();
    for (iter; iter != marksMap.end(); iter++)
    {
        cout << iter->first << " " << iter->second << endl; // first to get key, second to get value
    }

    cout << "The size of the map is " << marksMap.size() << endl;
    cout << "The max_size of the map is " << marksMap.max_size() << endl;
    cout << "The empty return value of the map is " << marksMap.empty() << endl;

    return 0;
}