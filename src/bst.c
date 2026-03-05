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
} BST;

BST* bstCreate(void)
{
    BST* tree = calloc(1, sizeof(*tree));
    assert(tree != NULL && "Ошибка выделения памяти при создании дерева.");
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

void bstPreorderRecursionAddingNodesInArr(Node* node, int* arr, int size, int* index)
{
    if (node == NULL || arr == NULL) {
        return;
    }
    arr[*index] = node->value;
    (*index)++;
    bstPreorderRecursionAddingNodesInArr(node->leftChild, arr, size, index);
    bstPreorderRecursionAddingNodesInArr(node->rightChild, arr, size, index);
}

int* getAllNodesFormTree(BST* tree, int size)
{
    if (size == 0) {
        printf("Дерево пустое, узлов нет.\n");
        return NULL;
    }
    int* arrWithNodes = malloc(sizeof(int) * size);
    assert(arrWithNodes != NULL && "Кажется, ошибка выделения памяти.");
    int index = 0;
    bstPreorderRecursionAddingNodesInArr(tree->root, arrWithNodes, size, &index);
    return arrWithNodes;
}

BST* bstMerge(BST* tree1, BST* tree2)
{
    int size1 = bstSize(tree1);
    int size2 = bstSize(tree2);
    int* nodes1 = getAllNodesFormTree(tree1, size1);
    int* nodes2 = getAllNodesFormTree(tree2, size2);
    BST* newTree = bstCreate();
    for (int i = 0; i < size1; i++) {
        bstInsert(newTree, nodes1[i]);
    }
    for (int j = 0; j < size2; j++) {
        if (!bstContains(newTree, nodes2[j])) {
            bstInsert(newTree, nodes2[j]);
        }
    }
    free(nodes1);
    free(nodes2);
    return newTree;
}
