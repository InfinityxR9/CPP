#include <iostream>
#include <string>

using namespace std;

// The Abstract Data-Type Stack based on LiFo Principle (Last in First out)
class Stack
{
    int top;
    char *arr;
    int size;

public:
    Stack(int arr_size)
    {
        size = arr_size;
        top = -1;
        arr = new char[size];
    }

    bool is_empty(void);
    bool is_full(void);
    char pop(void);
    void push(char);

    friend bool is_match(Stack &, char);

    ~Stack()
    {
        delete[] arr;
        arr = nullptr;
    }
};

bool Stack ::is_empty(void)
{
    if (top == -1)
        return true;
    return false;
}

bool Stack ::is_full(void)
{
    if (top == size - 1)
        return true;
    return false;
}

char Stack ::pop(void)
{
    if (!is_empty())
    {
        char val = arr[top--];
        return val;
    }

    cout << "Stack underflow" << endl;
    return '\0';
}

void Stack ::push(char element)
{
    if (!is_full())
    {
        arr[++top] = element;
    }

    else
    {
        cout << "Stack overflow" << endl;
    }
}

bool is_match(Stack &stack_obj, char str)
{
    if (!stack_obj.is_empty())
    {
        char top_val = stack_obj.arr[stack_obj.top];

        if (
            (str == ')' && top_val == '(') ||
            (str == ']' && top_val == '[') ||
            (str == '}' && top_val == '{') ||
            (str == '>' && top_val == '<'))
            return true;

        return false;
    }
    
    cout<<"Stack underflow" <<endl;
    return false;
}

int main()
{
    string str;
    cout << "Enter the bracket expression to be checked: ";
    cin >> str;

    int str_size = str.length();

    Stack str_stack = Stack(str_size);

    bool is_balanced = true;

    for (int i = 0; i < str_size; i++)
    {
        if (
            str[i] == '(' ||
            str[i] == '{' ||
            str[i] == '[' ||
            str[i] == '<')
            str_stack.push(str[i]);

        else if (
            str[i] == ')' ||
            str[i] == '}' ||
            str[i] == ']' ||
            str[i] == '>')
        {
            if (is_match(str_stack, str[i]))
            {
                str_stack.pop();
            }

            else
            {
                cout << "Unbalanced expression" << endl;
                is_balanced = false;
                break;
            }
        }
    }

    if (is_balanced)
    {
        if (str_stack.is_empty())
            cout << "Balanced expression" << endl;
        else
            cout << "Unbalanced expression" << endl;
    }

    return 0;
}