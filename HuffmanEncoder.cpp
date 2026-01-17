#include "HuffmanEncoder.h"
#include <iostream>
#include <sstream>
#include <bitset>
#include <fstream>
#include <iomanip>

std::map<char, int> HuffmanEncoder::countFrequencies(const std::string& text) {
    std::map<char, int> frequencies;
    for (char c : text) {
        frequencies[c]++;
    }
    return frequencies;
}

void HuffmanEncoder::writeDictionary(std::ofstream& out, const std::map<char, std::string>& encodingMap, const std::map<char, int>& frequencies) {
    out << "SŁOWNIK:\n";
    
    for (const auto& pair : encodingMap) {
        unsigned char symbol = static_cast<unsigned char>(pair.first);
        std::string code = pair.second;
        int freq = frequencies.at(pair.first);
        
        if (symbol >= 32 && symbol <= 126) {
            out << static_cast<char>(symbol) << ": " << freq << " - " << code << "\n";
        } else if (symbol == ' ') {
            out << "SPACJA: " << freq << " - " << code << "\n";
        } else if (symbol == '\n') {
            out << "ENTER: " << freq << " - " << code << "\n";
        } else if (symbol == '\t') {
            out << "TAB: " << freq << " - " << code << "\n";
        } else {
            out << "\\x" << std::hex << std::uppercase << std::setfill('0') << std::setw(2) 
                << static_cast<int>(symbol) << std::dec << ": " << freq << " - " << code << "\n";
        }
    }
}

bool HuffmanEncoder::compress(const std::string& inputFile, const std::string& outputFile) {
    // Wczytaj plik wejściowy
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Błąd: Nie można otworzyć pliku wejściowego: " << inputFile << std::endl;
        return false;
    }
    
    // Wczytaj całą zawartość pliku
    std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
    
    if (text.empty()) {
        std::cerr << "Błąd: Plik wejściowy jest pusty!" << std::endl;
        return false;
    }
    
    // Policz częstotliwości
    std::map<char, int> frequencies = countFrequencies(text);
    
    // Zbuduj drzewo Huffmana
    HuffmanTree tree;
    tree.buildTree(frequencies);
    
    // Pobierz mapę kodowania
    std::map<char, std::string> encodingMap = tree.getEncodingMap();
    
    // Otwórz plik wyjściowy w trybie tekstowym (jak u ziomka)
    std::ofstream out(outputFile, std::ios::out);
    if (!out.is_open()) {
        std::cerr << "Błąd: Nie można utworzyć pliku wyjściowego: " << outputFile << std::endl;
        return false;
    }
    
    // Zapisz słownik (część 1)
    writeDictionary(out, encodingMap, frequencies);
    
    // Zapisz nagłówek danych
    out << "DANE:\n";
    
    int bit_buffer = 0;
    int bit_count = 0;
    
    for (char ch : text) {
        const std::string& code = encodingMap[ch];
        
        for (char bit_char : code) {
            bit_buffer = (bit_buffer << 1) | (bit_char - '0');
            bit_count++;
            
            if (bit_count == 8) {
                out << static_cast<unsigned char>(bit_buffer);
                bit_buffer = 0;
                bit_count = 0;
            }
        }
    }
    
    int padding = 0;
    if (bit_count > 0) {
        padding = 8 - bit_count;
        bit_buffer <<= padding;
        out << static_cast<unsigned char>(bit_buffer);
    }
    out << "\nPADDING: " << padding << "\n";
    
    out.close();
    
    return true;
}
