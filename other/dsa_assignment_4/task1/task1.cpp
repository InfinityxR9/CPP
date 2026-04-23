#include <iostream>
using namespace std;

const int MAX_N = 100;
const int MAX_E = 1000;
const int INF = 1e9;

struct Edge
{
    int u, v;
    int cost;
    int time;
};

struct AdjNode
{
    int to;
    int time;
    int next;
};

struct HeapNode
{
    int node;
    int dist;
};

Edge edges[MAX_E];
Edge mstEdges[MAX_E];

AdjNode adj[2 * MAX_E];

HeapNode heap[MAX_N];

int head[MAX_N];
int parentDSU[MAX_N];

int distArr[MAX_N];
int parentPath[MAX_N];
bool explored[MAX_N];

int heapSize = 0;

int m = 0;
int mstCount = 0;
int adjPtr = 0;

void initGraph(int n)
{
    for (int i = 0; i < n; i++)
        head[i] = -1;

    adjPtr = 0;
}

void addAdj(int u, int v, int t)
{
    adj[adjPtr] = {v, t, head[u]};
    head[u] = adjPtr++;
}

bool validateGraph(Edge edges[], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        if (edges[i].u < 0 || edges[i].u >= n ||
            edges[i].v < 0 || edges[i].v >= n)
        {
            cout << "Invalid node ID detected\n";
            return false;
        }

        if (edges[i].u == edges[i].v)
        {
            cout << "Invalid self-loop\n";
            return false;
        }

        if (edges[i].cost < 0 || edges[i].time < 0)
        {
            cout << "Negative weight invalid\n";
            return false;
        }

        for (int j = i + 1; j < m; j++)
        {
            if ((edges[i].u == edges[j].u && edges[i].v == edges[j].v) || (edges[i].u == edges[j].v && edges[i].v == edges[j].u))
            {
                cout << "Duplicate road detected\n";
                return false;
            }
        }
    }
    return true;
}

int findSet(int x)
{
    if (parentDSU[x] != x)
        parentDSU[x] = findSet(parentDSU[x]);

    return parentDSU[x];
}

void uniteSet(int a, int b)
{
    a = findSet(a);
    b = findSet(b);

    if (a != b)
        parentDSU[b] = a;
}

void swapEdge(Edge &a, Edge &b)
{
    Edge t = a;
    a = b;
    b = t;
}

int partition(Edge arr[], int l, int r)
{
    int pivot = arr[r].cost;
    int i = l - 1;

    for (int j = l; j < r; j++)
    {
        if (arr[j].cost < pivot)
        {
            i++;
            swapEdge(arr[i], arr[j]);
        }
    }

    swapEdge(arr[i + 1], arr[r]);
    return i + 1;
}

void quickSort(Edge arr[], int l, int r)
{
    if (l < r)
    {
        int p = partition(arr, l, r);
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1, r);
    }
}

int buildMST(int n, bool skipEdge = false, int skipU = -1, int skipV = -1)
{
    for (int i = 0; i < n; i++)
        parentDSU[i] = i;

    quickSort(edges, 0, m - 1);

    mstCount = 0;
    int totalCost = 0;
    cout << "Building MST" << endl;

    for (int i = 0; i < m; i++)
    {
        if (skipEdge)
        {
            if ((edges[i].u == skipU && edges[i].v == skipV) || (edges[i].u == skipV && edges[i].v == skipU))
                continue;
        }

        cout << "Considering (" << edges[i].u << "," << edges[i].v << ") ";

        if (findSet(edges[i].u) != findSet(edges[i].v))
        {
            cout << "ACCEPT\n";
            uniteSet(edges[i].u, edges[i].v);
            totalCost += edges[i].cost;
            mstEdges[mstCount++] = edges[i];
        }
        else
            cout << "REJECT\n";
    }

    if (mstCount != n - 1)
    {
        cout << "Graph disconnected. No MST." << endl;
        return INF;
    }

    cout << "MST Cost = " << totalCost << endl;
    return totalCost;
}

void swapHeap(HeapNode &a, HeapNode &b)
{
    HeapNode t = a;
    a = b;
    b = t;
}

void heapifyUp(int i)
{
    while (i > 0)
    {
        int p = (i - 1) / 2;
        if (heap[p].dist <= heap[i].dist)
            break;

        swapHeap(heap[p], heap[i]);
        i = p;
    }
}

void pushHeap(int node, int d)
{
    heap[heapSize] = {node, d};
    heapifyUp(heapSize);
    heapSize++;
}

void heapifyDown(int i)
{
    while (true)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;

        if (l < heapSize && heap[l].dist < heap[smallest].dist)
            smallest = l;

        if (r < heapSize && heap[r].dist < heap[smallest].dist)
            smallest = r;

        if (smallest == i)
            break;

        swapHeap(heap[i], heap[smallest]);
        i = smallest;
    }
}

HeapNode extractMin()
{
    HeapNode res = heap[0];
    heap[0] = heap[--heapSize];
    if (heapSize > 0)
        heapifyDown(0);

    return res;
}

