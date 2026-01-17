#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H

#include "HuffmanTree.h"
#include <string>
#include <map>
#include <fstream>

class HuffmanDecoder {
private:
    std::map<char, std::string> readDictionary(std::ifstream& in);
    std::string binaryToText(const std::string& binaryData, size_t bitLength, int padding);
    HuffmanTree* buildTreeFromDictionary(const std::map<char, std::string>& encodingMap);
    
public:
    bool decompress(const std::string& inputFile, const std::string& outputFile);
};

#endif
