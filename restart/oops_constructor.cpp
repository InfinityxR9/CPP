#include <iostream>
#include <cmath>

using namespace std;

// Solution of finding displacement between two points in 2D cartesian coordinate system

class Point
{
    int _x_coordinate;
    int _y_coordinate;
    static int _points_count;

public:
    Point(int _x, int _y);
    void display_point();
    friend float get_distance(Point point_1, Point point_2);
    void get_details();
};

int Point::_points_count = 0;

Point::Point(int _x, int _y)
{
    _x_coordinate = _x;
    _y_coordinate = _y;

    cout << _points_count << endl;
    _points_count++;
}

void Point::display_point()
{
    cout << '(' << _x_coordinate << ',' << _y_coordinate << ')' << endl;
}

void Point::get_details()
{
    cout << "The x coordinate is " << _x_coordinate << endl;
    cout << "The y coordinate is " << _y_coordinate << endl;
    cout << "Total points initialsed so far " << _points_count << endl;
}

float get_distance(Point point_1, Point point_2)
{
    float distance = sqrt(pow(point_1._x_coordinate - point_2._x_coordinate, 2) + pow(point_1._y_coordinate - point_2._y_coordinate, 2));

    return distance;
}

int main()
{
    int p1_x, p1_y, p2_x, p2_y;
    cout << "Enter first point x coordinate: ";
    cin >> p1_x;
    cout << "Enter first point y coordinate: ";
    cin >> p1_y;

    cout << "Enter second point x coordinate: ";
    cin >> p2_x;
    cout << "Enter second point y coordinate: ";
    cin >> p2_y;

    Point p1(p1_x, p1_y);
    p1.display_point();
    p1.get_details();


    
    Point p2(p2_x, p2_y);

    p2.display_point();
    p2.get_details();

    cout << "The distance between first and second point is: " << get_distance(p1, p2);

    return 0;
}