int edgeTime(int a, int b)
{
    for (int i = 0; i < m; i++)
    {
        if ((edges[i].u == a && edges[i].v == b) || (edges[i].u == b && edges[i].v == a))
            return edges[i].time;
    }
    return -1;
}

void shortestPath(int src, int dest, int n)
{
    cout << "----\nFinding Shortest path" << endl;
    for (int i = 0; i < n; i++)
    {
        distArr[i] = INF;
        explored[i] = false;
        parentPath[i] = -1;
    }

    heapSize = 0;
    distArr[src] = 0;
    pushHeap(src, 0);

    while (heapSize > 0)
    {
        HeapNode cur = extractMin();
        int u = cur.node;

        if (explored[u])
            continue;

        explored[u] = true;
        for (int i = head[u]; i != -1; i = adj[i].next)
        {
            int v = adj[i].to;
            int w = adj[i].time;

            if (distArr[u] + w < distArr[v])
            {
                distArr[v] = distArr[u] + w;
                parentPath[v] = u;
                pushHeap(v, distArr[v]);
            }
        }
    }

    if (distArr[dest] == INF)
    {
        cout << "No path exists" << endl;
        return;
    }

    int path[MAX_N];
    int len = 0;
    int cur = dest;

    while (cur != -1)
    {
        path[len++] = cur;
        cur = parentPath[cur];
    }

    cout << "Path:" << endl;
    for (int i = len - 1; i > 0; i--)
    {
        int t = edgeTime(path[i], path[i - 1]);

        cout << path[i] << " -> " << path[i - 1] << " (" << t << ")\n";
    }

    cout << "Total Time = " << distArr[dest] << endl;
}

bool dfsMST(int u, int dest, bool visited[], int &timeSum)
{
    if (u == dest)
        return true;

    visited[u] = true;
    for (int i = 0; i < mstCount; i++)
    {
        int v = -1;
        int w = mstEdges[i].time;

        if (mstEdges[i].u == u)
            v = mstEdges[i].v;

        else if (mstEdges[i].v == u)
            v = mstEdges[i].u;

        if (v != -1 && !visited[v])
        {
            timeSum += w;
            if (dfsMST(v, dest, visited, timeSum))
                return true;

            timeSum -= w;
        }
    }

    return false;
}

void compareNetworks(int S, int T, int n)
{
    shortestPath(S, T, n);

    int shortest = distArr[T];
    bool visited[MAX_N] = {0};
    int mstTime = 0;

    dfsMST(S, T, visited, mstTime);

    cout << "MST path time = " << mstTime << endl;
    int diff = mstTime - shortest;
    double pct = 100.0 * diff / shortest;
    cout << "Slower by " << diff << " (" << pct << "%)" << endl;
}

void criticalRoads(int n)
{
    int original = buildMST(n);
    if (original == INF)
        return;

    for (int i = 0; i < mstCount; i++)
    {
        int u = mstEdges[i].u;
        int v = mstEdges[i].v;

        cout << "\nRemoving " << u << "-" << v << endl;

        int newCost = buildMST(n, true, u, v);

        if (newCost > original && newCost != INF)
        {
            cout << "CRITICAL ROAD between " << u << " and " << v << endl;
            cout << "Cost impact " << newCost - original << endl;
        }
    }
}

int main()
{
    cout << "\nTEST 1:" << endl;
    int n = 5;
    m = 7;
    edges[0] = {0, 1, 4, 3};
    edges[1] = {1, 2, 2, 1};
    edges[2] = {2, 3, 5, 4};
    edges[3] = {3, 4, 3, 2};
    edges[4] = {0, 4, 12, 8};
    edges[5] = {1, 3, 1, 6};
    edges[6] = {0, 2, 7, 5};

    if (validateGraph(edges, m, n))
    {
        initGraph(n);
        for (int i = 0; i < m; i++)
        {
            addAdj(edges[i].u, edges[i].v, edges[i].time);
            addAdj(edges[i].v, edges[i].u, edges[i].time);
        }

        buildMST(n);
        shortestPath(0, 4, n);
        compareNetworks(0, 4, n);
        criticalRoads(n);
    }

    cout << "\n------\nTEST 2:\n";
    n = 6;
    m = 8;
    edges[0] = {0, 1, 5, 2};
    edges[1] = {1, 2, 4, 2};
    edges[2] = {2, 5, 6, 2};
    edges[3] = {0, 3, 2, 6};
    edges[4] = {3, 4, 2, 5};
    edges[5] = {4, 5, 2, 5};
    edges[6] = {1, 4, 7, 3};
    edges[7] = {2, 4, 3, 1};

    if (validateGraph(edges, m, n))
    {
        initGraph(n);
        for (int i = 0; i < m; i++)
        {
            addAdj(edges[i].u, edges[i].v, edges[i].time);
            addAdj(edges[i].v, edges[i].u, edges[i].time);
        }
        buildMST(n);
        shortestPath(0, 5, n);
        compareNetworks(0, 5, n);
        criticalRoads(n);
    }

    return 0;
}