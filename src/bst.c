#include "bst.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

typedef struct BST {
    Node* root;
    int size;
} BST;

BST* bstCreate(void)
{
    BST* tree = calloc(1, sizeof(*tree));
    tree->size = 0;
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
                tree->size++;
                return;
            }
            currentNode = currentNode->leftChild;
        }
        if (currentNode->value < value) {
            if (currentNode->rightChild == NULL) {
                currentNode->rightChild = newNode;
                tree->size++;
                return;
            }
            currentNode = currentNode->rightChild;
        }
    }
    tree->root = newNode;
    tree->size++;
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
    bstFreeRecursion(tree->root);
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
    if (tree->root == NULL) {
        return;
    }
    bstPostorderRecursion(tree->root);
    printf("\n");
}

// ----------------------------------------------

int bstSize(BST* tree)
{
    return tree->size;
}

void bstPreorderRecursionAddingNodesInArr(Node* node, int* arr, int size, int* index)
{
    if (node == NULL || arr == NULL) {
        return;
    }
    arr[(*index)++] = node->value;
    bstPreorderRecursionAddingNodesInArr(node->leftChild, arr, size, index);
    bstPreorderRecursionAddingNodesInArr(node->rightChild, arr, size, index);
}

int* getAllNodesFromTree(BST* tree)
{
    int size = bstSize(tree);
    if (size == 0) {
        return NULL;
    }
    int* arrWithNodes = calloc(size, sizeof(int));
    if (arrWithNodes == NULL) {
        return NULL;
    }
    int index = 0;
    bstPreorderRecursionAddingNodesInArr(tree->root, arrWithNodes, size, &index);
    return arrWithNodes;
}

BST* bstMerge(BST* tree1, BST* tree2)
{
    int size1 = bstSize(tree1);
    int size2 = bstSize(tree2);
    int* nodes1 = getAllNodesFromTree(tree1);
    int* nodes2 = getAllNodesFromTree(tree2);
    BST* newTree = bstCreate();
    for (int i = 0; i < size1; i++) {
        bstInsert(newTree, nodes1[i]);
    }
    for (int j = 0; j < size2; j++) {
        bstInsert(newTree, nodes2[j]);
    }
    free(nodes1);
    free(nodes2);
    return newTree;
}
