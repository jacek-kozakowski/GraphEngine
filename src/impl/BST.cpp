//
// Created by Jacek Kozakowski on 02/01/2026.
//

#include "../include/BST.h"
#include <cmath>
#include <iostream>

BST::BST() : root(nullptr) {}

BST::BST(int key) { root = new BSTNode(key); }

void deleteTree(BSTNode *node) {
  if (node == nullptr)
    return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

BST::~BST() { deleteTree(root); }

void BST::insert(int key) {
  if (root == nullptr) {
    root = new BSTNode(key);
    return;
  }
  BSTNode *curr = root;
  while (true) {
    if (curr->key == key) {
      std::cout << key << " already exists\n";
      return;
    }
    if (curr->key > key) {
      if (curr->left == nullptr) {
        curr->left = new BSTNode(key);
        return;
      }
      curr = curr->left;
    } else if (curr->key < key) {
      if (curr->right == nullptr) {
        curr->right = new BSTNode(key);
        return;
      }
      curr = curr->right;
    }
  }
}

void BST::remove(int key) {
  BSTNode *curr = root;
  BSTNode *parent = nullptr;
  while (curr != nullptr && curr->key != key) {
    parent = curr;
    if (curr->key < key)
      curr = curr->left;
    else
      curr = curr->right;
  }
  if (curr == nullptr)
    return;
  if (curr->left == nullptr || curr->right == nullptr) {
    BSTNode *temp = (curr->left != nullptr) ? curr->left : curr->right;

    if (parent == nullptr) {
      root = temp;
    } else if (parent->left == curr) {
      parent->left = temp;
    } else {
      parent->right = temp;
    }
    delete curr;
  } else {
    BSTNode *succParent = curr;
    BSTNode *succ = succParent->right;
    while (succ->left != nullptr) {
      succParent = succ;
      succ = succParent->left;
    }
    curr->key = succ->key;
    if (succParent->left == succ)
      succParent->left = succ->right;
    else
      succParent->right = succ->right;
    delete succ;
  }
}

bool BST::search(int key) {
  BSTNode *curr = root;
  while (curr != nullptr) {
    if (curr->key == key) {
      std::cout << key;
      return true;
    }
    std::cout << key << "->";
    if (curr->key < key)
      curr = curr->left;
    else
      curr = curr->right;
  }
  return false;
}

void BST::traverseInOrder() {
  inOrderHelper(root);
  std::cout << "\n";
}

void BST::inOrderHelper(const BSTNode *root) {
  if (root == nullptr)
    return;
  inOrderHelper(root->left);
  std::cout << root->key << " ";
  inOrderHelper(root->right);
}

void BST::traversePreOrder() {
  preOrderHelper(root);
  std::cout << "\n";
}

void BST::preOrderHelper(const BSTNode *root) {
  if (root == nullptr)
    return;
  std::cout << root->key << " ";
  preOrderHelper(root->left);
  preOrderHelper(root->right);
}

void BST::traversePostOrder() {
  postOrderHelper(root);
  std::cout << "\n";
}
void BST::postOrderHelper(const BSTNode *root) {
  if (root == nullptr)
    return;
  postOrderHelper(root->left);
  postOrderHelper(root->right);
  std::cout << root->key << " ";
}

void BST::dsw() {
  if (root == nullptr)
    return;

  BSTNode dummy(0);
  dummy.right = root;
  int count = bstToVine(&dummy);

  int h = log2(count + 1);
  int m = pow(2, h) - 1;

  compress(&dummy, count - m);

  for (m = m / 2; m > 0; m /= 2) {
    compress(&dummy, m);
  }

  root = dummy.right;
}

int BST::bstToVine(BSTNode *root) {
  int count = 0;

  BSTNode *tmp = root->right;
  while (tmp != nullptr) {
    if (tmp->left != nullptr) {
      BSTNode *oldTmp = tmp;
      tmp = tmp->left;
      oldTmp->left = tmp->right;
      tmp->right = oldTmp;
      root->right = tmp;
    } else {
      count++;
      root = tmp;
      tmp = tmp->right;
    }
  }
  return count;
}

void BST::compress(BSTNode *root, int m) {
  BSTNode *tmp = root->right;
  for (int i = 0; i < m && tmp != nullptr; i++) {
    BSTNode *oldTmp = tmp;
    tmp = tmp->right;
    if (tmp == nullptr)
      break;
    root->right = tmp;
    oldTmp->right = tmp->left;
    tmp->left = oldTmp;
    root = tmp;
    tmp = tmp->right;
  }
}
