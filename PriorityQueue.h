#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

template<typename T>
class PriorityQueue {
private:
    std::vector<T> heap;
    int (*compare)(const T&, const T&);
    
    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = parent(index);
            if (compare(heap[index], heap[parentIndex]) < 0) {
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }
    
    void heapifyDown(int index) {
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);
        
        if (left < (int)heap.size() && compare(heap[left], heap[smallest]) < 0) {
            smallest = left;
        }
        
        if (right < (int)heap.size() && compare(heap[right], heap[smallest]) < 0) {
            smallest = right;
        }
        
        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    
    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }
    
public:
    PriorityQueue(int (*comp)(const T&, const T&)) : compare(comp) {}
    
    ~PriorityQueue() {
        heap.clear();
    }
    
    // Główne operacje
    void add(const T& element) {
        heap.push_back(element);
        heapifyUp(heap.size() - 1);
    }
    
    T remove() {
        if (heap.empty()) {
            throw std::runtime_error("Kolejka jest pusta!");
        }
        
        T root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return root;
    }
    
    void decreasePriority(int index, const T& newValue) {
        if (index < 0 || index >= (int)heap.size()) {
            throw std::runtime_error("Nieprawidłowy indeks!");
        }
        
        if (compare(newValue, heap[index]) > 0) {
            throw std::runtime_error("Nowa wartość nie jest mniejsza od obecnej!");
        }
        
        heap[index] = newValue;
        heapifyUp(index);
    }
    
    void buildFromArray(const std::vector<T>& array) {
        heap = array;
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }
    
    bool isEmpty() const {
        return heap.empty();
    }
    
    // Pomocnicze
    int size() const { return heap.size(); }
    
    T peek() const {
        if (heap.empty()) {
            throw std::runtime_error("Kolejka jest pusta!");
        }
        return heap[0];
    }
    
    void display() const {
        if (heap.empty()) {
            std::cout << "Kolejka jest pusta.\n";
            return;
        }
        
        std::cout << "Zawartość kolejki priorytetowej:\n";
        for (size_t i = 0; i < heap.size(); i++) {
            std::cout << "[" << i << "] ";
            std::cout << "\n";
        }
    }
    
    void clear() {
        heap.clear();
    }
};

#endif
