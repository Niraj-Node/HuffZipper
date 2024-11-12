#include <iostream>
#include "huffman.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Failed to detect Files";
		exit(1);
	}
    
    huffman f;
    f.compress(argv[1], argv[2]);
    cout << "Compressed successfully" << endl;
    
    return 0;
}