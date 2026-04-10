#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

int sucessor(Node *root, int key)
{
    if (root != nullptr)
    {
        Node* asc = nullptr;
        while (root != nullptr && root->data != key)
        {
            if (root->data > key)
            { // left side
                asc = root->data;
                root = root->left;
            }
            else
            {
                root = root->right;
            }
        }
        if (root == nullptr)
            return -1;

        if (root->right == nullptr) return asc;

        root = root->right;
        while (root->left != nullptr) {
            root = root->left;
        }

        return root->data;
    }

    return -1;
}

int main()
{

    return 0;
}