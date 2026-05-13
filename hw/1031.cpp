#include <iostream>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class BiNODE {
public:
    char data; // 结点值，字符类型，可以按字典序比较大小
    BiNODE* lchild; // 左子节点
    BiNODE* rchild; // 右子节点

    BiNODE(char d = '\0');//构造函数
    ~BiNODE();//析构函数
};

BiNODE::BiNODE(char d) : data(d), lchild(nullptr), rchild(nullptr) {}

BiNODE::~BiNODE() {
    delete lchild;
    delete rchild;
}

class BinaryTree {
public:

    BinaryTree(BiNODE* r = nullptr);  // 构造函数
    ~BinaryTree(); //析构函数

    BiNODE* BuildTree();  // 构建二叉树的函数
    void Recursion_Pre_Order(BiNODE* node);  // 递归前序遍历函数
    void NoRecursion_Pre_Order(BiNODE* node);  // 非递归前序遍历函数
    void Recursion_In_Order(BiNODE* node);  // 递归中序遍历函数
    void NoRecursion_In_Order(BiNODE* node);  // 非递归中序遍历函数
    void Recursion_Post_Order(BiNODE* node);  // 递归后序遍历函数
    void NoRecursion_Post_Order(BiNODE* node);  // 非递归后序遍历函数
    void Hierachicalorder(BiNODE* node);  // 层次遍历函数

    int Size_Of_Tree(BiNODE* node);  // 计算二叉树大小的函数
    int Height_Of_Tree(BiNODE* node);  // 计算二叉树高度的函数
    bool Is_Full_Tree(BiNODE* node);  // 判断是否为满二叉树的函数
    bool Is_Complete_Tree(BiNODE* node);  // 判断是否为完全二叉树的函数
    bool Is_Perfect_Tree(BiNODE*);//判断是否是完美二叉树
    bool another_way(BiNODE*);

    BiNODE* GetRoot();  // 获取根节点的函数
    void SetRoot(BiNODE* node);  // 修改根节点的函数

private:
    BiNODE* root;  // 二叉树的根节点
    void freeTree(BiNODE* node);  // 释放二叉树节点的函数
};

/*************************************************************************/
BiNODE* build_helper(int pre_left, int pre_right, int in_left, int in_right,const vector<char>& pre_order,const vector<char>& in_order)
{
    if (pre_left > pre_right)//base case
    {
        return nullptr;
    }
    BiNODE* root = new BiNODE(pre_order[pre_left]);
    int root_in = in_left;
    while(in_order[root_in] != root->data)
    {
        root_in++;
    }
    root->lchild = build_helper(pre_left + 1, pre_left + root_in - in_left, in_left, root_in - 1, pre_order, in_order);
    root->rchild = build_helper(pre_left + 1 + root_in - in_left, pre_right, root_in + 1, in_right, pre_order, in_order);
    return root;
}
BiNODE* BinaryTree:: BuildTree()//前序+中序建树，在函数中处理输入
{
    int num;
    cin >> num;
    BiNODE* root = nullptr;
    vector<char> pre_order(num);
    vector<char> in_order(num);
    for(int i = 0; i < num; i++)
    {
        cin >> pre_order[i];
    }
    for(int i = 0; i < num; i++)
    {
        cin >> in_order[i];
    }
    root = build_helper(0, num - 1, 0, num - 1, pre_order, in_order);
    
    return root;
}
void BinaryTree:: Recursion_Pre_Order(BiNODE* node)//递归前序遍历（*）
{
    if(node != nullptr)
    {
        cout << node->data << " ";
        Recursion_Pre_Order(node->lchild);
        Recursion_Pre_Order(node->rchild);
    }
}
void BinaryTree:: NoRecursion_Pre_Order(BiNODE* tree)//非递归前序遍历（*）
{
    stack<BiNODE*> tree_node;
    while (tree != nullptr || !tree_node.empty())
    {
        while (tree != nullptr)
        {
            cout << tree->data << " ";
            tree_node.push(tree);
            tree = tree->lchild;
        }
        
        if(!tree_node.empty())
        {
            tree = tree_node.top()->rchild;//turns to the right subtree of the current tree since left subtree has been viewed
            tree_node.pop();
        }
    }
}
void BinaryTree:: Recursion_In_Order(BiNODE* curr)//递归中序遍历（*）
{
    if(curr != nullptr)
    {
        Recursion_In_Order(curr->lchild);
        cout << curr->data << " ";
        Recursion_In_Order(curr->rchild);
    }
}
void BinaryTree:: NoRecursion_In_Order(BiNODE* curr)//非递归中序遍历
{
    stack<BiNODE*> tree_node;
    while(!tree_node.empty() || curr != nullptr)
    {
        while(curr != nullptr)
        {
            tree_node.push(curr);
            curr = curr->lchild;
        }
        if(!tree_node.empty())
        {
            curr = tree_node.top();
            cout << curr->data << " ";
            tree_node.pop();
            curr = curr->rchild;
        }
        
    }
}
void BinaryTree:: Recursion_Post_Order(BiNODE* curr)//递归后序遍历（*）
{
    if(curr != nullptr)
    {
        Recursion_Post_Order(curr->lchild);
        Recursion_Post_Order(curr->rchild);
        cout << curr->data << " " ;
    }
}
void BinaryTree:: NoRecursion_Post_Order(BiNODE* curr)//非递归后序遍历
{
    BiNODE* last_visited = nullptr;
    stack<BiNODE*> tree_node;
    while(!tree_node.empty() || curr != nullptr)
    {
        while(curr != nullptr)
        {
            tree_node.push(curr);
            curr = curr->lchild;
        }
        if(!tree_node.empty())
        {
            if(tree_node.top()->rchild == last_visited || tree_node.top()->rchild == nullptr)
            {
                last_visited = tree_node.top();
                tree_node.pop();
                cout << last_visited->data << endl;
            }
            else
            {
                curr = tree_node.top()->rchild;
            }
        }
    }
}
void BinaryTree:: Hierachicalorder(BiNODE* node)//层次遍历（*）
{
    if(node == nullptr) return;
    queue<BiNODE*> tree_queue;
    tree_queue.push(node);
    while(!tree_queue.empty())
    {
        BiNODE* temp = tree_queue.front();
        tree_queue.pop();
        cout << temp->data << " ";
        if(temp->lchild != nullptr)
            tree_queue.push(temp->lchild);
        if(temp->rchild != nullptr)
            tree_queue.push(temp->rchild);
    }
}

