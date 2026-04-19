#include <iostream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

/**
 * Tree Node structure
 * @param val Character data value
 * @param left Left child
 * @param right Right child
 */
struct Node
{
    char val;
    Node *left;
    Node *right;

    Node(char v) : val(v), left(nullptr), right(nullptr) {}
};

/**
 * Stack class for Building Expression Tree
 */
class Stack
{
    Node *arr[1000];
    int top;

public:
    Stack() : top(-1) {}

    void push(Node *x)
    {
        if (top == 999)
        {
            cout << "Stack overflow\n";
            return;
        }
        arr[++top] = x;
    }

    Node *pop()
    {
        if (top == -1)
            return nullptr;
        return arr[top--];
    }

    bool empty()
    {
        return top == -1;
    }
};

/**
 * Expression Tree Class
 * @note Tree stores the expression character-wise, so using number as "12" will read as seperate operands 1 and 2, Use the tree to store the character variables and operators, and then evaluate using the variable map
 */
class ExpTree
{
    /**
     * Allowed Operators
     * @param c Character to be checked
     * @returns `true` if character `c` is a valid and allowed operator as per Policy
     */
    bool isOperator(char c)
    {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    /**
     * Allowed Operands
     * @param c Character to be checked
     * @returns `true` if character `c` is a valid and allowed operand as per Policy
     */
    bool isOperand(char c)
    {
        return isalnum(c);
    }

    /**
     * Validates given string for PREFIX expression
     * @param expr Expression string to be checked
     * @returns `true` if `expr` is a valid PREFIX expression
     */
    bool validatePrefix(string &expr)
    {
        int count = 0;

        for (int i = expr.size() - 1; i >= 0; i--)
        {
            char c = expr[i];

            if (isOperand(c))
                count++;
            else if (isOperator(c))
            {
                if (count < 2)
                    return false;
                count--;
            }
            else
                return false;
        }
        return count == 1;
    }

    /**
     * Validates given string for POSTFIX expression
     * @param expr Expression string to be checked
     * @returns `true` if `expr` is a valid POSTFIX expression
     */
    bool validatePostfix(string &expr)
    {
        int count = 0;

        for (char c : expr)
        {
            if (isOperand(c))
                count++;
            else if (isOperator(c))
            {
                if (count < 2)
                    return false;
                count--;
            }
            else
                return false;
        }
        return count == 1;
    }

    /**
     * Validates given string for INFIX expression
     * @param expr Expression string to be checked
     * @returns `true` if `expr` is a valid INFIX expression
     */
    bool validateInfix(string &expr)
    {
        int balance = 0;

        for (int i = 0; i < expr.size(); i++)
        {
            char c = expr[i];
            if (!isOperand(c) && !isOperator(c) && c != '(' && c != ')')
                return false;

            if (c == '(')
            {
                balance++;
                if (i + 1 < expr.size() && isOperator(expr[i + 1]))
                    return false;
            }
            else if (c == ')')
            {
                balance--;
                if (balance < 0)
                    return false;

                if (i > 0 && isOperator(expr[i - 1]))
                    return false;
            }

            if (i > 0 && isOperand(c) && isOperand(expr[i - 1]))
                return false;
            if (i > 0 && isOperator(c) && isOperator(expr[i - 1]))
                return false;
            if (i > 0 && isOperand(expr[i - 1]) && c == '(')
                return false;
            if (i > 0 && expr[i - 1] == ')' && isOperand(c))
                return false;
        }

        if (isOperator(expr[0]) || isOperator(expr.back()))
            return false;

        return balance == 0;
    }

    /**
     * Utility function to get precedence of operator
     * @param op operator
     * @returns precedence of operator `op`
     */
    int precedence(char op)
    {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return 0;
    }

    /**
     * Utility function to convert infix expression to postfix
     * @param expr INFIX input expression
     * @returns POSTFIX expression of `expr`
     */
    string infixToPostfix(string &expr)
    {
        char stack[1000];
        int top = -1;
        string output = "";

        for (char c : expr)
        {
            if (isOperand(c))
            {
                output += c;
            }
            else if (c == '(')
            {
                stack[++top] = c;
            }
            else if (c == ')')
            {
                while (top != -1 && stack[top] != '(')
                    output += stack[top--];

                if (top == -1)
                {
                    cout << "Mismatched parentheses\n";
                    return "";
                }
                top--;
            }
            else
            {
                while (top != -1 && precedence(stack[top]) >= precedence(c))
                    output += stack[top--];
                stack[++top] = c;
            }
        }

        while (top != -1)
            output += stack[top--];

        return output;
    }

    /**
     * Function to build Exp Binary Tree from POSTFIX expression
     * @param expr input POSTFIX expression
     * @returns `root` pointer of the expression tree
     */
    Node *buildFromPostfix(string &expr)
    {
        Stack st;

        for (char c : expr)
        {
            if (isOperand(c))
            {
                st.push(new Node(c));
            }
            else
            {
                Node *right = st.pop();
                Node *left = st.pop();

                if (!left || !right)
                {
                    cout << "Malformed POSTFIX expression\n";
                    return nullptr;
                }

                Node *node = new Node(c);
                node->left = left;
                node->right = right;

                st.push(node);
            }
        }

        return st.pop();
    }
    /**
     * Function to build Exp Binary Tree from PREFIX expression
     * @param expr input PREFIX expression
     * @returns `root` pointer of the expression tree
     */
    Node *buildFromPrefix(string &expr)
    {
        Stack st;

        for (int i = expr.size() - 1; i >= 0; i--)
        {
            char c = expr[i];

            if (isOperand(c))
            {
                st.push(new Node(c));
            }
            else
            {
                Node *left = st.pop();
                Node *right = st.pop();

                if (!left || !right)
                {
                    cout << "Malformed PREFIX expression\n";
                    return nullptr;
                }

                Node *node = new Node(c);
                node->left = left;
                node->right = right;

                st.push(node);
            }
        }

        return st.pop();
    }

    /**
     * Utility function for inorder traversal of Exp Tree
     * @param root Root Node Pointer
     * @param inf INFIX string
     */
    void inorder(Node *root, string &inf)
    {
        if (!root)
            return;

        if (root->left)
            inf += '(';
        inorder(root->left, inf);
        inf += root->val;
        inorder(root->right, inf);
        if (root->right)
            inf += ')';
    }

    /**
     * Utility function for preorder traversal of Exp Tree
     * @param root Root Node Pointer
     * @param pre PREFIX string
     */
    void preorder(Node *root, string &pre)
    {
        if (!root)
            return;
        pre += root->val;
        preorder(root->left, pre);
        preorder(root->right, pre);
    }

    /**
     * Utility function for postorder traversal of Exp Tree
     * @param root Root Node Pointer
     * @param post POSTFIX string
     */
    void postorder(Node *root, string &post)
    {
        if (!root)
            return;
        postorder(root->left, post);
        postorder(root->right, post);
        post += root->val;
    }

    /**
     * Recursive utility function to get count of total nodes, internal nodes and leaf nodes
     * @param root Root node pointer
     * @param total Total nodes
     * @param internal Internal nodes
     * @param leaf Leaf nodes
     */
    void count(Node *root, int &total, int &internal, int &leaf)
    {
        if (!root)
            return;

        total++;

        if (!root->left && !root->right)
            leaf++;
        else
            internal++;

        count(root->left, total, internal, leaf);
        count(root->right, total, internal, leaf);
    }

public:
    /**
     * Function to detect the format of input expression
     * @returns format of `exp` as INFIX, POSTFIX, PREFIX. UNRECOGNISED if invalid.
     */
    string detectFormat(string &exp)
    {
        bool pre = validatePrefix(exp);
        bool post = validatePostfix(exp);
        bool in = validateInfix(exp);

        if (pre && !post && !in)
            return "PREFIX";
        if (post && !pre && !in)
            return "POSTFIX";
        if (in && !pre && !post)
            return "INFIX";

        return "UNRECOGNISED";
    }

    /**
     * Function to validate an expression as per Validation Policy
     * @param exp Input expression
     * @returns `true` if exp follows validation policy, otherwise `false`
     * @note Invalid expressions are rejected and also reported with the reason
     */
    bool validateExpression(string &exp)
    {
        int op = 0;
        int opr = 0;
        int balance = 0;
        for (int i = 0; i < exp.length(); i++)
        {
            char c = exp[i];
            if (!isOperand(c) && !isOperator(c) && c != '(' && c != ')')
            {
                cout << "Not a valid Operator/Operand/Bracket" << endl;
                return false;
            }
            if (isOperand(c))
                op++;
            else if (isOperator(c))
                opr++;
            if (c == '(')
                balance++;
            else if (c == ')')
                balance--;
        }
        // For n operands, there should be exactly n-1 operators
        if (opr != op - 1)
        {
            cout << "Invalid number of operators/operand" << endl;
            return false;
        }

        // Only parenthesis brackets are allowed, and they should be balanced
        if (balance != 0)
        {
            cout << "Parenthesis not balanced in expression" << endl;
            return false;
        }
        return true;
    }

    /**
     * Function to build Expression Tree from given expression
     * @param exp Input expression
     * @returns Pointer to root of the Exp Tree so formed
     * @note If the expression is identified as INFIX, it is converted into POSTFIX first
     */
    Node *buildTree(string &exp)
    {
        if (!validateExpression(exp)) return nullptr;
        string format = detectFormat(exp);

        if (format == "INFIX")
        {
            if (!validateInfix(exp))
            {
                cout << "Invalid INFIX expression\n";
                return nullptr;
            }
            string postfix = infixToPostfix(exp);
            if (postfix == "")
                return nullptr;

            return buildFromPostfix(postfix);
        }
        else if (format == "POSTFIX")
        {
            if (!validatePostfix(exp))
            {
                cout << "Invalid POSTFIX expression\n";
                return nullptr;
            }
            return buildFromPostfix(exp);
        }
        else if (format == "PREFIX")
        {
            if (!validatePrefix(exp))
            {
                cout << "Invalid PREFIX expression\n";
                return nullptr;
            }
            return buildFromPrefix(exp);
        }

        cout << "Unrecognised expression\n";
        return nullptr;
    }

    /**
     * Function to evaluate expression from Exp Tree using variables mapping
     * @param root Root node pointer
     * @param varMap Variable Map
     * @param flag Updated to `true`, if successfully evaluated, otherwise `false`
     * @returns Evaluated single double value (to avoid information lost due to int division)
     */
    double evaluate(Node *root, map<char, double> &varMap, bool &flag)
    {
        if (!root)
        {
            cout << "Empty expression tree" << endl;
            flag = false;
            return 0;
        }

        char c = root->val;

        if (!root->left && !root->right)
        {
            if (isdigit(c))
                return double(c - '0');

            if (isalpha(c))
            {
                if (varMap.find(c) == varMap.end())
                {
                    cout << "Undefined variable: " << c << endl;
                    flag = false;
                    return 0;
                }
                return varMap[c];
            }

            cout << "Invalid operand encountered" << endl;
            flag = false;
            return 0;
        }

        double left = evaluate(root->left, varMap, flag);
        if (!flag)
            return 0;
        double right = evaluate(root->right, varMap, flag);
        if (!flag)
            return 0;

        if (c == '+')
            return left + right;
        else if (c == '-')
            return left - right;
        else if (c == '*')
            return left * right;

        else if (c == '/')
        {
            if (right == 0)
            {
                cout << "Division by zero" << endl;
                flag = false;
                return 0;
            }
            return left / right;
        }

        cout << "Invalid operator" << endl;
        flag = false;
        return 0;
    }

    /**
     * Function to return the INFIX Representation of Tree
     * @param root Root node pointer
     * @returns INFIX Expression
     */
    string toInfix(Node *root)
    {
        string inf = "";
        inorder(root, inf);
        return inf;
    }

    /**
     * Function to return the PREFIX Representation of Tree
     * @param root Root node pointer
     * @returns PREFIX Expression
     */
    string toPrefix(Node *root)
    {
        string pre = "";
        preorder(root, pre);
        return pre;
    }

    /**
     * Function to return the POSTFIX Representation of Tree
     * @param root Root node pointer
     * @returns POSTFIX Expression
     */
    string toPostfix(Node *root)
    {
        string post = "";
        postorder(root, post);
        return post;
    }

    /**
     * Function to count the nodes in the Exp Tree
     * @param root Root node pointer
     * @returns array containing count of total nodes, internal and leaf nodes
     * @note free the arr after returning, as it is dynamically allocated
     */
    int *countNodes(Node *root)
    {
        int total, internal, leaf;
        total = internal = leaf = 0;
        count(root, total, internal, leaf);

        int *arr = new int[3];
        arr[0] = total;
        arr[1] = internal;
        arr[2] = leaf;
        return arr;
    }

    /**
     * Function to free all the nodes
     * @param root root node
     */
    void freeTree(Node *root)
    {
        if (!root)
            return;
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
};

int main()
{
    ExpTree tree;
    string expr = "ab+c*";
    cout << "Testing Expression: " << expr << endl;
    cout << "\nEXPRESSION VALIDATION\n";
    if (!tree.validateExpression(expr))
    {
        cout << "Expression is INVALID\n";
    }
    else
        cout << "Expression is VALID\n";

    cout << "\nFORMAT DETECTION\n";
    string format = tree.detectFormat(expr);
    cout << "Detected Format: " << format << endl;

    cout << "\nBUILDING TREE\n";
    Node *root = tree.buildTree(expr);
    if (!root)
    {
        cout << "Tree construction failed\n";
        return 0;
    }
    cout << "Tree constructed successfully\n";

    cout << "\nREPRESENTATIONS\n";
    cout << "Infix   : " << tree.toInfix(root) << endl;
    cout << "Prefix  : " << tree.toPrefix(root) << endl;
    cout << "Postfix : " << tree.toPostfix(root) << endl;

    cout << "\nEVALUATION\n";
    map<char, double> varMap;
    varMap['a'] = 2;
    varMap['b'] = 3;
    varMap['c'] = 4;
    varMap['d'] = 5;

    bool flag = true;
    int result = tree.evaluate(root, varMap, flag);
    if (flag)
        cout << "Evaluated Result at a=2,b=3,c=4,d=5: " << result << endl;

    cout << "\nNODE COUNTS\n";
    int *counts = tree.countNodes(root);
    cout << "Total Nodes   : " << counts[0] << endl;
    cout << "Internal Nodes: " << counts[1] << endl;
    cout << "Leaf Nodes    : " << counts[2] << endl;
    delete[] counts;

    tree.freeTree(root);

    cout << "\n\nTEST CASE 2\n";

    ExpTree tree2;

    string expr2 = "(a+b)*(c-d)";
    cout << "\nTesting Expression: " << expr2 << endl;

    cout << "\nEXPRESSION VALIDATION\n";
    if (!tree.validateExpression(expr2))
    {
        cout << "Expression is INVALID\n";
    }
    else
        cout << "Expression is VALID\n";

    cout << "\nFORMAT DETECTION\n";
    string format2 = tree2.detectFormat(expr2);
    cout << "Detected Format: " << format2 << endl;

    Node *root2 = tree2.buildTree(expr2);
    if (!root2)
    {
        cout << "Tree construction failed\n";
    }
    else
    {
        cout << "\nREPRESENTATIONS\n";
        cout << "Infix   : " << tree2.toInfix(root2) << endl;
        cout << "Prefix  : " << tree2.toPrefix(root2) << endl;
        cout << "Postfix : " << tree2.toPostfix(root2) << endl;

        cout << "\nEVALUATION\n";
        map<char, double> varMap2;
        varMap2['a'] = 5;
        varMap2['b'] = 2;
        varMap2['c'] = 10;
        varMap2['d'] = 3;

        bool flag2 = true;
        double result2 = tree2.evaluate(root2, varMap2, flag2);

        if (flag2)
            cout << "Evaluated Result: " << result2 << endl;

        cout << "\nNODE COUNTS\n";
        int *counts2 = tree2.countNodes(root2);
        cout << "Total Nodes   : " << counts2[0] << endl;
        cout << "Internal Nodes: " << counts2[1] << endl;
        cout << "Leaf Nodes    : " << counts2[2] << endl;
        delete[] counts2;

        tree2.freeTree(root2);
    }

    string expr3 = "*+ab-cd";
    cout << "\nTesting Expression: " << expr3 << endl;

    cout << "\nEXPRESSION VALIDATION\n";
    if (!tree.validateExpression(expr3))
    {
        cout << "Expression is INVALID\n";
    }
    else
        cout << "Expression is VALID\n";

    string format3 = tree2.detectFormat(expr3);
    cout << "Detected Format: " << format3 << endl;

    Node *root3 = tree2.buildTree(expr3);

    if (root3)
    {
        cout << "\nPrefix  : " << tree2.toPrefix(root3) << endl;
        cout << "Infix   : " << tree2.toInfix(root3) << endl;
        cout << "Postfix : " << tree2.toPostfix(root3) << endl;

        map<char, double> varMap3;
        varMap3['a'] = 1;
        varMap3['b'] = 2;
        varMap3['c'] = 3;
        varMap3['d'] = 4;

        bool flag3 = true;
        double result3 = tree2.evaluate(root3, varMap3, flag3);

        if (flag3)
            cout << "Evaluated Result: " << result3 << endl;

        tree2.freeTree(root3);
    }

    string expr4 = "a++b";
    cout << "\nTesting Expression: " << expr4 << endl;

    cout << "\nEXPRESSION VALIDATION\n";
    if (!tree.validateExpression(expr4))
    {
        cout << "Expression is INVALID\n";
    }
    else
        cout << "Expression is VALID\n";

    string format4 = tree2.detectFormat(expr4);
    cout << "Detected Format: " << format4 << endl;

    Node *root4 = tree2.buildTree(expr4);
    if (!root4)
    {
        cout << "Invalid expression correctly rejected\n";
    }

    string expr7 = "((a+b)*(c+d)-(e/f+g*h))";
    cout << "\nTesting Expression: " << expr7 << endl;

    cout << "\nEXPRESSION VALIDATION\n";
    if (!tree.validateExpression(expr7))
    {
        cout << "Expression is INVALID\n";
    }
    else
        cout << "Expression is VALID\n";

    string format7 = tree2.detectFormat(expr7);
    cout << "Detected Format: " << format7 << endl;

    Node *root7 = tree2.buildTree(expr7);

    if (root7)
    {
        cout << "\nREPRESENTATIONS\n";
        cout << "Infix   : " << tree2.toInfix(root7) << endl;
        cout << "Prefix  : " << tree2.toPrefix(root7) << endl;
        cout << "Postfix : " << tree2.toPostfix(root7) << endl;

        cout << "\nEVALUATION\n";
        map<char, double> varMap7;
        varMap7['a'] = 2;
        varMap7['b'] = 3;
        varMap7['c'] = 4;
        varMap7['d'] = 5;
        varMap7['e'] = 20;
        varMap7['f'] = 2;
        varMap7['g'] = 3;
        varMap7['h'] = 4;

        bool flag7 = true;
        double result7 = tree2.evaluate(root7, varMap7, flag7);

        if (flag7)
            cout << "Evaluated Result: " << result7 << endl;

        cout << "\nNODE COUNTS\n";
        int *counts7 = tree2.countNodes(root7);
        cout << "Total Nodes   : " << counts7[0] << endl;
        cout << "Internal Nodes: " << counts7[1] << endl;
        cout << "Leaf Nodes    : " << counts7[2] << endl;
        delete[] counts7;

        tree2.freeTree(root7);
    }

    return 0;
}