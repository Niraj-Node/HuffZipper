# Huffman Coding Compression and Decompression

This repository contains a C++ implementation of Huffman coding for compressing and decompressing files.

## Important Note:

The implementation currently lacks the completion of the `saveEncodedFile()` and `saveDecodedFile()` functions.

## Compilation

To compile the program, execute the following commands:

```bash
g++ -o compress encode.cpp
g++ -o decompress decode.cpp
```

This will generate the executable files compress and decompress.

## Usage

To compress a file, run the following command:

```bash
./compress input_file output_file
```

To decompress a file, run the following command:

```bash
./decompress compressed_file output_file
```

Replace input_file with the file you want to compress and output_file with the desired name for the compressed/decompressed file.

## Running the Program

Ensure that the necessary input files are available in the directory where the executables (compress and decompress) are located. Run the executables with the appropriate command-line arguments as mentioned in the "Usage" section.

## Description

This repository offers a C++ implementation of Huffman coding, a topic you might already be familiar with from your university studies and potentially from the "Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming" course at Stanford. The huffman.hpp header file contains the Huffman coding implementation using a huffman class with methods for compression `compress()` and decompression `decompress()`. It uses priority queues, file I/O operations, and tree traversal to encode and decode files.

The encode.cpp file contains the main function for compressing a file, while decode.cpp contains the main function for decompressing a file.
