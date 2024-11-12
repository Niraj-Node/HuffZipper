#include <iostream>
#include "HuffmanTree.hpp"

int main() {
    std::string mode, inputFile, outputFile;
    
    // Prompt the user for mode
    std::cout << "Enter mode ('c' for compress, 'd' for decompress): ";
    std::cin >> mode;

    // Validate mode input
    if (mode != "c" && mode != "d") {
        std::cerr << "Invalid mode. Please enter 'c' for compression or 'd' for decompression.\n";
        return 1;
    }

    // Prompt the user for input and output file paths
    std::cout << "Enter the input file path (leave blank for default 'inputFile.txt' or 'example.huff'): ";
    std::cin.ignore();  // Clear newline from mode input
    std::getline(std::cin, inputFile);

    std::cout << "Enter the output file path (leave blank for default 'example.huff' or 'outputFile.txt'): ";
    std::getline(std::cin, outputFile);

    // Set default names if user input is empty
    if (inputFile.empty()) {
        inputFile = (mode == "c") ? "inputFile.txt" : "example.huff";
    }
    if (outputFile.empty()) {
        outputFile = (mode == "c") ? "example.huff" : "outputFile.txt";
    }

    HuffmanTree huffman;

    if (mode == "c") {
        std::cout << "Compressing file: " << inputFile << " -> " << outputFile << std::endl;
        huffman.compress(inputFile, outputFile);
        std::cout << "File compressed successfully!" << std::endl;
    } else if (mode == "d") {
        std::cout << "Decompressing file: " << inputFile << " -> " << outputFile << std::endl;
        huffman.decompress(inputFile, outputFile);
        std::cout << "File decompressed successfully!" << std::endl;
    }

    return 0;
}
