// Implement only this file. See avl.h and the assignment for contracts.
#include "avl.h"

// cached height, or 0 for an empty subtree
int nodeHeight(const Node* node) {
    return node ? node->height : 0;
}

// height is 1 + the taller child
void updateHeight(Node* node) {
    int left = nodeHeight(node->left);
    int right = nodeHeight(node->right);
    node->height = 1 + (left > right ? left : right);
}

// left height minus right height
int balanceFactor(const Node* node) {
    if (!node) {
        return 0;
    }
    return nodeHeight(node->left) - nodeHeight(node->right);
}

// right child moves up, root becomes its left child
Node* rotateLeft(Node* root) {
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

// left child moves up, root becomes its right child
Node* rotateRight(Node* root) {
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

// fixes the four imbalance cases (LL, LR, RR, RL) with rotations
Node* rebalance(Node* root) {
    updateHeight(root);
    int bf = balanceFactor(root);
    if (bf > 1) {
        if (balanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }
    if (bf < -1) {
        if (balanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }
    return root;
}

// normal bst insert, then rebalance on the way back up
Node* insertNode(Node* root, Node* newNode) {
    if (!root) {
        return newNode;
    }
    if (newNode->data.departure < root->data.departure) {
        root->left = insertNode(root->left, newNode);
    } else {
        root->right = insertNode(root->right, newNode);
    }
    return rebalance(root);
}

// unlinks the smallest node into minNode and returns the rebalanced subtree
static Node* removeMin(Node* root, Node*& minNode) {
    if (!root->left) {
        minNode = root;
        return root->right;
    }
    root->left = removeMin(root->left, minNode);
    return rebalance(root);
}

// bst delete; a node with two children is replaced by its in-order successor
Node* deleteNode(Node* root, int departure) {
    if (!root) {
        return nullptr;
    }
    if (departure < root->data.departure) {
        root->left = deleteNode(root->left, departure);
    } else if (departure > root->data.departure) {
        root->right = deleteNode(root->right, departure);
    } else {
        Node* left = root->left;
        Node* right = root->right;
        delete root;
        if (!left) {
            return right;
        }
        if (!right) {
            return left;
        }
        Node* successor = nullptr;
        Node* rest = removeMin(right, successor);
        successor->right = rest;
        successor->left = left;
        return rebalance(successor);
    }
    return rebalance(root);
}

// walks down the tree to the exact time
const Node* findNode(const Node* root, int departure) {
    while (root && root->data.departure != departure) {
        if (departure < root->data.departure) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

// remembers the best candidate >= departure while going down
const Node* earliestNode(const Node* root, int departure) {
    const Node* best = nullptr;
    while (root) {
        if (root->data.departure >= departure) {
            best = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return best;
}

void findRange(const Node* root, int start, int end,
               const Node* results[], int& count) {
    (void)root;
    (void)start;
    (void)end;
    (void)results;
    (void)count; // TODO
}
