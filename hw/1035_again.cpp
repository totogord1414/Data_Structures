#include <bits/stdc++.h>

#define MAXN 107 // 最大节点个数
#define INFINITY_WEIGHT 0x3F3F3F // 权重无穷大
using namespace std;
struct node{
    char data;
     node* leftChild;
     node* rightChild;
     double weight;
     int leafCount;
     char minLeafchar;
     node(char d, double w, int l, char m, node* left = nullptr, node* right = nullptr)
     {
        data = d;
        weight = w;
        leafCount = l;
        minLeafchar = m;
        leftChild = left;
        rightChild = right;
     }
};

struct Compare// a functor that fits the min heap aka priority queue
{
    bool operator()(node* a, node* b)
    {
        if(abs(a->weight - b->weight) < 1e-5)
        {
            if(a->leafCount == b->leafCount)
            {
                return a->minLeafchar > b->minLeafchar;
            }
            return a->leafCount > b->leafCount;
        }
        return a->weight > b->weight;
    }
};



void generateCode(node* root, string val, map<char, string>& node_map)//a function that generate's all node's code
{
    if(!root)
        return;
    if(root->leftChild)
    {
        generateCode(root->leftChild, val + '0', node_map);
        generateCode(root->rightChild, val + '1', node_map);
        return;
    }
    node_map[root->data] = val;
}

/**
 * [构建一课Huffman树]
 * @param  data[] [每个结点的值]
 * @param  weight[] [每个结点出现的频率]
 * @param  number [] [结点的个数]
 * @return   [Huffman树根]
 */
node* createHuffmanTree(char data[], double weight[], int number)
{
    priority_queue<node*, vector<node*>, Compare> pq;
    node* root = nullptr;


    for(int i = 0; i < number; i++)
    {
        node* newNode = new node(data[i], weight[i], 1, data[i]);
        pq.push(newNode);
    }
    for(int i = 0; i < number - 1; i++)//create the tree
    {
        node* left = pq.top();
        pq.pop();
        node* right = pq.top();
        pq.pop();
        node* newNode = new node('*', left->weight + right->weight, left->leafCount + right->leafCount, min(left->minLeafchar, right->minLeafchar), left, right);
        pq.push(newNode);
    }
    root = pq.top();

    map<char, string> node_map;
    generateCode(root, "", node_map);
    for(int i = 0; i < number; i++)
    {
        string code = node_map[data[i]];
        cout << data[i] << " " << code << " " << code.length() << " " << fixed << setprecision(3) << code.length() * weight[i] << endl;
    }

    return root;
}