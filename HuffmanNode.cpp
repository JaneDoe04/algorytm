#include "HuffmanNode.h"

int compareHuffmanNodes(HuffmanNode* const& a, HuffmanNode* const& b) {
    if (a->frequency < b->frequency) return -1;
    if (a->frequency > b->frequency) return 1;
    return 0;
}
