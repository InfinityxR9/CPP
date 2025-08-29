#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

// Map is an associative array, equivalent to Dictionary/Objects
// *Map is executed as a Self-Balancing Tree, hence the operations like insert, erase, count take O(lg n)

// *Unordered Map (implemented as a hash table (open hashing)) takes only O(1) time for insert, erase, count operations (In super worst case, like mathematical collisioning, it might take O(n))

int main()
{
    map<string, int> marksMap; // string for key (*unique), int for value

    // *By default, map sorts the data in ascending order of keys*

    marksMap["Aryan"] = 99;
    marksMap["Adi"] = 108;
    marksMap["Jala"] = 88;
    marksMap["Jala"] = 88;

    marksMap.insert({{"PJ", 80}, {"HP", 97}});

    map<string, int>::iterator iter = marksMap.begin();
    for (iter; iter != marksMap.end(); iter++)
    {
        cout << iter->first << " " << iter->second << endl; // first to get key, second to get value
    }

    cout << "The size of the map is " << marksMap.size() << endl;
    cout << "The max_size of the map is " << marksMap.max_size() << endl;
    cout << "The empty return value of the map is " << marksMap.empty() << endl;

    // **count() returns the number of instances of occurrence of a key, since keys are unique in a map, it can only return 0 (not exist in map) or 1 (exist in map)
    cout << "count of jala (Does jala exist?) " << marksMap.count("Jala") << endl;

    // find() returns the iterator of the element if it is found, otherwise returns the end() iterator
    if (marksMap.find("RP") != marksMap.end()) cout<<"RP found in map!\n";
    else cout<<"RP not found in map!\n----\n";

    /* MultiMap */
    multimap<string, int> m;

    m.emplace("Aryan", 98);     // or insert()
    m.emplace("Adi", 107);
    m.emplace("Jala", 88);
    m.emplace("Aryan", 97);     // multimap supports duplicate keys, in sorting, stability is maintained
    m.emplace("PJ", 79);

    for (auto m0: m) cout<<m0.first<<" "<<m0.second<<endl;
    // m.erase("Aryan");       // deletes all keys of 'Aryan'
    // To delete only first occurence, use iterator
    m.erase(m.find("Aryan"));
    cout<<"-----"<<endl;
    for (auto m0: m) cout<<m0.first<<" "<<m0.second<<endl;
    cout<<"----\n";
    
    // An ***unordered_map*** (mostly used) is just like a map, except it doesn't do sorting and keeps the order of creation (random) (Needs to be included via header file) **(Stored as like a stack, the element inserted first is at the bottom)**
    
    unordered_map<string, int> um;
    um["Aryan"] = 99;
    um["Adi"] = 108;
    um["Jala"] = 88;
    for (auto m2: um) cout<<m2.first<<" "<<m2.second<<endl;

    return 0;
}