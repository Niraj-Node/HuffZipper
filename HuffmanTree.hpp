#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include "Node.hpp"

class HuffmanTree {
private:
    std::vector<std::shared_ptr<Node>> arr;
    std::shared_ptr<Node> root;
    
    // custom comparator for the priority_queue minHeap
    class Cmp {
        public:
            // This ensures that the priority queue maintains the order of nodes with the lowest frequency at the top        
            bool operator() (const std::shared_ptr<Node>& l, const std::shared_ptr<Node>& r) {
                return l->freq > r->freq;
            }
    };
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, Cmp> minHeap;

    std::fstream openFile(const std::string &fileName, std::ios::openmode mode);
    void initializeFrequencyArray();
    void calculateFrequency(const std::string& inFileName);
    void buildMinHeap();
    void buildTree();
    void assignCodes(std::shared_ptr<Node> node, const std::string& str);
    void generateCodes();
    void saveTreeStructure(const std::string& outFileName);
    std::string encodeInputFile(const std::string& inFileName);
    void saveEncodedFile(const std::string& encodedData, const std::string& outFileName);
    void decodeFileContent(const std::string& inFileName, const std::string& outFileName);

public:
    HuffmanTree();
    void compress(const std::string& inFileName, const std::string& outFileName);
    void decompress(const std::string& inFileName, const std::string& outFileName);
};

#endif // HUFFMAN_TREE_H
