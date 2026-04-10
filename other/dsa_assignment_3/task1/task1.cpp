#include <iostream>
#include <string>
#include <queue>

using namespace std;

// Creates a leaf node
struct Node
{
    string fname;
    int fsize;

    Node *left;
    Node *right;
    int height;

    Node(string n, int s) : fname(n), fsize(s), height(1), left(nullptr), right(nullptr) {}
};

class FS
{
    bool isAllowed(char &c)
    {
        if (isalnum(c))
            return true;
        if (c == '_' || c == '.' || c == '-')
            return true;
        return false;
    }

    // alphbets (a-z, A-Z) < digits (0-9) < special characters (_, -, .)
    // by ascii ordering, - < . < _ AND a-z < A-Z
    int priority(char &c)
    {
        if (isalpha(c))
            return 1;
        if (isdigit(c))
            return 2;
        return 3;
    }

    // To check if the f2 file would be considered "higher" for ranking (f1<f2)
    bool comparator(string &f1, string &f2)
    {
        int n = min(f1.length(), f2.length());

        for (int i = 0; i < n; i++)
        {
            if (f1[i] == f2[i])
                continue;
            int p1 = priority(f1[i]);
            int p2 = priority(f2[i]);

            if (p1 != p2)
                return p1 < p2;
            return f1[i] < f2[i];
        }

        return f1.length() < f2.length();
    }

    Node *create(string name, int size)
    {
        return new Node(name, size);
    }

    int getBF(Node *root)
    {
        return (root->left ? root->left->height : 0) - (root->right ? root->right->height : 0);
    }

    Node *leftRotate(Node *root)
    {
        if (!root || !root->right)
            return root;

        Node *new_r = root->right;
        root->right = root->right->left;
        new_r->left = root;

        root->height = 1 + max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);

        new_r->height = 1 + max(new_r->left ? new_r->left->height : 0, new_r->right ? new_r->right->height : 0);

