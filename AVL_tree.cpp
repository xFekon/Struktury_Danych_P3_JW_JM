#include "AVL_tree.h"


AVL_tree::AVL_tree() : root(nullptr) {}


AVL_tree::~AVL_tree() {

}




int AVL_tree::height(AVLNode* node) {
    return node ? node->height : 0;
}


int AVL_tree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}


void AVL_tree::insert(int key, int value) {
    
}


void AVL_tree::remove(int key) {
    
}


bool AVL_tree::find(int key, int& value) {
    
}


void AVL_tree::printInOrder() {
    
}