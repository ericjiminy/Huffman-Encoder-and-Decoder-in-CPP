// Eric Chun - jc2ppp - 11/9/20 - huffmanenc.cpp

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>
#include "heap.h"
using namespace std;

// get prefix codes from huffman tree and store them in codes hashmap, also prints section 1
unordered_map<char, string> getPrefixCodes(unordered_map<char, string>& codes, node* root, vector<string> code, int top) {
  if (root->left) {
    code[top] ="0";
    getPrefixCodes(codes, root->left, code, top + 1);
  }
  if (root->right) {
    code[top] = "1";
    getPrefixCodes(codes, root->right, code, top + 1);
  }
  if (root->left == NULL && root->right == NULL) {
    string s = "";
    for (int i = 0; i < top; i++) {
      s += code[i];
    }
    codes.insert(make_pair(root->character, s));
    if (root->character == ' ') {
      cout << "space " << s << endl;
    } else{
      cout << root-> character << " " << s << endl;
    }
  }
  return codes;
}

int main(int argc, char* argv[]) {
  // open input file
  ifstream file(argv[1]);
  if (!file.is_open()) {
    cout << "Unable to open '" << argv[1] << "' for reading" << endl;
    exit(2);
  }

  // count frequencies into hashmap
  string message = "";
  char c;
  unordered_map<char, int> freqs;
  while (file.get(c)) {
    if (c < 32 || c > 126) continue;
    message += c;
    if (freqs.find(c) == freqs.end()) {
      freqs[c] = 1;
    } else {
      freqs[c]++;
    }
  }

  // close input file
  file.close();

  // build min-heap with hashmap
  heap minHeap = heap();
  for (auto& pair : freqs) {
    node* n = new node();
    n->character = pair.first;
    n->frequency = pair.second;
    minHeap.insert(n);
  }

  // convert min-heap into huffman tree
  while (minHeap.size() > 1) {
    node* n1 = minHeap.deleteMin();
    node* n2 = minHeap.deleteMin();

    node* parent = new node();
    parent->frequency = n1->frequency + n2->frequency;
    parent->left = n1;
    parent->right = n2;

    minHeap.insert(parent);
  }

  // get prefix codes from huffman tree and store them in codes hashmap, also write section 1
  unordered_map<char, string> codes;
  node* root = minHeap.findMin();
  vector<string> code;
  code.resize(256);
  int top = 0;
  codes = getPrefixCodes(codes, root, code, top);
  cout << "----------------------------------------" << endl;

  // write section 2, encoded message
  string encodedMessage = "";
  for (char c : message) {
    encodedMessage += codes[c];
    cout << codes[c] << " ";
  }
  cout << endl;
  cout << "----------------------------------------" << endl;

  // write section 3, stats
  double numSymbols = message.size();
  double distinctSymbols = codes.size();
  double numBitsOriginal = numSymbols*8;
  double numBitsCompressed = encodedMessage.size();
  double compressionRatio = numBitsOriginal/numBitsCompressed;

  double huffmanCost = 0;
  for (auto& pair : codes) {
    huffmanCost += (freqs[pair.first]/numSymbols) * pair.second.size();
  }
  
  cout << "There are a total of " << numSymbols << " symbols that are encoded." << endl;
  cout << "There are " << distinctSymbols << " distinct symbols used." << endl;
  cout << "There were " << numBitsOriginal << " in the original file." << endl;
  cout << "There were " << numBitsCompressed << " in the compressed file." << endl;
  cout << fixed << setprecision(5) << "This gives us a compression ratio of " << compressionRatio << endl;
  cout << fixed << setprecision(5) << "The cost of the Huffman tree is " << huffmanCost << " bits per character." << endl;
}
