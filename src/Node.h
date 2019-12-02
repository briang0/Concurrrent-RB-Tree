#ifndef NODE
#define NODE

class node{
public:
  int key;
  node* parent;
  node* left;
  node* right;
  bool color;

  node (int inKey, node* inParent, node* inLeft, node* inRight);

};

#endif
