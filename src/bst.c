#include "bst.h"

#include "stack.h"
#include <assert.h>
#include <limits.h>
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

typedef struct Iterator {
    Stack* nodeStack;
} Iterator;

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

// Добавляет всю левую палку данной ноды в стек, начиная от ближайшего.
// Под палкой здесь подразумеваются элементы, по которым мы проходим, идя всё время именно влево, включая саму ноду.
void addLeftStickInStack(Stack* stack, Node* node)
{
    Node* currentNode = node;
    while (currentNode != NULL) {
        push(stack, currentNode);
        currentNode = currentNode->leftChild;
    }
}

Iterator* iteratorInit(BST* tree)
{
    Iterator* iterator = malloc(sizeof(*iterator));
    assert(iterator != NULL && "А вот на итератор-то памяти и не хватило. Ошибка.");

    Stack* stack = createStack();
    addLeftStickInStack(stack, tree->root);

    iterator->nodeStack = stack;
    return iterator;
}

bool iteratorHasNext(Iterator* iterator)
{
    return !isEmpty(iterator->nodeStack);
}

int iteratorNext(Iterator* iterator)
{
    assert(iteratorHasNext(iterator) && "Ошибка! Кончился у вас итератор! Нету его больше! Всё!");
    Node* node = pop(iterator->nodeStack);
    int value = node->value;

    if (node->rightChild != NULL) {
        addLeftStickInStack(iterator->nodeStack, node->rightChild);
    }

    return value;
}

void iteratorFree(Iterator* iterator)
{
    deleteStack(iterator->nodeStack);
    free(iterator);
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

bool bstIsValidRecursion(Node* node, int min, int max)
{
    if (node == NULL) {
        return true;
    }
    if (node->value <= min || node->value >= max) {
        return false;
    }
    return bstIsValidRecursion(node->leftChild, min, node->value) && bstIsValidRecursion(node->rightChild, node->value, max);
}

bool bstIsValid(BST* tree)
{
    if (tree->root == NULL) {
        return true;
    }
    // INT_MIN и INT_MAX взяты из библиотеки limits.h
    return bstIsValidRecursion(tree->root, INT_MIN, INT_MAX);
}
