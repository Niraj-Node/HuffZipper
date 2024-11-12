# HuffZipper

HuffZipper is a simple file compression and decompression program using Huffman coding. It allows users to compress and decompress files interactively.

## Description

This repository offers a C++ implementation of Huffman coding, a topic you might already be familiar with from your university studies and potentially from the "Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming" course at Stanford.

## Features

- **Compression**: Compresses a text file and saves it in a binary encoded format.
- **Decompression**: Decompresses a previously compressed file back to its original content.

## Requirements

- **C++ Compiler**: `g++` or any C++11 (or later) compliant compiler.

## Setup and Compilation

1. **Clone or Download** the repository to your local machine.

2. **Compile the Program**:
    ```bash
    g++ -o HuffZipper main.cpp HuffmanTree.cpp
    ```

    - Here, main.cpp is the main program file, and HuffmanTree.cpp contains the Huffman compression and decompression logic.

    - This will generate the executable file named `HuffZipper`.

## Usage

**Note**: Ensure that the input file exists in the specified path, and you have write permissions for the output file.
The program is designed for ASCII text files.

After compiling, you can run the program directly from the command line. The program will prompt you to enter details interactively.

1. **Run the Program**:
    ```bash
    ./HuffZipper
    ```

2. **Follow the Prompts**:
    - **Enter Mode**: Choose either c for compression or d for decompression.
    - **Enter the Input File Path**: Provide the path to the file you wish to compress or decompress.
    - **Enter the Output File Path**: Provide the path where the output file should be saved.

3. **Compression Example Walkthrough**:
    
    Suppose you have a text file `inputFile.txt` and want to compress it to `example.huff`.

    - Run the program:
        ```bash
        ./HuffZipper
        ```

    - When prompted, enter:
        - Mode: `c`
        - Input file: `inputFile.txt`
        - Output file: `example.huff`

    The program will compress `inputFile.txt` and save it as `example.huff`. You will see a success message.

4. **Decompression Example Walkthrough**:
    
    To decompress `example.huff` back to a text file `outputFile.txt`, run the program again:

    When prompted, enter:
    - Mode: `d`
    - Input file: `example.huff`
    - Output file: `outputFile.txt`

    The program will decompress `example.huff` and save the original content to `output.txt`.