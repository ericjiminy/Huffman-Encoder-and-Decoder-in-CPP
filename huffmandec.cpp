// Eric Chun - jc2ppp - 11/10/20 - huffmandec.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>
#include "heap.h"
using namespace std;

// create huffman tree from prefix codes
void createHuffmanTree(unordered_map<string, string> codes, node* root, vector<string> code, int top) {
  string path = "";
  for (int i = 0; i < top; i++) {
    path += code[i];
  }

  if (codes.find(path) == codes.end()) {
    node* left = new node();
    root->left = left;
    code[top] = "0";
    createHuffmanTree(codes, root->left, code, top+1);

    node* right = new node();
    root->right = right;
    code[top] = "1";
    createHuffmanTree(codes, root->right, code, top+1);
  } else {
    root->character = codes.find(path)->second[0];
  }
}

// delete nodes in huffman tree
void freeHuffmanTree(node* root) {
  if (root->left != NULL) {
    node* left = root->left;
    node* right = root->right;
    delete root;
    freeHuffmanTree(left);
    freeHuffmanTree(right);
  } else {
    delete root;
  }
}

int main(int argc, char* argv[]) {
  // open encoded file
  ifstream file(argv[1], ifstream::binary);
  if (!file.is_open()) {
    cout << "Unable to open file '" << argv[1] << "'." << endl;
    exit(2);
  }

  // store prefix codes into codes hashmap
  unordered_map<string, string> codes;
  while (true) {
    string character, prefix;
    
    file >> character;
    if (character[0] == '-' && character.length() > 1) break;
    if (character == "space") character = " ";
    
    file >> prefix;
    codes.insert(make_pair(prefix, character));
  }

  // create huffman tree from prefix codes
  heap minHeap = heap();
  node* root = new node();
  minHeap.insert(root);
  vector<string> code;
  code.resize(256);
  int top = 0;
  createHuffmanTree(codes, root, code, top);

  // read in the encoded message
  stringstream sstm;
  while (true) {
    string bits;
    file >> bits;
    if (bits[0] == '-') break;
    sstm << bits;
  }
  string encoded = sstm.str();

  // traverse huffman tree using encoded message, print out decoded message
  for (char c : encoded) {
    string s(1, c);
    if (s == "0") {
      root = root->left;
    } else if (s == "1") {
      root = root->right;
    }
    if (root->left == NULL && root->right == NULL) {
      cout << root->character;
      root = minHeap.findMin();
    }
  }
  cout << endl;

  root = minHeap.findMin();
  freeHuffmanTree(root);
}
