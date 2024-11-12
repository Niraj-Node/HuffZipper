#ifndef NODE_H // Header Guards - Which Prevents file inclusion multiple times
#define NODE_H

#include <memory>
#include <string>

// Node (Customized for Huffman Tree)
struct Node {
    char data;
    unsigned freq;
    std::string code;
    std::shared_ptr<Node> left, right;

    Node(char d = '\0', unsigned f = 0) 
        : data(d), freq(f), left(nullptr), right(nullptr) {}
};

#endif // NODE_H
