// Eric Chun - jc2ppp - 11/9/20 - heap.h
// Using heap code from the slides

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "node.h"
using namespace std;

class heap {
 public:
  heap();
  ~heap();

  void insert(node* n);
  node* findMin();
  node* deleteMin();
  unsigned int size();
  void makeEmpty();
  bool isEmpty();
  
 private:
  vector<node*> myHeap;
  unsigned int heap_size;

  void percolateUp(int hole);
  void percolateDown(int hole);
};

#endif
