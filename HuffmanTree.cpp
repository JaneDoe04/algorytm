#include "HuffmanTree.h"
#include "PriorityQueue.h"
#include "HuffmanNode.h"
#include <vector>
#include <queue>

HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::~HuffmanTree() {
    deleteTree(root);
}

void HuffmanTree::deleteTree(HuffmanNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void HuffmanTree::buildTree(const std::map<char, int>& frequencies) {
    deleteTree(root);
    root = nullptr;
    encodingMap.clear();
    
    if (frequencies.empty()) {
        return;
    }
    
    if (frequencies.size() == 1) {
        auto it = frequencies.begin();
        root = new HuffmanNode(it->first, it->second);
        encodingMap[it->first] = "0";
        return;
    }
    
    // Zamiast dodawać pojedynczo, tworzymy wektor i budujemy kolejkę w czasie liniowym O(n)
    std::vector<HuffmanNode*> nodes;
    nodes.reserve(frequencies.size());
    for (const auto& pair : frequencies) {
        nodes.push_back(new HuffmanNode(pair.first, pair.second));
    }
    
    PriorityQueue<HuffmanNode*> pq(compareHuffmanNodes);
    pq.buildFromArray(nodes);
    
    while (pq.size() > 1) {
        HuffmanNode* left = pq.remove();
        HuffmanNode* right = pq.remove();
        
        int combinedFreq = left->frequency + right->frequency;
        HuffmanNode* merged = new HuffmanNode(combinedFreq, left, right);
        
        pq.add(merged);
    }
    
    root = pq.remove();
    
    buildEncodingMap(root, "");
}

void HuffmanTree::buildEncodingMap(HuffmanNode* node, const std::string& code) {
    if (node == nullptr) return;
    
    if (node->isLeaf()) {
        encodingMap[node->character] = code.empty() ? "0" : code;
    } else {
        buildEncodingMap(node->left, code + "0");
        buildEncodingMap(node->right, code + "1");
    }
}

void HuffmanTree::buildTreeFromEncodingMap(const std::map<char, std::string>& encodingMap) {
    deleteTree(root);
    root = nullptr;
    this->encodingMap = encodingMap;
    
    if (encodingMap.empty()) {
        return;
    }
    
    if (encodingMap.size() == 1) {
        auto it = encodingMap.begin();
        root = new HuffmanNode(it->first, 1);
        return;
    }
    
    root = new HuffmanNode(0, nullptr, nullptr);
    
    for (const auto& pair : encodingMap) {
        char symbol = pair.first;
        const std::string& code = pair.second;
        
        HuffmanNode* current = root;
        for (size_t i = 0; i < code.length(); i++) {
            if (code[i] == '0') {
                if (current->left == nullptr) {
                    if (i == code.length() - 1) {
                        current->left = new HuffmanNode(symbol, 1);
                    } else {
                        current->left = new HuffmanNode(0, nullptr, nullptr);
                    }
                }
                current = current->left;
            } else if (code[i] == '1') {
                if (current->right == nullptr) {
                    if (i == code.length() - 1) {
                        current->right = new HuffmanNode(symbol, 1);
                    } else {
                        current->right = new HuffmanNode(0, nullptr, nullptr);
                    }
                }
                current = current->right;
            }
        }
    }
}

std::string HuffmanTree::encode(const std::string& text) {
    std::string result;
    for (char c : text) {
        if (encodingMap.find(c) != encodingMap.end()) {
            result += encodingMap.at(c);
        }
    }
    return result;
}

std::string HuffmanTree::decode(const std::string& binaryString) {
    if (root == nullptr) return "";
    
    std::string result;
    HuffmanNode* current = root;
    
    for (char bit : binaryString) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }
        
        if (current == nullptr) {
            return ""; // Błąd dekodowania
        }
        
        if (current->isLeaf()) {
            result += current->character;
            current = root;
        }
    }
    
    return result;
}
