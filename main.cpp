#include <iostream>
#include <string>
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"
#include "PriorityQueue.h"
#include "HuffmanNode.h"
#include <vector>

// Funkcja do demonstracji kolejki priorytetowej
void demonstratePriorityQueue() {
    std::cout << "\n=== DEMONSTRACJA KOLEJKI PRIORYTETOWEJ ===\n\n";
    
    PriorityQueue<HuffmanNode*> pq(compareHuffmanNodes);
    
    std::vector<HuffmanNode*> nodes;
    nodes.push_back(new HuffmanNode('a', 5));
    nodes.push_back(new HuffmanNode('b', 9));
    nodes.push_back(new HuffmanNode('c', 12));
    nodes.push_back(new HuffmanNode('d', 13));
    nodes.push_back(new HuffmanNode('e', 16));
    nodes.push_back(new HuffmanNode('f', 45));
    
    std::cout << "1. Budowanie kolejki z tablicy:\n";
    std::cout << "   Dodaje wezly: a(5), b(9), c(12), d(13), e(16), f(45)\n";
    pq.buildFromArray(nodes);
    
    std::cout << "\n2. Sprawdzanie czy kolejka jest pusta:\n";
    std::cout << "   Kolejka jest pusta: " << (pq.isEmpty() ? "TAK" : "NIE") << "\n";
    
    std::cout << "\n3. Wyswietlanie kolejki:\n";
    std::cout << "   Rozmiar kolejki: " << pq.size() << "\n";
    std::cout << "   Element o najwyzszym priorytecie (najmniejsza czestotliwosc): ";
    HuffmanNode* top = pq.peek();
    std::cout << top->character << "(" << top->frequency << ")\n";
    
    std::cout << "\n4. Usuwanie elementow z kolejki:\n";
    while (!pq.isEmpty()) {
        HuffmanNode* node = pq.remove();
        std::cout << "   Usunieto: " << node->character << "(" << node->frequency << ")\n";
    }
    
    std::cout << "\n5. Dodawanie elementow do kolejki:\n";
    pq.add(new HuffmanNode('x', 3));
    pq.add(new HuffmanNode('y', 7));
    pq.add(new HuffmanNode('z', 1));
    std::cout << "   Dodano: x(3), y(7), z(1)\n";
    std::cout << "   Element o najwyzszym priorytecie: ";
    top = pq.peek();
    std::cout << top->character << "(" << top->frequency << ")\n";
    
    std::cout << "\n6. Zmniejszanie priorytetu:\n";
    HuffmanNode* node = pq.remove();
    std::cout << "   Usunieto: " << node->character << "(" << node->frequency << ")\n";
    node->frequency = 0;
    pq.add(node);
    std::cout << "   Zmieniono priorytet i dodano z powrotem: " << node->character << "(" << node->frequency << ")\n";
    std::cout << "   Nowy element o najwyzszym priorytecie: ";
    top = pq.peek();
    std::cout << top->character << "(" << top->frequency << ")\n";
    
    while (!pq.isEmpty()) {
        delete pq.remove();
    }
    for (HuffmanNode* node : nodes) {
        delete node;
    }
    
    std::cout << "\n=== KONIEC DEMONSTRACJI ===\n\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "  Program kompresji/dekompresji Huffmana\n";
    std::cout << "========================================\n\n";
    
    int choice;
    std::string inputFile, outputFile;
    
    while (true) {
        std::cout << "Wybierz opcję:\n";
        std::cout << "1. Kompresja pliku\n";
        std::cout << "2. Dekompresja pliku\n";
        std::cout << "3. Demonstracja kolejki priorytetowej\n";
        std::cout << "4. Wyjście\n";
        std::cout << "Twój wybór: ";
        
        std::cin >> choice;
        
        if (choice == 1) {
            std::cout << "\nPodaj nazwę pliku do skompresowania: ";
            std::cin >> inputFile;
            std::cout << "Podaj nazwę pliku wyjściowego (skompresowanego): ";
            std::cin >> outputFile;
            
            HuffmanEncoder encoder;
            if (encoder.compress(inputFile, outputFile)) {
                std::cout << "Kompresja zakończona pomyślnie!\n\n";
            } else {
                std::cout << "Błąd podczas kompresji!\n\n";
            }
            
        } else if (choice == 2) {
            std::cout << "\nPodaj nazwę pliku do zdekompresowania: ";
            std::cin >> inputFile;
            std::cout << "Podaj nazwę pliku wyjściowego (zdekompresowanego): ";
            std::cin >> outputFile;
            
            HuffmanDecoder decoder;
            if (decoder.decompress(inputFile, outputFile)) {
                std::cout << "Dekompresja zakończona pomyślnie!\n\n";
            } else {
                std::cout << "Błąd podczas dekompresji!\n\n";
            }
            
        } else if (choice == 3) {
            demonstratePriorityQueue();
            
        } else if (choice == 4) {
            std::cout << "Do widzenia!\n";
            break;
            
        } else {
            std::cout << "Nieprawidłowy wybór! Spróbuj ponownie.\n\n";
        }
    }
    
    return 0;
}
