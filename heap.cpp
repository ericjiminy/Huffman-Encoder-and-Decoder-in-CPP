// Eric Chun - jc2ppp - 11/9/20 - heap.cpp
// Using heap code from the slides

#include <iostream>
#include "heap.h"
using namespace std;

heap::heap() {
  heap_size = 0;
  myHeap.push_back(NULL);
}

heap::~heap() {
  
}

void heap::insert(node* n) {
  myHeap.push_back(n);
  percolateUp(++heap_size);
}

void heap::percolateUp(int hole) {
  node* n = myHeap[hole];
  for ( ; (hole > 1) && (n->frequency < myHeap[hole/2]->frequency); hole /= 2) {
    myHeap[hole] = myHeap[hole/2];
  }
  myHeap[hole] = n;
}

node* heap::deleteMin() {
  if (heap_size == 0) {
    throw "deleteMin() called on empty heap";
  }

  node* ret = myHeap[1];
  myHeap[1] = myHeap[heap_size--];
  myHeap.pop_back();
  if (!isEmpty()) {
    percolateDown(1);
  }
  return ret;
}

void heap::percolateDown(int hole) {
  node* n = myHeap[hole];
  while (hole*2 <= heap_size) {
    int child = hole*2;
    if ((child+1 <= heap_size) && (myHeap[child+1]->frequency < myHeap[child]->frequency)) {
      child++;
    }
    if (n->frequency > myHeap[child]->frequency) {
      myHeap[hole] = myHeap[child];
      hole = child;
    }
    else break;
  }
  myHeap[hole] = n;
}

node* heap::findMin() {
  if (heap_size == 0) {
    throw "findMin() called on empty heap";
  }
  return myHeap[1];
}

unsigned int heap::size() {
  return heap_size;
}

void heap:: makeEmpty() {
  heap_size = 0;
  myHeap.resize(1);
}

bool heap::isEmpty() {
  return heap_size == 0;
}
