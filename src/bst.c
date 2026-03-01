#include "bst.h"

#include "stack.h"
#include <assert.h>
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
    free(iterator->nodeStack);
    free(iterator);
}
