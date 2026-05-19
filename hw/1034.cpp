#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <stack>
using namespace std;

struct Data
{
    bool isOp;
    char op;
    double oprand;
};

struct TreeNode
{
    Data data;
    TreeNode* left;
    TreeNode* right;

    TreeNode()
        : data(), left(nullptr), right(nullptr) {}
    TreeNode(const Data& data_, TreeNode* left_, TreeNode* right_)
        : data(data_), left(left_), right(right_) {}
    ~TreeNode()
    {
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
    }
};

TreeNode* buildTree(const string& expr);
double solveExprTree(TreeNode* root);

int main()
{
    int T{ 0 };
    cin >> T;
    for (int i = 0; i < T; i++) {
        string expression;
        cin >> expression;
        TreeNode* root{ buildTree(expression) };
        cout << fixed << setprecision(6) << solveExprTree(root) << endl;
        delete root;
    }
    return 0;
}

TreeNode* buildTree(const string& expr)
{
    stack<TreeNode*> nodes;
    for (const auto& c : expr) {
        if (isdigit(c)) {
            Data data{ false, 0, double(c - '0') };
            nodes.push(new TreeNode{ data, nullptr, nullptr });
        }
        else {
            Data data{ true, c, -1.0 };
            TreeNode* right = nodes.top();
            nodes.pop();
            TreeNode* left = nodes.top();
            nodes.pop();
            nodes.push(new TreeNode{ data, left, right });
        }
    }
    return nodes.top();
}

double solveExprTree(TreeNode* root) {
    if(!root)
        return 0.0;
    if(!root->data.isOp)
    {
        return root->data.oprand;
    }
    else
    {
        char op = root->data.op;
        switch (op)
        {
        case '+':
            return solveExprTree(root->left) + solveExprTree(root->right);
        case '-':
            return solveExprTree(root->left) - solveExprTree(root->right);
        case '*':
            return solveExprTree(root->left) * solveExprTree(root->right);
        case '/':
            return solveExprTree(root->left) / solveExprTree(root->right);
        default:
            return 0.0;
        }
    }
}