int BinaryTree:: Size_Of_Tree(BiNODE* node)//求结点个数
{
    if(node == nullptr) return 0;
    int count = 0;
    queue<BiNODE*> tree_queue;
    tree_queue.push(node);
    while(!tree_queue.empty())
    {
        BiNODE* temp = tree_queue.front();
        tree_queue.pop();
        count++;
        if(temp->lchild != nullptr)
            tree_queue.push(temp->lchild);
        if(temp->rchild != nullptr)
            tree_queue.push(temp->rchild);
    }
    return count;
}

int BinaryTree:: Height_Of_Tree(BiNODE* node)//返回二叉树的高度，这里定义空树高度为0.无需输出，返回即可
{
    if (node == nullptr) return 0;
    int height = 0;
    queue<BiNODE*> tree_queue;
    tree_queue.push(node);
    while(!tree_queue.empty())
    {
        int size = tree_queue.size();
        for(int i = 0; i < size; i++)
        {
            BiNODE* temp = tree_queue.front();
            tree_queue.pop();
            if(temp->lchild != nullptr)
                tree_queue.push(temp->lchild);
            if(temp->rchild != nullptr)
                tree_queue.push(temp->rchild);
        }
        height++;
    }
    return height;
}
bool BinaryTree:: Is_Full_Tree(BiNODE* node)//判断是否是满二叉树
{
    if(node == nullptr) return true;
    if(node->lchild == nullptr && node->rchild == nullptr)
    {
        return true;
    }
    else if(node->lchild == nullptr || node->rchild == nullptr)
    {
        return false;
    }
    else
    {
        return Is_Full_Tree(node->lchild) && Is_Full_Tree(node->rchild);
    }
}
bool BinaryTree:: Is_Complete_Tree(BiNODE* node)//判断是否是完全二叉树
{
    queue<BiNODE*> node_queue;
    if(node == nullptr) return true;
    node_queue.push(node);
    bool has_null = false;
    while(!node_queue.empty())
    {
        int size = node_queue.size();
        for(int i = 0; i < size; i++)
        {
            BiNODE* temp = node_queue.front();
            node_queue.pop();
            if(temp == nullptr)
            {
                has_null = true;
            }
            else
            {
                if(has_null)
                {
                    return false;
                }
                node_queue.push(temp->lchild);
                node_queue.push(temp->rchild);
            }
        }
    }
    return true;
}
bool is_complete(BiNODE* node, int index, int size)
{
    if(node == nullptr)
    {
        return true;
    }
    if(index > size)
    {
        return false;
    }
    return is_complete(node->lchild, 2 * index, size) && is_complete(node->rchild, 2 * index + 1, size);
}
bool BinaryTree:: another_way(BiNODE* node)
{
    int size = Size_Of_Tree(node);
    return is_complete(node, 1, size);
}


bool BinaryTree:: Is_Perfect_Tree(BiNODE* node)//判断是否是完美二叉树
{
    if(node == nullptr) return true;
    int h = Height_Of_Tree(node);
    int count = Size_Of_Tree(node);
    return count == (1 << h) - 1;//it's the same as 2^n
}