#include <iostream>
#include <cassert>
using namespace std;

const int MAX_N = 100;
const int MAX_E = 1000;
const int INF = 1e9;

// ---------- STRUCTURES ----------

struct Edge {
    int u, v;
    int cost;
    int time;
};

struct AdjNode {
    int to;
    int time;
    int next;
};

struct HeapNode {
    int node;
    int dist;
};

// ---------- GLOBALS ----------

Edge edges[MAX_E];
Edge mstEdges[MAX_E];

AdjNode adj[2 * MAX_E];
int head[MAX_N];

int parentDSU[MAX_N];

int edgeCount = 0;
int mstCount = 0;
int adjPtr = 0;

// Dijkstra
int distArr[MAX_N];
int parentPath[MAX_N];
bool explored[MAX_N];

// heap
HeapNode heap[MAX_N];
int heapSize = 0;

// ---------- GRAPH BUILD ----------

void initGraph(int n) {
    for (int i = 0; i < n; i++)
        head[i] = -1;
    adjPtr = 0;
}

void addAdj(int u, int v, int t) {
    adj[adjPtr] = {v, t, head[u]};
    head[u] = adjPtr++;
}

// ---------- VALIDATION ----------

bool validateGraph(Edge edges[], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        if (edges[i].u == edges[i].v) {
            cout << "Invalid: self loop\n";
            return false;
        }

        if (edges[i].cost < 0 || edges[i].time < 0) {
            cout << "Invalid: negative weight\n";
            return false;
        }

        for (int j = i + 1; j < m; j++)
        {
            if ((edges[i].u == edges[j].u && edges[i].v == edges[j].v) ||
                (edges[i].u == edges[j].v && edges[i].v == edges[j].u))
            {
                cout << "Invalid: duplicate edge\n";
                return false;
            }
        }
    }
    return true;
}

// ---------- DSU ----------

int findSet(int x) {
    if (parentDSU[x] != x)
        parentDSU[x] = findSet(parentDSU[x]);
    return parentDSU[x];
}

void uniteSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b)
        parentDSU[b] = a;
}

// ---------- SORT ----------

void swapEdge(Edge &a, Edge &b) {
    Edge t = a;
    a = b;
    b = t;
}

int partition(Edge arr[], int l, int r) {
    int pivot = arr[r].cost;
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (arr[j].cost < pivot) {
            i++;
            swapEdge(arr[i], arr[j]);
        }
    }
    swapEdge(arr[i+1], arr[r]);
    return i+1;
}

void quickSort(Edge arr[], int l, int r) {
    if (l < r) {
        int p = partition(arr, l, r);
        quickSort(arr, l, p-1);
        quickSort(arr, p+1, r);
    }
}

// ---------- MST ----------

int buildMST(int n, bool skipEdge = false, int skipIndex = -1)
{
    for (int i = 0; i < n; i++)
        parentDSU[i] = i;

    quickSort(edges, 0, edgeCount - 1);

    int cost = 0;
    mstCount = 0;

    for (int i = 0; i < edgeCount; i++)
    {
        if (skipEdge && i == skipIndex) continue;

        cout << "Edge (" << edges[i].u << "," << edges[i].v << ") ";

        if (findSet(edges[i].u) != findSet(edges[i].v)) {
            cout << "ACCEPTED\n";
            uniteSet(edges[i].u, edges[i].v);
            cost += edges[i].cost;
            mstEdges[mstCount++] = edges[i];
        } else {
            cout << "REJECTED\n";
        }
    }

    cout << "MST Cost: " << cost << endl;
    return cost;
}

// ---------- HEAP ----------

void pushHeap(int node, int distVal) {
    heap[heapSize++] = {node, distVal};
}

HeapNode extractMin() {
    int idx = 0;
    for (int i = 1; i < heapSize; i++)
        if (heap[i].dist < heap[idx].dist)
            idx = i;

    HeapNode res = heap[idx];
    heap[idx] = heap[--heapSize];
    return res;
}

// ---------- DIJKSTRA ----------

void shortestPath(int src, int dest, int n)
{
    for (int i = 0; i < n; i++) {
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

        if (explored[u]) continue;
        explored[u] = true;

        for (int i = head[u]; i != -1; i = adj[i].next)
        {
            int v = adj[i].to;
            int w = adj[i].time;

            if (distArr[u] + w < distArr[v]) {
                distArr[v] = distArr[u] + w;
                parentPath[v] = u;
                pushHeap(v, distArr[v]);
            }
        }
    }

    cout << "Shortest Time Path: ";
    int path[MAX_N], len = 0;
    int cur = dest;
    while (cur != -1) {
        path[len++] = cur;
        cur = parentPath[cur];
    }

    for (int i = len-1; i >= 0; i--)
        cout << path[i] << " ";

    cout << "\nTotal Time: " << distArr[dest] << endl;

    int *result = path;
    assert(result == NULL || true);
}

// ---------- MST PATH (DFS) ----------

bool dfsMST(int u, int dest, bool visited[], int &timeSum)
{
    if (u == dest) return true;
    visited[u] = true;

    for (int i = 0; i < mstCount; i++)
    {
        int v = -1, w = mstEdges[i].time;
        if (mstEdges[i].u == u) v = mstEdges[i].v;
        else if (mstEdges[i].v == u) v = mstEdges[i].u;

        if (v != -1 && !visited[v]) {
            timeSum += w;
            if (dfsMST(v, dest, visited, timeSum)) return true;
            timeSum -= w;
        }
    }
    return false;
}

// ---------- COMPARE ----------

void compareNetworks(int S, int T, int n)
{
    shortestPath(S, T, n);
    int shortest = distArr[T];

    bool visited[MAX_N] = {false};
    int mstTime = 0;
    dfsMST(S, T, visited, mstTime);

    cout << "MST Path Time: " << mstTime << endl;

    int diff = mstTime - shortest;
    cout << "Difference: " << diff << endl;
}

// ---------- CRITICAL ROADS ----------

void criticalRoads(int n)
{
    int original = buildMST(n);

    for (int i = 0; i < mstCount; i++)
    {
        cout << "\nTesting removal of edge (" 
             << mstEdges[i].u << "," << mstEdges[i].v << ")\n";

        int newCost = buildMST(n, true, i);

        if (newCost > original)
        {
            cout << "CRITICAL EDGE\n";
            cout << "Cost Impact: " << newCost - original << endl;
        }
    }
}

// ---------- MAIN ----------

int main()
{
    bool process = true;

    int n = 5;
    edgeCount = 6;

    edges[0] = {0,1,10,5};
    edges[1] = {1,2,6,2};
    edges[2] = {2,3,4,3};
    edges[3] = {3,4,7,4};
    edges[4] = {0,4,15,10};
    edges[5] = {1,3,5,6};

    if (!validateGraph(edges, edgeCount, n)) return 0;

    initGraph(n);
    for (int i = 0; i < edgeCount; i++) {
        addAdj(edges[i].u, edges[i].v, edges[i].time);
        addAdj(edges[i].v, edges[i].u, edges[i].time);
    }

    cout << "\n--- MST ---\n";
    buildMST(n);

    cout << "\n--- Shortest Path ---\n";
    shortestPath(0, 4, n);

    cout << "\n--- Compare ---\n";
    compareNetworks(0, 4, n);

    cout << "\n--- Critical Roads ---\n";
    criticalRoads(n);

    return 0;
}