#ifndef HUFFMAN_H //Header Guards - Which Prevents file inclusion multiple times
#define HUFFMAN_H
#include <bits/stdc++.h>
using namespace std;

// Node (Customized for Huffman Tree)
struct Node 
{
    char data;
    unsigned freq;
    string code;
    Node *left, *right;

    Node() {
        left = right = NULL;
        data = '\0';
        freq = 0;
        code = "";
    }
};

class huffman 
{
    private:
        fstream openFile(const string &fileName, ios::openmode mode) {
            fstream file(fileName, mode);
            if (!file) {
                cerr << "Error: Unable to open file " << fileName << "!" << endl;
                exit(1);
            }
            return file;
        }

        vector<Node*> arr;
        Node* root = NULL;
        
        // custom comparator for the priority_queue minHeap
        class Cmp
        {
            public:
                // This ensures that the priority queue maintains the order of nodes with the lowest frequency at the top
                bool operator() (Node* l, Node* r)
                {
                    return l->freq > r->freq;
                }
        };
        priority_queue<Node*, vector<Node*>, Cmp> minHeap;
        
        // Initializing a vector representing character's ascii value and its frequency with 0
        void createArr(string inFileName) 
        {
            for(int i = 0; i < 128; i++) 
            {
                arr.push_back(new Node());
                arr[i]->data = i;
                arr[i]->freq = 0;
            }

            fstream inFile = openFile(inFileName, ios::in);
            char id;
            inFile.get(id);
            while(!inFile.eof()) 
            {
                arr[id]->freq++;
                inFile.get(id);
            }
            inFile.close();
        }
        
        // Populating Min Heap by inserting Nodes of characters which appears in the input file
        void createMinHeap() 
        {
            for(int i = 0; i < 128; i++) 
            {
                if(arr[i]->freq > 0)
                    minHeap.push(arr[i]);
            }
        }
        void createTree() 
        {
            createMinHeap();
            Node *left, *right;
            priority_queue <Node*, vector<Node*>, Cmp> tempPQ(minHeap);
            while(tempPQ.size() != 1)
            {
                left = tempPQ.top();
                tempPQ.pop();
                    
                right = tempPQ.top();
                tempPQ.pop();
                    
                root = new Node();
                root->left = left;
                root->right = right;
                root->freq = left->freq + right->freq;

                tempPQ.push(root);
            }
        }

        // Traversing the constructed tree to generate huffman codes of each present character
        void traverse(Node* r, string str) 
        {
            if(r->left == NULL && r->right == NULL) 
            {
                r->code = str;
                return;
            }

            if(r->left) traverse(r->left, str + '0');
            if(r->right) traverse(r->right, str + '1');
        }
        // Generating Huffman codes
        void assignHCodes() {
            // Traversing the Huffman Tree and assigning specific codes to each character as leaf node
            traverse(root, "");
        }

        // Save tree structure and metadata at the beginning of the file
        void saveTreeStructure(string outFileName) 
        {
            fstream outFile = openFile(outFileName, ios::out | ios::binary);

            // Write tree metadata to the file (character and its frequency)
            for(int i = 0; i < 128; i++) 
            {
                if(arr[i]->freq > 0) 
                {
                    // Escape special characters
                    if (arr[i]->data == '\n') {
                        outFile << "\\n " << arr[i]->freq << '\n';
                    } else if (arr[i]->data == '\t') {
                        outFile << "\\t " << arr[i]->freq << '\n';
                    } else if (arr[i]->data == '\r') {
                        outFile << "\\r " << arr[i]->freq << '\n';
                    } else if (arr[i]->data == ' ') {
                        outFile << "\\s " << arr[i]->freq << '\n';
                    } else if (arr[i]->data == '\\') {
                        outFile << "\\\\ " << arr[i]->freq << '\n';
                    } else {
                        outFile << arr[i]->data << ' ' << arr[i]->freq << '\n';
                    }
                }
            }
            outFile << "@!#$END_MARKER$#@!\n";  // Marking the end of the tree structure
            outFile.close();
        }
        // Encode the input file
        string encodeFile(string inFileName) 
        {
            fstream inFile = openFile(inFileName, ios::in);
            string encodedData = "";
            char ch;
            while (inFile.get(ch)) {
                encodedData += arr[ch]->code;
            }
            inFile.close();
            return encodedData;
        }
        // Convert the string of bits to actual bytes and write them to the output file
        void saveEncodedFile(const string& encodedData, string outFileName) 
        {
            fstream outFile = openFile(outFileName, ios::app | ios::binary);
            
            // Calculate padding and store it
            int padding = (8 - encodedData.size() % 8) % 8;
            outFile << padding << '\n';  // Write padding info as a single character
            
            unsigned char byte = 0;
            int bitCount = 0;
            for(char bit : encodedData) 
            {
                byte = (byte << 1) | (bit - '0');
                bitCount++;

                // If we have 8 bits, write them as a byte
                if(bitCount == 8) {
                    outFile.put(byte);
                    byte = 0;
                    bitCount = 0;
                }
            }

            // If there are leftover bits, pad them to 8 bits and write
            if(bitCount > 0) {
                byte = byte << (8 - bitCount);
                outFile.put(byte);
            }

            outFile.close();
        }
        // Encode the input file and save the compressed data to the output file
        void encodeAndSaveFile(string inFileName, string outFileName) {
            saveTreeStructure(outFileName);
            string encodedData = encodeFile(inFileName);
            saveEncodedFile(encodedData, outFileName);
        }

        void saveDecodedFile() {
            // Reconstruct the Huffman tree from tree structure and metadata from the compressed file
            // Decode the encoded data using the Huffman tree
            // Save decoded data in the decompressed file
        }

    public:
        // Compressing input file
        void compress(string inFileName, string outFileName) 
        {
            createArr(inFileName);
            createTree();
            assignHCodes();
            encodeAndSaveFile(inFileName, outFileName);
        }
        
        // Decompressing input file
        void decompress() 
        {
            saveDecodedFile();
        }
};
#endif