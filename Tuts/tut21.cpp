#include <iostream>

using namespace std;

class Employee
{
private:
    int a, b, c;

public:
    int d, e;
    void setData(int a, int b, int c);
    void getData();
};

void Employee ::setData(int a, int b, int c)
{
    a = a;
    b = b;
    c = c;
}

int main()
{
    Employee aryan;
    aryan.setData(1, 2, 3);
    aryan.getData();
    
    
    return 0;
}