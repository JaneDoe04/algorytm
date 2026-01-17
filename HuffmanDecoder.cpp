#include "HuffmanDecoder.h"
#include <iostream>
#include <bitset>
#include <algorithm>
#include <fstream>
#include <sstream>

std::map<char, std::string> HuffmanDecoder::readDictionary(std::ifstream& in) {
    std::map<char, std::string> encodingMap;
    std::string line;
    
    if (!std::getline(in, line) || line != "SŁOWNIK:") {
        return encodingMap;
    }
    
    while (std::getline(in, line)) {
        if (line == "DANE:") {
            break;
        }
        
        size_t colon_pos = line.find(':');
        if (colon_pos == std::string::npos) continue;
        
        size_t dash_pos = line.find('-', colon_pos);
        if (dash_pos == std::string::npos) continue;
        
        std::string char_part = line.substr(0, colon_pos);
        unsigned char ch;
        
        if (char_part == "SPACJA") {
            ch = ' ';
        } else if (char_part == "ENTER") {
            ch = '\n';
        } else if (char_part == "TAB") {
            ch = '\t';
        } else if (char_part.length() >= 3 && char_part.substr(0, 2) == "\\x") {
            int hex_val;
            std::istringstream hex_stream(char_part.substr(2));
            hex_stream >> std::hex >> hex_val;
            ch = static_cast<unsigned char>(hex_val);
        } else {
            ch = static_cast<unsigned char>(char_part[0]);
        }
        
        std::string code_part = line.substr(dash_pos + 1);
        size_t start = code_part.find_first_not_of(" \t");
        if (start != std::string::npos) {
            code_part = code_part.substr(start);
        }
        if (!code_part.empty() && code_part.back() == '\r') {
            code_part.pop_back();
        }
        if (!code_part.empty() && code_part.back() == '\n') {
            code_part.pop_back();
        }
        
        encodingMap[ch] = code_part;
    }
    
    return encodingMap;
}

std::string HuffmanDecoder::binaryToText(const std::string& binaryData, size_t bitLength, int padding) {
    std::string result;
    result.reserve(bitLength);
    
    for (size_t i = 0; i < binaryData.length(); i++) {
        unsigned char byte = static_cast<unsigned char>(binaryData[i]);
        int bits_to_process = 8;
        
        // Ostatni bajt - uwzględnij padding
        if (i == binaryData.length() - 1 && padding > 0) {
            bits_to_process = 8 - padding;
        }
        
        for (int j = 7; j >= (8 - bits_to_process); j--) {
            if (result.length() < bitLength) {
                if (byte & (1 << j)) {
                    result += '1';
                } else {
                    result += '0';
                }
            }
        }
    }
    
    return result;
}

HuffmanTree* HuffmanDecoder::buildTreeFromDictionary(const std::map<char, std::string>& encodingMap) {
    // Utwórz odwrotną mapę: kod -> symbol
    std::map<std::string, char> reverseMap;
    for (const auto& pair : encodingMap) {
        reverseMap[pair.second] = pair.first;
    }
    
    // Zbuduj drzewo rekurencyjnie
    // Najpierw musimy zbudować mapę częstotliwości (używamy 1 dla każdego symbolu)
    std::map<char, int> frequencies;
    for (const auto& pair : encodingMap) {
        frequencies[pair.first] = 1;
    }
    
    HuffmanTree* tree = new HuffmanTree();
    tree->buildTree(frequencies);
    
    return tree;
}

bool HuffmanDecoder::decompress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::in);
    if (!in.is_open()) {
        std::cerr << "Błąd: Nie można otworzyć pliku wejściowego: " << inputFile << std::endl;
        return false;
    }
    
    std::map<char, std::string> encodingMap = readDictionary(in);
    
    if (encodingMap.empty()) {
        std::cerr << "Błąd: Nie można wczytać słownika!" << std::endl;
        in.close();
        return false;
    }
    
    long data_start_pos = in.tellg();
    
    std::string line;
    long padding_pos = -1;
    int padding = 0;
    
    while (std::getline(in, line)) {
        if (line.find("PADDING:") == 0) {
            padding_pos = in.tellg();
            size_t space_pos = line.find(' ');
            if (space_pos != std::string::npos) {
                padding = std::stoi(line.substr(space_pos + 1));
            }
            break;
        }
    }
    
    if (padding_pos == -1) {
        std::cerr << "Błąd: Nie znaleziono linii PADDING w pliku!" << std::endl;
        in.close();
        return false;
    }
    
    in.seekg(data_start_pos);
    
    long bytes_to_read = padding_pos - data_start_pos - 1;
    
    std::string binaryData;
    binaryData.reserve(bytes_to_read);
    
    long bytes_read = 0;
    char byte;
    while (bytes_read < bytes_to_read && in.get(byte)) {
        binaryData += byte;
        bytes_read++;
    }
    
    in.close();
    
    std::map<std::string, char> reverseMap;
    for (const auto& pair : encodingMap) {
        reverseMap[pair.second] = pair.first;
    }
    
    std::string decodedText;
    std::string current_code;
    
    for (size_t i = 0; i < binaryData.length(); i++) {
        unsigned char byte = static_cast<unsigned char>(binaryData[i]);
        
        int bits_to_process = 8;
        if (i == binaryData.length() - 1 && padding > 0) {
            bits_to_process = 8 - padding;
        }
        
        for (int j = 7; j >= (8 - bits_to_process); j--) {
            int bit = (byte >> j) & 1;
            current_code += (bit + '0');
            
            if (reverseMap.find(current_code) != reverseMap.end()) {
                decodedText += reverseMap[current_code];
                current_code.clear();
            }
        }
    }
    
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) {
        std::cerr << "Błąd: Nie można utworzyć pliku wyjściowego: " << outputFile << std::endl;
        return false;
    }
    
    out.write(decodedText.c_str(), decodedText.length());
    out.close();
    
    return true;
}
