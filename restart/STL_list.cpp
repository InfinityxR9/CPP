#include <iostream>
#include <list>

// Equivalent to Doubly Linked List (Advanced)

// Difference between Deque (Doubly Ended Queue) and List 
// Deque is implemented using Dynamic Arrays and hence Random access is faster

using namespace std;

void print_list(list<int> &lst)
{
    list<int>::iterator i;

    for (i = lst.begin(); i != lst.end(); i++)
    {
        cout << *i << " ";
    }

    cout << endl;
}

void insert_list (list<int> &lst) {
    list<int> ::iterator i = lst.begin();

    for (i; i != lst.end(); i++)
    {
        cout<<"Enter the value: ";
        cin>>*i;
    }    
}

int main()
{
    list<int> list1; // Initiliase an empty list
    list1.push_back(5);
    list1.push_back(7);
    list1.push_back(2);
    list1.push_back(8);
    list1.push_back(85);
    list1.push_back(3);

    /*list<int>::iterator iter = list1.begin(); // creates an iterator of list<int> type
    cout << *iter << " ";
    iter++;
    cout << *iter << " ";
    iter++;
    cout << *iter << " ";
    iter++;
    cout << *iter << " ";
    iter++;
    cout << *iter << " ";
    iter++;
    cout << *iter << " ";   // would print the first element
    cout << endl; */

    print_list(list1);

    list <int> list2(5); // Empty list of size 5
    insert_list(list2);

    // print_list(list2);
    // list2.pop_back();
    // print_list(list2);
    // list2.pop_front();
    // print_list(list2);
    // list2.remove(46);       // remove all occurences of 46
    print_list(list2);

    list2.sort();

    print_list(list2);

    cout<<"List 1 after merging with list 2"<<endl;
    list1.merge(list2);

    print_list(list1);
    list1.reverse();
    print_list(list1);

    return 0;
}