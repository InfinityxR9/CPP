#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAXN = 1000;

struct Request
{
    int id;
    int priority;
    int timestamp;
};

Request heap[MAXN];
int pos[MAXN];
int heapSize = 0;

void swapReq(Request &a, Request &b)
{
    Request t = a;
    a = b;
    b = t;
}

bool validateInput(Request arr[], int n)
{
    bool seen[MAXN] = {0};

    for (int i = 0; i < n; i++)
    {
        if (arr[i].priority < 0 || arr[i].priority > 100)
        {
            cout << "Invalid priority\n";
            return false;
        }

        if (arr[i].id < 0)
        {
            cout << "Invalid ID\n";
            return false;
        }

        if (seen[arr[i].id])
        {
            cout << "Duplicate ID detected\n";
            return false;
        }

        seen[arr[i].id] = 1;
    }

    return true;
}

void heapifyUp(int i)
{
    while (i > 0)
    {
        int p = (i - 1) / 2;

        if (heap[p].priority >= heap[i].priority)
            break;

        cout << "Swap " << heap[p].id << " and " << heap[i].id << endl;
        pos[heap[p].id] = i;
        pos[heap[i].id] = p;
        swapReq(heap[p], heap[i]);
        i = p;
    }
}

void heapifyDown(int i)
{
    while (true)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;

        if (l < heapSize && heap[l].priority > heap[largest].priority)
            largest = l;

        if (r < heapSize && heap[r].priority > heap[largest].priority)
            largest = r;

        if (largest == i)
            break;

        cout << "Swap " << heap[i].id << " and " << heap[largest].id << endl;
        pos[heap[i].id] = largest;
        pos[heap[largest].id] = i;

        swapReq(heap[i], heap[largest]);
        i = largest;
    }
}

void buildStructure(Request arr[], int n)
{
    heapSize = n;
    for (int i = 0; i < n; i++)
    {
        heap[i] = arr[i];
        pos[arr[i].id] = i;
    }

    cout << "Building Max Heap\n";
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyDown(i);
}

void printHeap()
{
    cout << "Heap state (ID, PRIORITY):\n";
    for (int i = 0; i < heapSize; i++)
        cout << "[" << heap[i].id << "," << heap[i].priority << "] ";

    cout << endl;
}

Request dispatchNext()
{
    Request top = heap[0];
    cout << "Dispatching ID: " << top.id << ", priority: " << top.priority << endl;

    heapSize--;
    if (heapSize > 0)
    {
        heap[0] = heap[heapSize];
        pos[top.id] = -1;
        heapifyDown(0);
    }

    printHeap();
    return top;
}

void updatePriority(int id, int newPriority)
{
    if (id < 0 || id >= MAXN)
    {
        cout << "Invalid ID\n";
        return;
    }

    int i = pos[id];
    if (i == -1)
    {
        cout << "Unknown ID\n";
        return;
    }

    int old = heap[i].priority;
    if (old == newPriority)
    {
        cout << "Old and new priorities are same. Nothing to update" << endl;
        return;
    }

    if (newPriority < 0 || newPriority > 100)
    {
        cout << "Invalid priority update\n";
        return;
    }

    heap[i].priority = newPriority;
    cout << "Updating ID " << id << ": " << old << " -> " << newPriority << endl;
    cout << "Current Heap State:" << endl;

    if (newPriority > old)
    {
        cout << "Moving upward\n";
        heapifyUp(i);
    }
    else if (newPriority < old)
    {
        cout << "Moving downward\n";
        heapifyDown(i);
    }
    printHeap();
}

bool lessThan(Request a, Request b, char key)
{
    if (key == 'p')
    {
        if (a.priority != b.priority)
            return a.priority < b.priority;

        return a.id < b.id;
    }

    if (a.timestamp != b.timestamp)
        return a.timestamp < b.timestamp;

    return a.id < b.id;
}

