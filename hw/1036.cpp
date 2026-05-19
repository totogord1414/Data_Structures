#include <bits/stdc++.h>
using namespace std;
typedef struct huffnode {
    char data; // 值
    struct huffnode * leftChild; // 左子树
    struct huffnode * rightChild; // 右子树
    /* 其他成员变量，细节隐藏不表 */
} HUFFNODE;

string decipherHuffmanCoding(HUFFNODE* head, char cipher[])
{
    string result;
    HUFFNODE* root = head;
    HUFFNODE* curr = head;
    int i = 0;
    while(cipher[i])
    {
        if(cipher[i] == '0')
        {
            curr = curr->leftChild;
        }
        else{
            curr = curr->rightChild;
        }
        if(!curr->leftChild && !curr->rightChild)
        {
            result = result + curr->data;
            curr = root;
        }
        i++;
    }

    return result;
}