        return new_r;
    }

    Node *rightRotate(Node *root)
    {
        if (!root || !root->left)
            return root;

        Node *new_r = root->left;
        root->left = root->left->right;
        new_r->right = root;

        root->height = 1 + max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);

        new_r->height = 1 + max(new_r->left ? new_r->left->height : 0, new_r->right ? new_r->right->height : 0);

        return new_r;
    }

    Node *inorderPred(Node *root)
    {
        root = root->left;
        while (root && root->right)
        {
            root = root->right;
        }
        return root;
    }

    // Inserts a file with valid and unique file name
    Node *insertUtil(Node *root, string &name, int &size)
    {
        if (!root)
            return create(name, size);
        if (root->fname == name) {
            cout<<"File already exists"<<endl;
            return root;
        }
        else if (comparator(root->fname, name))
            root->right = insertUtil(root->right, name, size);
        else
            root->left = insertUtil(root->left, name, size);

        root->height = 1 + max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
        int bf = getBF(root);

        if (bf > 1 && !comparator(root->left->fname, name))
        {
            cout << "LL Rotation triggered at file name: " << root->fname << endl;
            return rightRotate(root);
        }
        if (bf < -1 && comparator(root->right->fname, name))
        {
            cout << "RR Rotation triggered at file name: " << root->fname << endl;
            return leftRotate(root);
        }
        if (bf > 1 && comparator(root->left->fname, name))
        {
            cout << "LR Rotation triggered at file name: " << root->fname << endl;
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (bf < -1 && !comparator(root->right->fname, name))
        {
            cout << "RL Rotation triggered at file name: " << root->fname << endl;
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

public:
    bool validateFilename(string &name)
    {
        int n = name.length();
        if (n == 0 || n >= 20)
        {
            cout << "Invalid filename length" << endl;
            return false;
        }
        if (name[0] == '_' || name[0] == '.' || name[0] == '-' || name[n - 1] == '_' || name[n - 1] == '.' || name[n - 1] == '-')
        {
            cout << "Invalid filename, starting or trailing special characters not allowed" << endl;
            return false;
        }

        for (int i = 0; i < n; i++)
        {
            if (!isAllowed(name[i]))
            {
                cout << "Invalid character present in filename" << endl;
                return false;
            }
            if (i > 0 && ((name[i] == '.' && name[i - 1] == '.') || (name[i] == '-' && name[i - 1] == '-') || (name[i] == '_' && name[i - 1] == '_')))
            {
                cout << "Invalid filename, Repeating special characters not allowed" << endl;
                return false;
            }
        }

        return true;
    }

    Node *search(Node *root, string &name)
    {
        if (!root || root->fname == name)
            return root;
        if (comparator(root->fname, name))
            return search(root->right, name);
        else
            return search(root->left, name);
    }

    Node *insert(Node *root, string &name, int &size)
    {
        if (!validateFilename(name))
        {
            return root;
        }

        cout << "Valid Filename" << endl;
        return insertUtil(root, name, size);
    }

    Node *delete_(Node *root, string &name)
    {
        if (!root)
        {
            cout << "Given file not present in the directory" << endl;
            return nullptr;
        }
        if (root->fname == name)
        {
            if (!root->left && !root->right)
            {
                delete root;
                root = nullptr;
                return root;
            }

            if (!root->left)
            {
                Node *temp = root->right;
                delete root;
                root = nullptr;
                return temp;
            }
            else if (!root->right)
            {
                Node *temp = root->left;
                delete root;
                root = nullptr;
                return temp;
            }

            Node *in_pre = inorderPred(root);
            root->fname = in_pre->fname;
            root->fsize = in_pre->fsize;
            root->left = delete_(root->left, in_pre->fname);
        }
        else if (comparator(root->fname, name))
        {
            root->right = delete_(root->right, name);
        }
        else
        {
            root->left = delete_(root->left, name);
        }

        if (!root)
            return root;

        root->height = 1 + max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
        int bf = getBF(root);

        if (bf > 1 && getBF(root->left) >= 0)
        {
            cout << "LL Rotation triggered at file name: " << root->fname << endl;
            return rightRotate(root);
        }
        if (bf < -1 && getBF(root->right) <= 0)
        {
            cout << "RR Rotation triggered at file name: " << root->fname << endl;
            return leftRotate(root);
        }
        if (bf > 1 && getBF(root->left) < 0)
        {
            cout << "LR Rotation triggered at file name: " << root->fname << endl;
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (bf < -1 && getBF(root->right) > 0)
        {
            cout << "RL Rotation triggered at file name: " << root->fname << endl;
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node *findMin(Node *root)
    {
        if (!root || !root->left)
            return root;
        while (root->left)
            root = root->left;
        return root;
    }

    Node *findMax(Node *root)
    {
        if (!root || !root->right)
            return root;
        while (root->right)
            root = root->right;
        return root;
    }

    void display(Node *root)
    {
        if (!root)
            return;
        display(root->left);
        cout << "File Name: " << root->fname << endl;
        cout << "File size: " << root->fsize << endl;
        int bf = getBF(root);
        cout << "BF: " << bf << "\n-----" << endl;
        display(root->right);
    }

    void levelorder(Node *root)
    {
        if (!root)
            return;
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int l = q.size();
            for (int i = 0; i < l; i++)
            {
                Node *n = q.front();
                q.pop();
                cout << n->fname << " " << n->fsize << " " << n->height << "| ";
                if (n->left)
                    q.push(n->left);
                if (n->right)
                    q.push(n->right);
            }
            cout << endl;
        }
    }

    void freeNodes(Node *root)
    {
        if (root)
        {
            freeNodes(root->left);
            freeNodes(root->right);
            delete root;
            root = nullptr;
        }
    }
};

int main()
{
    cout << "====== FILENAME POLICY ======" << endl;
    cout << "1. Only Alphanumeric characters and some special characters (-, ., _) are allowed" << endl;
    cout << "2. Max length of filename can be 20 characters" << endl;
    cout << "3. Empty filenames not allowed" << endl;
    cout << "4. Special Characters at start or end of filenames not allowed" << endl;
    cout << "5. Repeating special characters not allowed\n"
         << endl;

    cout << "====== ORDERING/COMPARATOR POLICY ======" << endl;
    cout << "1. Special Characters have highest priority" << endl;
    cout << "2. Digits have less priority than special characters, but greater than alphabets" << endl;
    cout << "3. Alphabets have least priority" << endl;
    cout << "4. If priority is same, then standard ASCII value is used for ordering, i.e, - < . < _ and a-z < A-Z" << endl;
    cout << "5. If still ties persist, longer filenames are given higher priority\n"
         << endl;

    FS fs;
    Node *root = nullptr;

    cout << "====== INSERTING FILES ======" << endl;
    
    string f1 = "fileA";
    int s1 = 120;
    string f2 = "fileB";
    int s2 = 80;
    string f3 = "fileC";
    int s3 = 200;
    string f4 = "fileD";
    int s4 = 50;
    string f5 = "fileE";
    int s5 = 90;
    
    root = fs.insert(root, f1, s1);
    root = fs.insert(root, f2, s2);
    root = fs.insert(root, f3, s3);
    root = fs.insert(root, f4, s4);
    root = fs.insert(root, f5, s5);

    cout << "\n====== INSERTING EXISTING FILE ======" << endl;
    string f6 = "fileC";
    int s6 = 160;
    root = fs.insert(root, f6, s6);

    cout << "\n====== TREE (INORDER + BF) ======" << endl;
    fs.display(root);
    fs.levelorder(root);

    cout << "\n====== SEARCH TEST ======" << endl;
    string key = "fileC";
    Node *found = fs.search(root, key);
    if (found)
        cout << "Found: " << found->fname << " Size: " << found->fsize << endl;
    else
        cout << "File not found\n";

    cout << "\n====== MIN / MAX ======" << endl;
    Node *minNode = fs.findMin(root);
    Node *maxNode = fs.findMax(root);

    if (minNode)
        cout << "Min File: " << minNode->fname << endl;
    if (maxNode)
        cout << "Max File: " << maxNode->fname << endl;

    cout << "\n====== DELETE OPERATIONS ======" << endl;

    string d1 = "fileD";
    root = fs.delete_(root, d1);

    cout << "\nAfter deleting fileD:\n";
    fs.display(root);

    string d2 = "fileA";
    root = fs.delete_(root, d2);

    cout << "\nAfter deleting fileA:\n";
    fs.display(root);
    fs.levelorder(root);

    cout << "\n====== INSERT INVALID FILE ======" << endl;
    string invalid = ".badFile";
    int s7 = 40;
    root = fs.insert(root, invalid, s7);

    cout << "\n====== FINAL TREE ======" << endl;
    fs.display(root);
    fs.levelorder(root);

    cout << "\n====== FREEING MEMORY ======" << endl;
    fs.freeNodes(root);
    root = nullptr;

    cout << "All nodes deleted successfully.\n"
         << endl;

    cout << "====== TIME AND SPACE COMPLEXITY ======" << endl;
    cout << "validateFilename(name): O(N), O(1) (N -> length of filename string)" << endl;
    cout << "insert(name, size): O(lg n), O(lg n) (n -> number of files in tree)" << endl;
    cout << "delete(name): O(lg n), O(lg n)" << endl;
    cout << "search(name): O(lg n), O(lg n)" << endl;
    cout << "findMin() / findMax(): O(lg n), O(1)" << endl;
    cout << "display(): O(n), O(lg n)" << endl;

    return 0;
}