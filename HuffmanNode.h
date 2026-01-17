#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <string>

struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char ch, int freq) 
        : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
    
    HuffmanNode(int freq, HuffmanNode* l, HuffmanNode* r)
        : character('\0'), frequency(freq), left(l), right(r) {}
    
    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

int compareHuffmanNodes(HuffmanNode* const& a, HuffmanNode* const& b);

#endif
