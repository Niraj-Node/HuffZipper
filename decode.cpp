#include <iostream>
#include "huffman.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Failed to detect Files";
		exit(1);
	}

    Huffman f;
    f.decompress(argv[1], argv[2]);
    cout << "Decompressed successfully" << endl;

    return 0;
}