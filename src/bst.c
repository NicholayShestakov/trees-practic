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

BST* bstCreate(void)
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

void bstPreorderRecursion(Node* node)
{
    if (node == NULL) {
        return;
    }
    printf("%d ", node->value);
    bstPreorderRecursion(node->leftChild);
    bstPreorderRecursion(node->rightChild);
}

void bstPreorder(BST* tree)
{
    if (tree == NULL) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }
    bstPreorderRecursion(tree->root);
    printf("\n");
}

void bstInorderRecursion(Node* node)
{
    if (node == NULL) {
        return;
    }
    bstInorderRecursion(node->leftChild);
    printf("%d ", node->value);
    bstInorderRecursion(node->rightChild);
}

void bstInorder(BST* tree)
{
    if (tree == NULL) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }
    bstInorderRecursion(tree->root);
    printf("\n");
}

void bstPostorderRecursion(Node* node)
{
    if (node == NULL) {
        return;
    }
    bstPostorderRecursion(node->leftChild);
    bstPostorderRecursion(node->rightChild);
    printf("%d ", node->value);
}

void bstPostorder(BST* tree)
{
    if (tree == NULL) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }
    bstPostorderRecursion(tree->root);
    printf("\n");
}