#include "AVL_tree.h"

#include <iostream>
#include <algorithm>

AVL_tree::AVL_tree() : root(nullptr) {}


AVL_tree::~AVL_tree() {
    deleteTree(root);
}

// Pomocnicza funkcja do usuwania drzewa
void AVL_tree::deleteTree(AVLNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}


int AVL_tree::height(AVLNode* node) {
    return node ? node->height : 0;
}


int AVL_tree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Rotacja w lewo
AVL_tree::AVLNode* AVL_tree::rotateLeft(AVLNode* y) {
    AVLNode* x = y->right;
    AVLNode* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));

    return x;
}

// Rotacja w prawo
AVL_tree::AVLNode* AVL_tree::rotateRight(AVLNode* x) {
    AVLNode* y = x->left;
    AVLNode* T2 = y->right;

    y->right = x;
    x->left = T2;

    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));

    return y;
}

// Balansowanie poddrzewa
AVL_tree::AVLNode* AVL_tree::balance(AVLNode* node) {
    int balanceFactor = getBalance(node);

    // Lewo-lewo
    if (balanceFactor > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);

    // Lewo-prawo
    if (balanceFactor > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Prawo-prawo
    if (balanceFactor < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);

    // Prawo-lewo
    if (balanceFactor < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


// Wstawianie (rekurencyjnie)
AVL_tree::AVLNode* AVL_tree::insert(AVLNode* node, int key, int value) {
    if (!node)
        return new AVLNode(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else {
        node->value = value;  // Nadpisz wartoœæ dla istniej¹cego klucza
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    return balance(node);
}


// Usuwanie najmniejszego wêz³a (pomocnicze)
AVL_tree::AVLNode* AVL_tree::findMin(AVLNode* node) {
    while (node->left)
        node = node->left;
    return node;
}

// Usuwanie wêz³a (rekurencyjnie)
AVL_tree::AVLNode* AVL_tree::remove(AVLNode* node, int key) {
    if (!node)
        return nullptr;

    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        // Wêze³ do usuniêcia
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        else {
            AVLNode* temp = findMin(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key);
        }
    }

    node->height = 1 + std::max(height(node->left), height(node->right));
    return balance(node);
}



void AVL_tree::insert(int key, int value) {
    root = insert(root, key, value);
}


void AVL_tree::remove(int key) {
    root = remove(root, key);
}


bool AVL_tree::find(int key, int& value) {
    AVLNode* current = root;
    while (current) {
        if (key == current->key) {
            value = current->value;
            return true;
        }
        current = key < current->key ? current->left : current->right;
    }
    return false;
}


void AVL_tree::printInOrder() {
    inorderPrint(root);
    std::cout << std::endl;
}

void AVL_tree::inorderPrint(AVLNode* node) {
    if (node) {
        inorderPrint(node->left);
        std::cout << "(" << node->key << ":" << node->value << ") ";
        inorderPrint(node->right);
    }
}