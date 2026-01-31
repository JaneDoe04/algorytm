#include "HuffmanDecoder.h"
#include "HuffmanNode.h"
#include <iostream>
#include <bitset>
#include <algorithm>
#include <fstream>
#include <sstream>

std::map<char, std::string> HuffmanDecoder::readDictionary(std::ifstream& in) {
    std::map<char, std::string> encodingMap;
    std::string line;
    
    // Pominięcie linii "SŁOWNIK:"
    if (!std::getline(in, line)) {
        return encodingMap;
    }
    // Ignorujemy sprawdzanie dokładnej treści nagłówka ze względu na kodowanie (UTF-8 vs CP1250)
    // if (line != "SŁOWNIK:") ...
    
    // Czytanie słownika
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        
        // Sprawdź czy to koniec słownika
        if (line == "DANE:") {
            break;
        }
        
        // Parsowanie linii słownika
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
        
        encodingMap[ch] = code_part;
    }
    
    return encodingMap;
}

std::string HuffmanDecoder::binaryToText(const std::string& binaryData, size_t bitLength, int padding) {
    std::string result;
    result.reserve(bitLength);
    (void)padding; // Unused parameter warning fix
    
    for (size_t i = 0; i < binaryData.length(); i++) {
        unsigned char byte = static_cast<unsigned char>(binaryData[i]);
        int bits_to_process = 8;
        
        // Ta funkcja jest używana tylko pomocniczo, główna logika jest w decompress
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
    std::map<std::string, char> reverseMap;
    for (const auto& pair : encodingMap) {
        reverseMap[pair.second] = pair.first;
    }
    
    std::map<char, int> frequencies;
    for (const auto& pair : encodingMap) {
        frequencies[pair.first] = 1;
    }
    
    HuffmanTree* tree = new HuffmanTree();
    tree->buildTree(frequencies);
    
    return tree;
}

bool HuffmanDecoder::decompress(const std::string& inputFile, const std::string& outputFile) {
    // Otwórz binarnie
    std::ifstream in(inputFile, std::ios::in | std::ios::binary);
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
    
    // Jesteśmy po "DANE:". getline zjadł \n po DANE:.
    long data_start_pos = in.tellg();
    
    // Szukamy PADDING od końca pliku
    in.seekg(0, std::ios::end);
    long file_end = in.tellg();
    
    int search_len = 100; // Wystarczy do znalezienia PADDING: X
    if (file_end - data_start_pos < search_len) search_len = file_end - data_start_pos;
    if (search_len <= 0) {
         // Pusty obszar danych
         in.close();
         return false;
    }

    in.seekg(file_end - search_len);
    
    std::string tail;
    tail.resize(search_len);
    in.read(&tail[0], search_len);
    
    size_t padding_idx = tail.rfind("PADDING:");
    if (padding_idx == std::string::npos) {
        std::cerr << "Błąd: Nie znaleziono linii PADDING w pliku!" << std::endl;
        in.close();
        return false;
    }
    
    int padding = std::stoi(tail.substr(padding_idx + 8));
    
    // Oblicz gdzie kończą się dane binarne.
    // tail[padding_idx] to 'P'. Przed nim powinno być \n (lub \r\n).
    long padding_pos_in_file = (file_end - search_len) + padding_idx;
    long data_end_pos = padding_pos_in_file;
    
    // Cofamy się o znak nowej linii przed PADDING
    if (data_end_pos > data_start_pos) {
        // Sprawdźmy co jest przed 'P' w naszym buforze tail, jeśli wystarczy
        if (padding_idx > 0) {
            if (tail[padding_idx - 1] == '\n') {
                data_end_pos--;
                if (padding_idx > 1 && tail[padding_idx - 2] == '\r') {
                    data_end_pos--;
                }
            }
        } else {
            // Musimy doczytać z pliku
            in.seekg(padding_pos_in_file - 1);
            char c;
            if (in.get(c) && c == '\n') {
                data_end_pos--;
                in.seekg(padding_pos_in_file - 2);
                if (in.get(c) && c == '\r') {
                    data_end_pos--;
                }
            }
        }
    }
    
    long bytes_to_read = data_end_pos - data_start_pos;
    if (bytes_to_read < 0) bytes_to_read = 0;
    
    std::string binaryData;
    binaryData.resize(bytes_to_read);
    
    in.seekg(data_start_pos);
    in.read(&binaryData[0], bytes_to_read);
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
