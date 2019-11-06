class node{
public:
  int key;
  node* parent;
  node* left;
  node* right;
  bool color;

  node (int inKey, node* inParent, node* inLeft, node* inRight) {
    key = inKey;
    parent = inParent;
    left = inLeft;
    right = inRight;
  }

  int getKey() {
    return key;
  }

  node* getParent() {
    return parent;
  }

  node* getLeft() {
    return left;
  }

  node* getRight() {
    return right;
  }

  bool getColor() {
    return color;
  }

  void setKey(int in_key) {
    key = in_key;
  }

  void setParent(node* in_parent) {
    parent = in_parent;
  }

  void setLeft(node* in_left) {
    left = in_left;
  }

  void setRight(node* in_right) {
    right = in_right;
  }

  bool setColor(bool in_color) {
    color = in_color;
  }

};
