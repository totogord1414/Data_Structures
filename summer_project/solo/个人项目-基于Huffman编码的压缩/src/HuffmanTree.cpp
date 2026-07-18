#include "HuffmanTree.h"
#include <queue>

HuffmanTree::HuffmanTree() {
    root = nullptr;
    codes.resize(256, "");
}

HuffmanTree::~HuffmanTree() {
    HuffmanTree::freeTree(root);
}

void HuffmanTree::freeTree(HuffmanNode* node) {
    if (node == nullptr) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);

    delete node;
}

std::vector<std::string> HuffmanTree::getCodes() const {
    return codes;
}

void HuffmanTree::buildTree(const std::vector<int>& frenquencies) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> minHeap;
    
    for (int i = 0; i < 256; i++) {
        int freq = frenquencies[i];
        if (freq > 0) {
            HuffmanNode* newNode = new HuffmanNode(i, freq);
            minHeap.push(newNode);
        }
    }

    while (minHeap.size() > 1) {
        HuffmanNode* leftNode = minHeap.top();
        minHeap.pop();
        HuffmanNode* rightNode = minHeap.top();
        minHeap.pop();
        
        HuffmanNode* newNode = new HuffmanNode(leftNode->data, leftNode->freq + rightNode->freq);
        newNode->left = leftNode;
        newNode->right = rightNode;
        minHeap.push(newNode);
    }
    //in case the whole file is empty
    if (minHeap.empty()) {
        return;
    }

    root = minHeap.top();

    generateCodesRecursive(root, "");
}

void HuffmanTree::generateCodesRecursive(HuffmanNode* node, std::string currentCode) {
    if (node == nullptr) {
        return;
    }
    if (node->left == nullptr && node->right == nullptr) {
        codes[node->data] = currentCode;
        return;
    }
    generateCodesRecursive(node->left, currentCode + "0");
    generateCodesRecursive(node->right, currentCode + "1");

}