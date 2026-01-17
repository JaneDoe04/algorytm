#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include "HuffmanTree.h"
#include <string>
#include <map>
#include <fstream>

class HuffmanEncoder {
private:
    std::map<char, int> countFrequencies(const std::string& text);
    void writeDictionary(std::ofstream& out, const std::map<char, std::string>& encodingMap, const std::map<char, int>& frequencies);
    
public:
    bool compress(const std::string& inputFile, const std::string& outputFile);
};

#endif
