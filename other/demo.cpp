#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int num_test;
    cin >> num_test;
    while (num_test--)
    {
        int num_element;
        cin >> num_element;
        int array[num_element];
        bool ha_0 = false;
        bool ha_neg = false;
        for (int i = 0; i < num_element; i++)
        {
            int element;
            array[i] = element;
            if (element == 0)
                ha_0 = true;
            if (element < 0)
                ha_neg = true;
        }

        int min = array[0];
        for (int i = 0; i < num_element; i++)
        {
            if (min > array[i])
                min = array[i];
        }

        if (ha_neg && !ha_0)
        {
            for (int i = 0; i < num_element; i++)
            {
                array[i] = array[i] + min;
            }
        }
        else
        {
            for (int i = 0; i < num_element; i++)
            {
                array[i] = array[i] - min;
            }
        }
        int num = 0;
        while (true)
        {
            bool flag = false;
            for (int i = 0; i < num_element; i++)
            {
                if (array[i] == num)
                {
                    flag = true;
                    num++;
                    break;
                }
            }
            if (!flag)
            {
                cout << num << endl;
            }
            break;
        }
        return 0;
    }
}