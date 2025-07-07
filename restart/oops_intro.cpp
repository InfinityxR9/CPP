#include <iostream>
#include <string>

using namespace std;

class Employee
{
private:
    string _name;
    int _salary;
    int _age;
    
    public:
    string company_name = "Infinity Limited";
    string evaluated_date = __DATE__;
    string evaluated_time = __TIME__;
    void get_data();
    void set_data(string name, int salary, int age);
    void get_public_details();
};

void Employee::get_data()
{
    cout << "Name: " << _name << endl;
    cout << "Salary: " << _salary << endl;
    cout << "Age: " << _age << endl;
}

void Employee::set_data(string name, int salary, int age)
{
    _name = name;
    _salary = salary;
    _age = age;
}

void Employee::get_public_details()
{
    cout << "Company: " << company_name << endl;
    cout << "Joining Date: " << evaluated_date << endl;
    cout << "Joining Time: " << evaluated_time << endl;
}

int main()
{
    Employee aryan;
    aryan.get_public_details();
    aryan.set_data("Aryan S", 959795, 19);
    aryan.get_data();

    return 0;
}