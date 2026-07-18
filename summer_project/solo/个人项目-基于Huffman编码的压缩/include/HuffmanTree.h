#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <string>
#include <vector>

struct HuffmanNode {
    unsigned char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(unsigned char d, int f) {
        data = d;
        freq = f;
    }
};

struct CompareNode{
    bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2) {
        if (n1->freq == n2->freq) {
            return n1->data > n2->data;
        }

        return n1->freq > n2->freq;
    }
};

class HuffmanTree {
public:
    HuffmanTree();
    ~HuffmanTree();

    void buildTree(const std::vector<int>& frenquencies);

    std::vector<std::string> getCodes() const;
private:

    HuffmanNode* root;
    std::vector<std::string> codes;

    void generateCodesRecursive(HuffmanNode* node, std::string currentNode);

    void freeTree(HuffmanNode* node);
};

#endif