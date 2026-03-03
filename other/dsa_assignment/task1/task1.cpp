#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

/**
 * Standard Variables and Constants Declaration
 * For the classification purpose, we will assume any pixel = 0 is the background canvas
 */

// Define `MAX` to be maximum possible 2D matrix size
#define MAX 200

// Define `M, N` as row and column variables
int M, N;

// Define the 2D `matrix` representing the image
int matrix[MAX][MAX];

// Define `isVisited` boolean matrix, marking whether each pixel `[i][j]` is visited or not for region expansion
bool isVisited[MAX][MAX];

// Define threshold limit `(T)` for grouping the pixels as region
int T = 5;

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
    // Constructor
    Stack()
    {
        top = -1;
    }

    // Push operation
    void push(Point key)
    {
        arr[++top] = key;
    }

    // Pop operation
    Point pop()
    {
        return arr[top--];
    }

    // Checking for stack to be empty
    bool isEmpty()
    {
        return (top == -1);
    }
};

/**
 * Image Region as a ADT
 * @param area The pixel count of region
 * @param min_r Minimum row index
 * @param max_r Maximum row index
 * @param min_c Minimum column index
 * @param max_c Maximum column index
 * @param sum_r Sum of all `row` indices
 * @param sum_c Sum of all `column` indices
 * @param pixels Collection of all the points in this region
 */
struct Region
{
    int area;
    int min_r;
    int max_r;
    int min_c;
    int max_c;

    double sum_r;
    double sum_c;

    Point pixels[MAX * MAX];
};

/**
 * Utility function to check if a point is a valid point in the 2D Image matrix
 * @param r Row index
 * @param c Column index
 * @return `true` or `false` value indicating whether the input indices form a valid point in 2D image `matrix`
 */
bool isValid(int r, int c)
{
    return (r >= 0 && r < M && c >= 0 && c < N);
}

/**
 * Core Algorithm to get the region expanded by the input point
 * @param start_r Row index of the point around which the region is to be expanded
 * @param start_c Column index of the point around which the region is to be expanded
 * @return The expanded Region around the input Point, such that each point in the region is under a threshold value (`T`) around the input point
 */
Region expandRegion(int start_r, int start_c)
{
    Stack st;
    Region region;

    region.area = region.sum_r = region.sum_c = 0;
    region.max_c = region.min_c = start_c;
    region.min_r = region.max_r = start_r;

    st.push(Point(start_r, start_c));
    isVisited[start_r][start_c] = true;

    // the four directions for region expansion (x, y)
    int x[4] = {-1, 1, 0, 0};
    int y[4] = {0, 0, 1, -1};
    
    while (!st.isEmpty())
    {
        Point p = st.pop();

        int r = p.r;
        int c = p.c;

        // Updating Region statistics
        region.pixels[region.area++] = p;
        region.sum_r += r;
        region.sum_c += c;

        region.min_r = min(r, region.min_r);
        region.min_c = min(c, region.min_c);
        region.max_c = max(c, region.max_c);
        region.max_r = max(r, region.max_r);


        for (int i = 0; i < 4; i++)
        {
            int new_r = r + x[i];
            int new_c = c + y[i];

            /**
             * Region Expansion along this point occurs if all the following conditions are met:
                * This is a valid point on image matrix
                * This point is not already visited
                ** The pixel value at this point is under the tolerance with current point intensity (Using current intensity instead of fixed seed intensity to include the gradient points)
             */

            if (isValid(new_r, new_c) && !isVisited[new_r][new_c] && abs(matrix[new_r][new_c] - matrix[r][c]) <= T)
            {
                // Mark the point as visited and push into stack for region expansion
                isVisited[new_r][new_c] = true;
                st.push(Point(new_r, new_c));
            }
        }
    }

    return region;
}

/**
 * Classification logic for Rectangular Region
 * @note The region is rectangular if the `fillRatio/density` is nearly `0.95` suggesting that the region marked by these rectangular boundaries are `95%` filled
 * @param region The Region to be classified as Rectangular
 * @returns `true` if the Region `region` is rectangular, otherwise `false`
 */
bool isRectangle(const Region &region)
{
    int width = region.max_c - region.min_c + 1;
    int height = region.max_r - region.min_r + 1;
    int boxArea = width * height;

    // density ratio
    double fillRatio = (double)region.area / boxArea;

    // Rectangle must be almost fully filled
    if (fillRatio >= 0.95)
        return true;

    return false;
}

/**
 * Classification logic for Circular Region
 *
 * @param region The Region to be classified as Circular
 * @returns `true` if the Region `region` is circular, otherwise `false`
 */
bool isCircular(const Region &region)
{
    int width = region.max_c - region.min_c + 1;
    int height = region.max_r - region.min_r + 1;

    // the boundaries should be square-like for the region to be near circlular
    if (abs(width - height) > 0.1 * max(width, height))
        return false;

    int boxArea = width * height;
    double fillRatio = (double)region.area / boxArea;

    // Circle expected = 0.785 ((pi*r*r)/(4*r*r))
    // fillRatio greater than 90% will suggest that the region is more rectangular than circular 
    return (fillRatio > 0.65 && fillRatio < 0.90);
}

/**
 * Show the rectangular boundary for the Region `region` by maximising the intensity of the boundary pixels
 * @param region The region of which boundary is to be shown
 */
void show_boundary(Region &region)
{
    for (int r = region.min_r; r <= region.max_r; r++)
    {
        matrix[r][region.min_c] = 255;
        matrix[r][region.max_c] = 255;
    }

    for (int c = region.min_c; c <= region.max_c; c++)
    {
        matrix[region.min_r][c] = 255;
        matrix[region.max_r][c] = 255;
    }
}

/**
 * Function to call the detection classification logic on the 2D Image Matrix
 */
void run_detection()
{
    // Taking the 2D matrix from input file
    cin >> M >> N;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            cin >> matrix[i][j];

    // Initialise the isVisited matrix as a false boolean matrix
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
        {
            if (matrix[i][j] == 0)
            {
                // marking canvas points as true so that they don't interfere in the classification
                isVisited[i][j] = true;
                continue;
            }
            isVisited[i][j] = false;
        }

    // For each unvisited non-canvas point in the 2D matrix, expand the region for that point
    // and classify the region as rectangular or circular

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!isVisited[i][j] && matrix[i][j] > 0)
            {
                Region region = expandRegion(i, j);

                // If the expanded region is too small, it is probably noise, so ignore it
                if (region.area >= 0.01 * (M * N))
                {
                    if (isCircular(region))
                    {
                        cout << "Region is Circular" << endl;
                        show_boundary(region);
                    }
                    else if (isRectangle(region))
                    {
                        cout << "Region is Rectangular" << endl;
                        show_boundary(region);
                    }
                }
            }
        }
    }

    // showing the final modified matrix
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--------------------------" << endl;
}

/**
 * Utility function to display the modified 2D Image Matrix as a Heatmap
 */
void print_visual_image()
{

    cout << "Visual Representation:" << endl;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {

            int val = matrix[i][j];
            char pixel;

            if (val <= 30)
                pixel = ' ';
            else if (val <= 60)
                pixel = '.';
            else if (val <= 100)
                pixel = ':';
            else if (val <= 150)
                pixel = '*';
            else if (val <= 200)
                pixel = 'O';
            else
                pixel = '#';

            cout << pixel;
        }
        cout << endl;
    }

    cout << endl;
}

int main()
{
    // Calling the functions in right order 
    run_detection();
    print_visual_image();

    return 0;
}