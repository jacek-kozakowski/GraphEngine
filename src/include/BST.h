//
// Created by Jacek Kozakowski on 02/01/2026.
//

#ifndef GRAPHENGINE_BST_H
#define GRAPHENGINE_BST_H

struct BSTNode {
  int key;
  BSTNode *left, *right;
  BSTNode(int val) : key(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
  BSTNode *root;
  void inOrderHelper(const BSTNode *root);
  void preOrderHelper(const BSTNode *root);
  void postOrderHelper(const BSTNode *root);
  int bstToVine(BSTNode *root);
  void compress(BSTNode *root, int m);
public:
  BST();
  BST(int key);
  ~BST();

  void insert(int key);
  void remove(int key);
  bool search(int key);
  void traverseInOrder();
  void traversePreOrder();
  void traversePostOrder();
  void dsw();
};

#endif // GRAPHENGINE_BST_H