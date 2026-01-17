#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "HuffmanNode.h"
#include "PriorityQueue.h"
#include <string>
#include <map>

class HuffmanTree {
private:
    HuffmanNode* root;
    std::map<char, std::string> encodingMap;
    
    void buildEncodingMap(HuffmanNode* node, const std::string& code);
    void deleteTree(HuffmanNode* node);
    
public:
    HuffmanTree();
    ~HuffmanTree();
    
    void buildTree(const std::map<char, int>& frequencies);
    void buildTreeFromEncodingMap(const std::map<char, std::string>& encodingMap);
    std::map<char, std::string> getEncodingMap() const { return encodingMap; }
    HuffmanNode* getRoot() const { return root; }
    
    std::string encode(const std::string& text);
    std::string decode(const std::string& binaryString);
};

#endif