int partition(Request arr[], int l, int r, char key)
{
    int p = l + rand() % (r - l + 1);
    swapReq(arr[p], arr[r]);
    cout << "Pivot: " << arr[r].id << endl;

    int i = l - 1;
    for (int j = l; j < r; j++)
    {
        if (lessThan(arr[j], arr[r], key))
        {
            i++;
            swapReq(arr[i], arr[j]);
        }
    }

    swapReq(arr[i + 1], arr[r]);
    cout << "Partition boundaries: [" << l << "," << r << "]\n";

    return i + 1;
}

void sortRecords(Request arr[], int l, int r, char key)
{
    if (l < r)
    {
        int p = partition(arr, l, r, key);
        sortRecords(arr, l, p - 1, key);
        sortRecords(arr, p + 1, r, key);
    }
}

void printRecords(Request arr[], int n)
{
    cout << "Records (ID, PRIORITY, TIME):\n";
    for (int i = 0; i < n; i++)
    {
        cout << "(" << arr[i].id << "," << arr[i].priority << "," << arr[i].timestamp << ") ";
    }
    cout << endl;
}

void topKRequests(int k)
{
    if (k > heapSize)
        k = heapSize;

    Request backup[MAXN];
    int oldSize = heapSize;

    for (int i = 0; i < heapSize; i++)
        backup[i] = heap[i];

    cout << "Top " << k << " requests:\n";
    for (int i = 0; i < k; i++)
    {
        Request x = dispatchNext();
        cout << "ID: " << x.id << ", Priority: " << x.priority << endl;
    }

    heapSize = oldSize;
    for (int i = 0; i < oldSize; i++)
    {
        heap[i] = backup[i];
        pos[heap[i].id] = i;
    }
}

int main()
{
    srand(time(0));

    for (int i = 0; i < MAXN; i++)
        pos[i] = -1;

    cout << "\nTEST CASE 1\n";
    Request A[7] = {{10, 55, 7}, {11, 80, 2}, {12, 35, 5}, {13, 90, 1}, {14, 60, 4}, {15, 50, 8}, {16, 70, 3}};

    if (validateInput(A, 7))
    {
        buildStructure(A, 7);
        printHeap();
        cout << "\nDispatch Next\n";
        dispatchNext();
        cout << "\nIncrease Priority\n";
        updatePriority(12, 95);
        cout << "\nDecrease Priority\n";
        updatePriority(14, 20);
        cout << "\nTop K Requests\n";
        topKRequests(3);

        cout << "\nSort By Priority\n";
        Request P[7];
        for (int i = 0; i < 7; i++)
            P[i] = A[i];

        sortRecords(P, 0, 6, 'p');
        printRecords(P, 7);

        cout << "\nSort By Timestamp\n";
        Request T[7];
        for (int i = 0; i < 7; i++)
            T[i] = A[i];
        sortRecords(T, 0, 6, 't');
        printRecords(T, 7);
    }

    cout << "\n-------\nTEST CASE 2\n";

    Request B[8] = {{21, 40, 9}, {22, 65, 4}, {23, 85, 1}, {24, 30, 8}, {25, 75, 3}, {26, 50, 7}, {27, 95, 2}, {28, 60, 6}};

    for (int i = 0; i < MAXN; i++)
        pos[i] = -1;

    if (validateInput(B, 8))
    {
        buildStructure(B, 8);
        printHeap();
        cout << "\nDispatch Two Requests\n";
        dispatchNext();
        dispatchNext();
        cout << "\nPriority Update\n";
        updatePriority(24, 88);
        cout << "\nTop 4 Requests\n";
        topKRequests(4);
        cout << "\nSort By Priority\n";
        Request P2[8];

        for (int i = 0; i < 8; i++)
            P2[i] = B[i];

        sortRecords(P2, 0, 7, 'p');
        printRecords(P2, 8);

        cout << "\nSort By Timestamp\n";
        Request T2[8];
        for (int i = 0; i < 8; i++)
            T2[i] = B[i];
        sortRecords(T2, 0, 7, 't');
        printRecords(T2, 8);
    }

    return 0;
}