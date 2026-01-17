CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = huffman
SOURCES = main.cpp HuffmanNode.cpp HuffmanTree.cpp HuffmanEncoder.cpp HuffmanDecoder.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = PriorityQueue.h HuffmanNode.h HuffmanTree.h HuffmanEncoder.h HuffmanDecoder.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
