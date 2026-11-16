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

Node* insertNode(Node* root, Node* newNode) {
    (void)newNode;
    return root; // TODO
}

Node* deleteNode(Node* root, int departure) {
    (void)departure;
    return root; // TODO
}

const Node* findNode(const Node* root, int departure) {
    (void)root;
    (void)departure;
    return nullptr; // TODO
}

const Node* earliestNode(const Node* root, int departure) {
    (void)root;
    (void)departure;
    return nullptr; // TODO
}

void findRange(const Node* root, int start, int end,
               const Node* results[], int& count) {
    (void)root;
    (void)start;
    (void)end;
    (void)results;
    (void)count; // TODO
}
