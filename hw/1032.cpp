#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef char TElemSet;

struct BinaryTreeNode // 定义二叉树节点的结构体
{
    TElemSet data; // 节点的数据成员，类型为 TElemSet
    BinaryTreeNode *left; // 指向左子节点的指针
    BinaryTreeNode *right; // 指向右子节点的指针

    BinaryTreeNode(TElemSet val) : data(val), left(nullptr), right(nullptr) {} // 构造函数，初始化节点数据
};

class BinaryTree // 定义二叉树类
{
private:
    BinaryTreeNode *root; // 指向二叉树根节点的指针

public:
    void CopyTree(BinaryTreeNode *&thisNode, BinaryTreeNode *otherNode); // 深拷贝二叉树的递归函数，将 otherNode 拷贝到 thisNode
    void DestroyTree(BinaryTreeNode *node); // 递归销毁以 node 为根节点的二叉树，释放内存
    BinaryTreeNode *BuildTree(const TElemSet *preorder, const TElemSet *inorder, int n); // 根据前序和中序遍历序列构建二叉树
    BinaryTree(const TElemSet *preorder, const TElemSet *inorder, int n); // 带参数的构造函数，用于从遍历序列构建二叉树
    BinaryTree(const BinaryTree &other); // 深拷贝构造函数，用于根据已有二叉树创建新二叉树
    ~BinaryTree(); // 析构函数，用于销毁二叉树并释放内存
    BinaryTree &operator=(const BinaryTree &other); // 赋值操作符重载，用于将一个二叉树赋值给另一个二叉树
    BinaryTreeNode *getRoot(); // 返回根节点的指针
    int Diameter(BinaryTreeNode *node); // 计算并返回以 node 为根节点的子树的直径
    int Height(BinaryTreeNode *node); // 计算并返回以 node 为根节点的子树的高度
};

int search_path(BinaryTreeNode *node,int& max_dia)
{
    int left = 0;
    int right = 0;
    if(node->left != nullptr)
    {
        left = search_path(node->left, max_dia) + 1;
    }
    if(node->right != nullptr)
    {
        right = search_path(node->right, max_dia) + 1;
    }
    if(left + right> max_dia)
        max_dia = left + right;
    return max(left, right);
}

int BinaryTree::Diameter(BinaryTreeNode *node) {
    int max_dia = 0;
    if(node != nullptr)
        search_path(node, max_dia);
    return max_dia;
}


//recursive version
#include <functional>
int Diameter(BinaryTreeNode *node)
{
    if(node == nullptr)
        return 0;
    int max_dia = 0;
    function<int(BinaryTreeNode*)> dfs = [&](BinaryTreeNode* curr) -> int
    {
        int left = 0;
        int right = 0;
        if(curr->left != nullptr)
            left = dfs(curr->left) + 1;
        if(curr->right != nullptr)
            right = dfs(curr->right) + 1;
        if(max_dia < left + right)
            max_dia = left + right;
        return max(left, right);
    };
    dfs(node);
    return max_dia;
}