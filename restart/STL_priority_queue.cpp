#include <iostream>
#include <queue>

using namespace std;

// Priority Queue (in STL) is a stack like DS which automatically arranges the input elements on basis of their priority (value) as greatest element on the top. In (In implementation) it is based on a max heap or a min heap DS which is itself based on Complete Binary Trees DS

int main()
{
    // priority_queue<int> q;  // greatest element on top Priority Queue
    priority_queue<int, vector<int>, greater<int>> q;  // lowest element on top Priority Queue

    q.push(56);
    q.push(5);
    q.push(6);
    q.push(69);

    while (!q.empty())
    {
        cout << q.top() << " ";
        q.pop();
    }

    cout << endl;

    return 0;
}