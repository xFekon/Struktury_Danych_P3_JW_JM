#pragma once
class AVL_tree
{
private:
    struct AVLNode {
        int key;
        int value;
        int height;
        AVLNode* left;
        AVLNode* right;

        AVLNode(int k, int v)
            : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
    };

    AVLNode* root;

    int height(AVLNode* node);
    int getBalance(AVLNode* node);

    AVLNode* insert(AVLNode* node, int key, int value);
    AVLNode* remove(AVLNode* node, int key);
    AVLNode* findMin(AVLNode* node);
    AVLNode* balance(AVLNode* node);

    AVLNode* rotateLeft(AVLNode* y);
    AVLNode* rotateRight(AVLNode* x);

    void inorderPrint(AVLNode* node);
    void deleteTree(AVLNode* node);


public:
    AVL_tree();
    ~AVL_tree();

    void insert(int key, int value);
    void remove(int key);
    bool find(int key, int& value);
    void printInOrder();
};

