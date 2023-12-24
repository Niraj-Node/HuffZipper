#ifndef HUFFMAN_H //Header Guards - Which Prevents file inclusion multiple times
#define HUFFMAN_H
#include<bits/stdc++.h>
using namespace std;

//Node (Customized for Huffman Tree)
struct Node 
{
    char data;
    unsigned freq;
    string code;
    Node *left, *right;

    Node() {
        left = right = NULL;
    }
};

class huffman 
{
    private:

        fstream inFile, outFile;
        string inFileName, outFileName;

        vector<Node*> arr;
        Node* root;
        
        //custom comparator for the priority_queue minHeap
        class Cmp
        {
            public:
                //This ensures that the priority queue maintains the order of nodes with the highest frequency at the top
                bool operator() (Node* l, Node* r)
                {
                    return l->freq > r->freq;
                }
        };
        priority_queue <Node*, vector<Node*>, Cmp> minHeap;
        
        //Initializing a vector representing character's ascii value and its frequency with 0
        void createArr() 
        {
            for(int i = 0; i < 128; i++) 
            {
                arr.push_back(new Node());
                arr[i]->data = i;
                arr[i]->freq = 0;
            }
        }
        
        //Populating Min Heap by inserting Nodes of characters which appears in the input file
        void createMinHeap() 
        {
            char id;
            inFile.open(inFileName, ios::in);
            inFile.get(id);
            while(!inFile.eof()) 
            {
                arr[id]->freq++;
                inFile.get(id);
            }
            inFile.close();
    
            for(int i = 0; i < 128; i++) 
            {
                if(arr[i]->freq > 0)
                    minHeap.push(arr[i]);
            }
        }

        void createTree() 
        {
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

        //Traversing the constructed tree to generate huffman codes of each present character
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
        
        //Generating Huffman codes
        void assignHCodes() {
            //Traversing the Huffman Tree and assigning specific codes to each character as leaf node
            traverse(root, "");
        }

        void saveEncodedFile() {
            // Save tree structure and metadata at the beginning of the file
            // Save encoded data after the tree structure and metadata
        }

        void saveDecodedFile() {
            // Reconstruct the Huffman tree from tree structure and metadata from the compressed file
            // Decode the encoded data using the Huffman tree
            // Save decoded data in the decompressed file
        }

    public:
        //Constructor
        huffman(string inFileName, string outFileName)
        {
            this->inFileName = inFileName;
            this->outFileName = outFileName;
            createArr();
        }
        //Compressing input file
        void compress() 
        {
            createMinHeap();
            createTree();
            assignHCodes();
            saveEncodedFile();
        }
        //Decompressing input file
        void decompress() 
        {
            saveDecodedFile();
        }
};
#endif