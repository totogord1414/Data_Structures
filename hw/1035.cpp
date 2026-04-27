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
    char minLeafChar;
    node(char d, double w, int l, char m, node* left = nullptr, node* right = nullptr)
    {
        data = d;
        weight = w;
        leafCount = l;
        minLeafChar = m;
        leftChild = left;
        rightChild = right;
    }
};

/**
 * [构建一课Huffman树]
 * @param  data[] [每个结点的值]
 * @param  weight[] [每个结点出现的频率]
 * @param  number [] [结点的个数]
 * @return   [Huffman树根]
 */
bool compareNodes(node* a, node* b)
{
    if(abs(a->weight - b->weight) > 1e-7)
    {
        return a->weight < b->weight;
    }
    if(a->leafCount != b->leafCount)
    {
        return a->leafCount < b->leafCount;
    }
    return a->minLeafChar < b->minLeafChar;
}
 
void generateCode(node* root, map<char, string>& code_map, string code)
{
    if(root == nullptr)
        return;
    if(root->leftChild == nullptr && root->rightChild == nullptr)
    {
        code_map[root->data] = code;
    }
    generateCode( root->leftChild, code_map, code + '0');
    generateCode( root->rightChild, code_map, code + '1');
}
node* createHuffmanTree(char data[], double weight[], int number)
{
    vector<node*> leaf;
    for(int i = 0; i < number; i++)
    {
        node* NewNode = new node(data[i], weight[i], 1, data[i]);
        leaf.push_back(NewNode);
    }
    while(leaf.size() > 1)
    {
        sort(leaf.begin(), leaf.end(), compareNodes);
        node* left = leaf.front();
        leaf.erase(leaf.begin());
        node* right = leaf.front();
        leaf.erase(leaf.begin());
        node* NewNode = new node('*', left->weight + right->weight, left->leafCount + right->leafCount, min(left->minLeafChar, right->minLeafChar));
        NewNode->leftChild = left;
        NewNode->rightChild = right;
        leaf.push_back(NewNode);
    }
    node* root = leaf.front();
    map<char, string> code_map;
    generateCode(root, code_map, "");
    for(int i = 0; i < number; i++)
    {
        char curr_data = data[i];
        string code = code_map[curr_data];
        int code_length = code.length();
        double wpl = weight[i] * code_length;
        cout << curr_data << " " << code << " " << code_length << " " << fixed << setprecision(3) << wpl << endl;
    }
    return root;
    
}