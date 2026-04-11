#include <iostream>
#include <string>

using namespace std;

/**
 * File Node Structure
 * @param fname Name of file
 * @param fsize Size of file
 * @param left Pointer to left child
 * @param right Pointer to right child
 * @param height Height of the file node
 */
struct Node
{
    string fname;
    int fsize;

    Node *left;
    Node *right;
    int height;

    Node(string n, int s) : fname(n), fsize(s), height(1), left(nullptr), right(nullptr) {}
};

/**
 * File System Class, implemented as an AVL Tree
 */
class FS
{
    /**
     * Utility function is check if a character is allowed as per Filename Policy
     * @param c Character to check
     * @returns `true` if chracter is allowed, otherwise `false`
     */
    bool isAllowed(char &c)
    {
        if (isalnum(c))
            return true;
        if (c == '_' || c == '.' || c == '-')
            return true;
        return false;
    }

    /**
     * Utility function to get the priority of an allowed character
     * @param c Character whose priority is needed
     * @returns the `int` priority of character `c`
     */
    int priority(char &c)
    {
        if (isalpha(c))
            return 1;
        if (isdigit(c))
            return 2;
        return 3;
    }

    /**
     * Function to check if file `f2` would be considered higher in ordering and in priority than file `f1`
     * @param f1 Filename `f1`
     * @param f2 Filename `f2`
     * @returns `true` if `f2` has higher priority in ordering, `false` otherwise
     */
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

    /**
     * Function to create a leaf node in tree
     * @param name Filename
     * @param size File size
     * @returns a new leaf node with given properties
     */
    Node *create(string name, int size)
    {
        return new Node(name, size);
    }

    /**
     * Utility function to get the Balance Factor of a Node
     * @param root Node pointer
     * @returns Balance factor of node `root`
     */
    int getBF(Node *root)
    {
        return (root->left ? root->left->height : 0) - (root->right ? root->right->height : 0);
    }

    /**
     * Function to perform single left rotation
     * @param root Node about which Left rotation is performed
     * @returns modifed `root` after rotation
     */
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

    /**
     * Function to perform single right rotation
     * @param root Node about which Right rotation is performed
     * @returns modifed `root` after rotation
     */
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

    /**
     * Utility function to get inorder predecessor of a node (Given it exists in Left Subtree)
     * @param root Node whose inorder predecessor is to be found
     * @returns the inorder predecessor of `root`
     */
    Node *inorderPred(Node *root)
    {
        root = root->left;
        while (root && root->right)
        {
            root = root->right;
        }
        return root;
    }

