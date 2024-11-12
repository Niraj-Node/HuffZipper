#include "HuffmanTree.hpp"

// Helper function to open a file with error handling
std::fstream HuffmanTree::openFile(const std::string &fileName, std::ios::openmode mode) {
    std::fstream file(fileName, mode);
    if (!file) {
        std::cerr << "Error: Unable to open file " << fileName << "!" << std::endl;
        exit(1);
    }
    return file;
}

// Initialize frequency array with 128 nodes for ASCII characters
void HuffmanTree::initializeFrequencyArray() {
    arr.resize(128);
    for(int i = 0; i < 128; ++i)
        arr[i] = std::make_shared<Node>(static_cast<char>(i));
}

// Calculate frequency of characters in the input file
void HuffmanTree::calculateFrequency(const std::string& inFileName) {
    std::fstream inFile = openFile(inFileName, std::ios::in);
    char ch;
    while (inFile.get(ch)) {
        arr[static_cast<unsigned char>(ch)]->freq++;
    }
    inFile.close();
}

// Build min-heap of nodes with non-zero frequencies characters in the input file
void HuffmanTree::buildMinHeap() {
    for (const auto& node : arr) {
        if (node->freq > 0)
            minHeap.push(node);
    }
}

// Build Huffman tree from min-heap
void HuffmanTree::buildTree() {
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, Cmp> tempPQ(minHeap);
    while (tempPQ.size() > 1) {
        auto left = tempPQ.top(); tempPQ.pop();
        auto right = tempPQ.top(); tempPQ.pop();
        auto newNode = std::make_shared<Node>('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        tempPQ.push(newNode);
    }
    root = tempPQ.top();
}
// Assign codes to characters by Recursively traversing the constructed tree 
void HuffmanTree::assignCodes(std::shared_ptr<Node> node, const std::string& str) {
    if (!node) return;
    if (!node->left && !node->right) {
        node->code = str;
        return;
    }
    assignCodes(node->left, str + '0');
    assignCodes(node->right, str + '1');
}
// Function to generate Huffman codes
void HuffmanTree::generateCodes() {
    buildTree();
    assignCodes(root, ""); // Traversing the Huffman Tree and assigning specific codes to each character as leaf node
}

// Save Huffman tree structure or metadata at the beginning of the file
void HuffmanTree::saveTreeStructure(const std::string& outFileName) {
    std::fstream outFile = openFile(outFileName, std::ios::out | std::ios::binary);
    for (const auto& node : arr) {
        if (node->freq > 0) {
            // Escape special characters
            if (node->data == '\n') {
                outFile << "\\n " << node->freq << '\n';
            } else if (node->data == '\t') {
                outFile << "\\t " << node->freq << '\n';
            } else if (node->data == '\r') {
                outFile << "\\r " << node->freq << '\n';
            } else if (node->data == ' ') {
                outFile << "\\s " << node->freq << '\n';
            } else if (node->data == '\\') {
                outFile << "\\\\ " << node->freq << '\n';
            } else {
                outFile << node->data << ' ' << node->freq << '\n';
            }
        }
    }
    outFile << "@END\n"; // Marking the end of the tree structure
    outFile.close();
}

// Encode the input file using Huffman codes
std::string HuffmanTree::encodeInputFile(const std::string& inFileName) {
    std::string encodedData;
    std::fstream inFile = openFile(inFileName, std::ios::in);
    char ch;
    while (inFile.get(ch)) {
        encodedData += arr[static_cast<unsigned char>(ch)]->code;
    }
    inFile.close();
    return encodedData;
}

// Save encoded data to file
void HuffmanTree::saveEncodedFile(const std::string& encodedData, const std::string& outFileName) {
    std::fstream outFile = openFile(outFileName, std::ios::app | std::ios::binary);
    int padding = (8 - encodedData.size() % 8) % 8; // Calculate padding and store it as a single character
    outFile << padding << '\n';
    unsigned char byte = 0;
    int bitCount = 0;
    // Convert the string of bits to actual bytes and write them to the output file
    for (char bit : encodedData) { 
        byte = (byte << 1) | (bit - '0');
        bitCount++;
        if (bitCount == 8) {
            outFile.put(byte);
            byte = 0;
            bitCount = 0;
        }
    }
    // If there are leftover bits, pad them to 8 bits and write
    if (bitCount > 0) {
        byte <<= (8 - bitCount);
        outFile.put(byte);
    }
    outFile.close();
}

// Decode the input file and save the decompressed data to the output file
void HuffmanTree::decodeFileContent(const std::string& inFileName, const std::string& outFileName) {
    std::fstream inFile = openFile(inFileName, std::ios::in | std::ios::binary);

    // Step 1: Reconstruct the Huffman tree using metadata from the file
    std::string line;
    while (std::getline(inFile, line)) {
        if (line == "@END") break; // End marker for the metadata section
        std::istringstream iss(line);
        std::string dataStr;
        unsigned freq;
        iss >> dataStr >> freq;
        // Handle escaped characters
        char ch;
        if (dataStr == "\\n") {
            ch = '\n';
        } else if (dataStr == "\\t") {
            ch = '\t';
        } else if (dataStr == "\\r") {
            ch = '\r';
        } else if (dataStr == "\\s") {
            ch = ' ';
        } else if (dataStr == "\\\\") {
            ch = '\\';
        } else {
            ch = dataStr[0];
        }

        arr[ch]->freq = freq;
        minHeap.push(arr[ch]);
    }
    buildTree(); // Rebuild the Huffman tree based on frequencies

    // Step 2: Read the padding information
    int padding;
    inFile >> padding;
    inFile.get(); // Move to the next line after padding info

    // Step 3: Decode the encoded binary data
    std::shared_ptr<Node> currentNode = root;
    std::string decodedText;
    unsigned char byte;

    // Read the binary data and decode it bit-by-bit
    while (inFile.read(reinterpret_cast<char*>(&byte), 1)) {
        // Process each bit in the byte, stopping for padding at the last byte
        for (int i = 7; i >= 0; --i) {
            // Stop if we're in the last byte and padding bits are reached
            if (inFile.peek() == EOF && i < padding) break;

            bool bit = byte & (1 << i);
            currentNode = bit ? currentNode->right : currentNode->left;

            // Append character when a leaf node is reached, then reset to root
            if (!currentNode->left && !currentNode->right) {
                decodedText += currentNode->data;
                currentNode = root;
            }
        }
    }
    inFile.close();

    // Step 4: Write the decoded text to the output file
    std::fstream outFile = openFile(outFileName, std::ios::out);
    outFile << decodedText;
    outFile.close();
}

// Constructor initializes frequency array
HuffmanTree::HuffmanTree() {
    initializeFrequencyArray();
}

// Public function to compress a file
void HuffmanTree::compress(const std::string& inFileName, const std::string& outFileName) {
    calculateFrequency(inFileName);
    buildMinHeap();
    generateCodes();
    saveTreeStructure(outFileName);
    std::string encodedData = encodeInputFile(inFileName);
    saveEncodedFile(encodedData, outFileName);
}

// Public function to decompress a file
void HuffmanTree::decompress(const std::string& inFileName, const std::string& outFileName) {
    decodeFileContent(inFileName, outFileName);
}
