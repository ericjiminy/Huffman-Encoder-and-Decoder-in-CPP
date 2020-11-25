// Eric Chun - jc2ppp - 11/9/20 - node.h

#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class node {
public:
  node();
  ~node();
  char character;
  int frequency;
  node* left;
  node* right;
  friend class heap;
};

#endif