    /**
     * Function to insert a file with valid and unique filename
     * @param root root node
     * @param name Filename
     * @param size File size
     * @returns modified root after insertion
     */
    Node *insertUtil(Node *root, string &name, int &size)
    {
        if (!root)
            return create(name, size);
        if (root->fname == name)
        {
            cout << "File already exists" << endl;
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
    /**
     * Function to validate whether given name is a valid or not as per Filename Policy
     * @param name Filename to be checked
     * @returns `true` if a valid filename, otherwise `false`
     */
    bool validateFilename(string &name)
    {
        int n = name.length();
        if (n == 0 || n >= 20)
        {
            cout << "Invalid filename " << name << " length" << endl;
            return false;
        }
        if (name[0] == '_' || name[0] == '.' || name[0] == '-' || name[n - 1] == '_' || name[n - 1] == '.' || name[n - 1] == '-')
        {
            cout << "Invalid filename " << name << ", starting or trailing special characters not allowed" << endl;
            return false;
        }

        for (int i = 0; i < n; i++)
        {
            if (!isAllowed(name[i]))
            {
                cout << "Invalid character present in filename " << name << ": " << name[i] << endl;
                return false;
            }
            if (i > 0 && ((name[i] == '.' && name[i - 1] == '.') || (name[i] == '-' && name[i - 1] == '-') || (name[i] == '_' && name[i - 1] == '_')))
            {
                cout << "Invalid filename " << name << ", Repeating special characters not allowed" << endl;
                return false;
            }
        }

        return true;
    }

    /**
     * Function to search a node in the FS Tree
     * @param root root node
     * @param name Filename to be searched
     * @returns Pointer to searched node, if found, otherwise `nullptr`
     */
    Node *search(Node *root, string &name)
    {
        if (!root || root->fname == name)
            return root;
        if (comparator(root->fname, name))
            return search(root->right, name);
        else
            return search(root->left, name);
    }

    /**
     * Function to insert into the FS AVL Tree
     * @param root root node
     * @param name Filename
     * @param size File size
     * @returns modifed root after insertion
     */
    Node *insert(Node *root, string &name, int &size)
    {
        if (!validateFilename(name))
        {
            return root;
        }

        cout << "Valid Filename " << name << endl;
        return insertUtil(root, name, size);
    }

    /**
     * Function to delete a node from the FS AVL tree
     * @param root root node
     * @param name Filename to be deleted
     * @returns modified root after deletion
     */
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

    /**
     * Function to find the minimum element in the FS AVL tree
     * @param root root node
     * @returns pointer to the minimum element node
     */
    Node *findMin(Node *root)
    {
        if (!root || !root->left)
            return root;
        while (root->left)
            root = root->left;
        return root;
    }

    /**
     * Function to find the maximum element in the FS AVL tree
     * @param root root node
     * @returns pointer to the maximum element node
     */
    Node *findMax(Node *root)
    {
        if (!root || !root->right)
            return root;
        while (root->right)
            root = root->right;
        return root;
    }

    /**
     * Function to display the FS AVL tree in inorder Traversal, along with Node information and Balance Factor
     * @param root root node
     */
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

    /**
     * Function to free all the nodes
     * @param root root node
     */
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
    FS fs;
    Node *root = nullptr;

    cout << "INSERTING FILES" << endl;

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

    cout << "\nINSERTING EXISTING FILE" << endl;
    string f6 = "fileC";
    int s6 = 160;
    root = fs.insert(root, f6, s6);

    cout << "\nSEARCH TEST" << endl;
    string key = "fileC";
    Node *found = fs.search(root, key);
    if (found)
        cout << "Found: " << found->fname << " Size: " << found->fsize << endl;
    else
        cout << "File not found\n";

    cout << "\nMIN / MAX" << endl;
    Node *minNode = fs.findMin(root);
    Node *maxNode = fs.findMax(root);

    if (minNode)
        cout << "Min File: " << minNode->fname << endl;
    if (maxNode)
        cout << "Max File: " << maxNode->fname << endl;

    cout << "\nDELETE OPERATION" << endl;

    cout << "\nDeleting fileD\n";
    string d1 = "fileD";
    root = fs.delete_(root, d1);

    cout << "\nINSERT INVALID FILE" << endl;
    string invalid = ".badFile";
    int s7 = 40;
    root = fs.insert(root, invalid, s7);

    cout << "\nFinal Tree Inorder with BF" << endl;
    fs.display(root);
    fs.freeNodes(root);
    root = nullptr;

    cout << "\n\nTEST CASE 2\n";

    FS fs2;
    Node *root2 = nullptr;

    cout << "INSERTING FILES (WITH MIXED PRIORITY)\n";

    string t1 = "alpha";
    int ts1 = 100;

    string t2 = "Alpha";
    int ts2 = 200;

    string t3 = "alpha_1";
    int ts3 = 150;

    string t4 = "alpha-2";
    int ts4 = 90;

    string t5 = "alpha.3";
    int ts5 = 60;

    root2 = fs2.insert(root2, t1, ts1);
    root2 = fs2.insert(root2, t2, ts2);
    root2 = fs2.insert(root2, t3, ts3);
    root2 = fs2.insert(root2, t4, ts4);
    root2 = fs2.insert(root2, t5, ts5);

    cout << "\nINSERT INVALID FILES\n";

    string bad1 = "_startBad";
    int bs1 = 10;

    string bad2 = "endBad_";
    int bs2 = 20;

    string bad3 = "double__underscore";
    int bs3 = 30;

    root2 = fs2.insert(root2, bad1, bs1);
    root2 = fs2.insert(root2, bad2, bs2);
    root2 = fs2.insert(root2, bad3, bs3);

    cout << "\nSEARCH TEST (EXISTING + NON-EXISTING)\n";

    string key1 = "alpha_1";
    string key2 = "ghostFile";

    Node *f1_ptr = fs2.search(root2, key1);
    Node *f2_ptr = fs2.search(root2, key2);

    if (f1_ptr)
        cout << "Found: " << f1_ptr->fname << " Size: " << f1_ptr->fsize << endl;
    else
        cout << key1 << " not found\n";

    if (f2_ptr)
        cout << "Found: " << f2_ptr->fname << " Size: " << f2_ptr->fsize << endl;
    else
        cout << key2 << " not found\n";

    cout << "\nMIN / MAX\n";
    Node *minNode2 = fs2.findMin(root2);
    Node *maxNode2 = fs2.findMax(root2);

    if (minNode2)
        cout << "Min File: " << minNode2->fname << endl;
    if (maxNode2)
        cout << "Max File: " << maxNode2->fname << endl;

    cout << "\nDELETE TEST (EXISTING + NON-EXISTING)\n";

    string del1 = "alpha";
    string del2 = "notPresent";

    root2 = fs2.delete_(root2, del1);
    root2 = fs2.delete_(root2, del2);

    cout << "\nTREE AFTER DELETIONS\n";
    fs2.display(root2);

    fs2.freeNodes(root2);
    root2 = nullptr;

    return 0;
}