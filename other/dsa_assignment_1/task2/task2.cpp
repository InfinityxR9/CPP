#include <iostream>

using namespace std;

/**
 * Standard Variables and Constants Declaration
 */

#define MAX 200
int M, N;
int matrix[MAX][MAX];
bool isVisited[MAX][MAX];

/**
 * Define the pixel class as a point in 2D matrix
 * @param r Row index
 * @param c Column index
 */
struct Point
{
    int r;
    int c;

public:
    Point() {};
    Point(int r_, int c_) : r(r_), c(c_) {};
};

/**
 * Define Stack ADT Class
 */
class Stack
{
    Point arr[MAX * MAX];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    void push(Point key)
    {
        arr[++top] = key;
    }

    Point pop()
    {
        return arr[top--];
    }

    bool isEmpty()
    {
        return (top == -1);
    }
};

/**
 * The Linked List representation of Sparse matrix
 *
 * @param r Row index value
 * @param c Column index value
 * @param val Pixel value (only non-zero)
 * @param next Pointer to next node of LL
 */
struct Node
{
    int r;
    int c;
    int val;
    Node *next;
};

// the head pointer for the LL (maintanted as global pointer)
Node *head = nullptr;

/**
 * Object in 2D image `matrix`
 * @param area Total pixels in that object
 * @param b_count Total boundary pixels
 * @param b_pix Array of boundary pixels (In worse case, it can go upto `MAX*MAX` size)
 */
struct Object
{
    int area;
    int b_count;
    Point b_pix[MAX * MAX];
};

/**
 * Insertion at head operation in LL
 * @param r Row value
 * @param c Column value
 * @param val non-zero Pixel value
 */
void insert(int r, int c, int val)
{
    Node *newN = new Node;
    newN->r = r;
    newN->c = c;
    newN->val = val;
    newN->next = head;
    head = newN;
}

/**
 * Utility function to free up all nodes of LL at last (avoid memory leaks)
 */
void free_LL()
{
    Node *temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
}

/**
 * Utility function to check if a point is a valid point in the 2D Image matrix
 * @param r Row index
 * @param c Column index
 * @return `true` or `false` value indicating whether the input indices form a valid point in 2D image `matrix` as (r, c)
 */
bool isValid(int r, int c)
{
    return (r >= 0 && r < M && c >= 0 && c < N);
}

/**
 * Function to construct the LL representation of global sparse `matrix`
 */
void construct()
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matrix[i][j] == 1)
            {
                insert(i, j, matrix[i][j]);
            }
        }
    }
}

/**
 * Core Algorithm to get the Object around the input point
 * @param start_r Row index of the initial `point`
 * @param start_c Column index of the initial `point`
 * @return The `object` identified around the input Point
 */
Object detect_obj(int start_r, int start_c)
{
    Stack st;

    st.push(Point(start_r, start_c));
    isVisited[start_r][start_c] = true;

    Object obj;
    obj.area = 0;
    obj.b_count = 0;

    int x[4] = {-1, 1, 0, 0};
    int y[4] = {0, 0, 1, -1};

    while (!st.isEmpty())
    {
        Point p = st.pop();
        int r = p.r;
        int c = p.c;

        obj.area++;
        bool bound = false;

        for (int i = 0; i < 4; i++)
        {
            int new_r = r + x[i];
            int new_c = c + y[i];

            /**
             * The pixel point (r, c) is a boundary point if any of the 4 directions are either:
             * * Invalid point on 2D matrix
             * OR
             * * is a background point
             */

            if (!isValid(new_r, new_c) || matrix[new_r][new_c] == 0)
            {
                bound = true;
            }

            else if (!isVisited[new_r][new_c])
            {
                isVisited[new_r][new_c] = true;
                st.push(Point(new_r, new_c));
            }
        }

        if (bound)
        {
            obj.b_pix[obj.b_count++] = Point(r, c);
        }
    }

    return obj;
}

void display()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << "(" << temp->r << ", " << temp->c << ", " << temp->val << ")" << " ";
        temp = temp->next;
    }

    cout << endl;
}

int main()
{
    // Taking the 2D matrix from input file
    cin >> M >> N;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            isVisited[i][j] = false;
        }
    }

    // Construct the LL representation
    construct();

    /** Algorithm Logic:
     * Traverse along the LL, as it contains only the foreground points, identify the objects around these points
     * Store the detected objects in an Object array, which, in worst case can have M*N size
     */
    Object *objs = new Object[M * N];
    int objs_count = 0;

    Node *temp = head;
    while (temp != nullptr)
    {
        if (!isVisited[temp->r][temp->c])
        {
            objs[objs_count++] = detect_obj(temp->r, temp->c);
        }
        temp = temp->next;
    }

    // Showing asked outputs
    // original Sparse LL
    cout << "Showing the original sparse LL" << endl;
    display();

    // Total objects detected and area of each object
    cout << "Total connected components detected: " << objs_count << endl;
    for (int i = 0; i < objs_count; i++)
    {
        cout << "Area of Obj " << (i + 1) << ": " << objs[i].area << endl;
    }

    // Boundary pixels of each detected object
    for (int i = 0; i < objs_count; i++)
    {
        cout << "Boundary pixels for object " << (i + 1) << ":" << endl;

        for (int j = 0; j < objs[i].b_count; j++)
        {
            cout << "(" << objs[i].b_pix[j].r << ", " << objs[i].b_pix[j].c << ") ";
        }
        cout << endl;
    }

    // To flip the background and foreground pixels
    /**
     * Inintialise a boolean matrix representing true (1) for foreground points
     * Free old sparse matrix and create a new one with the flipped structure, containing new Foregrouned points
     * Reconstruct the matrix using this new sparse LL
     *
     * @note since we are flipping every possible element in the matrix, we can't do asymptotically better than O(M*N)
     */
    int m[MAX][MAX] = {0};
    temp = head;
    while (temp != nullptr)
    {
        m[temp->r][temp->c] = 1;
        temp = temp->next;
    }
    free_LL();
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!m[i][j])
            {
                insert(i, j, 1);
            }
        }
    }

    // Reconstruct matrix using the new sparse LL
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = 0;
        }
    }
    temp = head;
    while (temp != nullptr)
    {
        matrix[temp->r][temp->c] = 1;
        temp = temp->next;
    }

    // print final reconstructed matrix
    cout << "Printing the final reconstructed image matrix:" << endl;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // updated Sparse LL after Operations
    cout << "Showing the new sparse LL (after operations)" << endl;
    display();

    delete[] objs;
    objs = nullptr;
    free_LL();

    return 0;
}