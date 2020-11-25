// Eric Chun - jc2ppp - 11/9/20 - node.cpp

#include "node.h"
using namespace std;

node::node() {
  character = '?';
  frequency = 0;
  left = NULL;
  right = NULL;
}
node::~node() {
}
