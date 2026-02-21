#include "bst.h"

#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

typedef struct BST {
    Node* root;
} BST;

BST* bstCreate()
{
    BST* tree = calloc(1, sizeof(*tree));
    return tree;
}

void bstInsert(BST* tree, int value)
{
    Node* newNode = calloc(1, sizeof(*newNode));
    newNode->value = value;

    Node* currentNode = tree->root;
    while (currentNode != NULL) {
        if (currentNode->value == value) {
            free(newNode);
            return;
        }
        if (currentNode->value > value) {
            if (currentNode->leftChild == NULL) {
                currentNode->leftChild = newNode;
                return;
            }
            currentNode = currentNode->leftChild;
        }
        if (currentNode->value < value) {
            if (currentNode->rightChild == NULL) {
                currentNode->rightChild = newNode;
                return;
            }
            currentNode = currentNode->rightChild;
        }
    }
    tree->root = newNode;
}

bool bstContains(BST* tree, int value)
{
    Node* currentNode = tree->root;
    while (currentNode != NULL) {
        if (currentNode->value == value) {
            return true;
        }
        if (currentNode->value > value) {
            if (currentNode->leftChild == NULL) {
                return false;
            }
            currentNode = currentNode->leftChild;
        }
        if (currentNode->value < value) {
            if (currentNode->rightChild == NULL) {
                return false;
            }
            currentNode = currentNode->rightChild;
        }
    }
    return false;
}

void bstFreeRecursion(Node* node)
{
    if (node == NULL) {
        return;
    }
    bstFreeRecursion(node->leftChild);
    bstFreeRecursion(node->rightChild);
    free(node);
}

void bstFree(BST* tree)
{
    if (tree->root == NULL) {
        return;
    }
    bstFreeRecursion(tree->root->leftChild);
    bstFreeRecursion(tree->root->rightChild);
    free(tree->root);
    free(tree);
}

// int max(int a, int b)
// {
//     if (a > b) {
//         return a;
//     }
//     return b;
// }

// int bstHeightRecursion(Node* node, int height)
// {
//     if ()
// }

// int bstHeight(BST* tree)
// {
//     if (tree->root == NULL) {
//         return 0;
//     }

//     return max(bstHeightRecursion(tree->root->leftChild, 1), bstHeightRecursion(tree->root->rightChild, 1));
// }

int bstSizeRecursion(Node* node)
{
    if (node == NULL) {
        return 0;
    }

    return bstSizeRecursion(node->leftChild) + bstSizeRecursion(node->rightChild) + 1;
}

int bstSize(BST* tree)
{
    if (tree->root == NULL) {
        return 0;
    }

    return bstSizeRecursion(tree->root->leftChild) + bstSizeRecursion(tree->root->rightChild) + 1;
}

int bstMin(BST* tree)
{
    if (tree->root == NULL) {
        return -1;
    }

    Node* currentNode = tree->root;
    while (currentNode->leftChild != NULL) {
        currentNode = currentNode->leftChild;
    }
    return currentNode->value;
}

int bstMax(BST* tree)
{
    if (tree->root == NULL) {
        return -1;
    }

    Node* currentNode = tree->root;
    while (currentNode->rightChild != NULL) {
        currentNode = currentNode->rightChild;
    }
    return currentNode->value;
}
