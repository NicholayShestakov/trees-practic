#include "bst.h"

#include "stack.h"
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

int bstHeightRecursion(Node* node)
{
    if (node == NULL) {
        return 0;
    }
    int leftHeight = bstHeightRecursion(node->leftChild);
    int rightHeight = bstHeightRecursion(node->rightChild);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int bstHeight(BST* tree)
{
    if (tree->root == NULL) {
        return 0;
    }
    int height = bstHeightRecursion(tree->root);
    return height - 1;
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

// ----------------------------------------------

int bstSize(BST* tree)
{
    return tree->size;
}

// Внутренняя функция, не доступная пользователю.
// Рекурсивно добавляет элементы в переданный массив
void bstPreorderRecursionAddingNodesInArr(Node* node, int* arr, int* index)
{
    if (node == NULL || arr == NULL) {
        return;
    }
    arr[(*index)++] = node->value;
    bstPreorderRecursionAddingNodesInArr(node->leftChild, arr, index);
    bstPreorderRecursionAddingNodesInArr(node->rightChild, arr, index);
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
    bstPreorderRecursionAddingNodesInArr(tree->root, arrWithNodes, &index);
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

Node* parentRecursive(Node* root, Node* node)
{
    if (root == NULL) {
        return NULL;
    }

    else if (root->leftChild == node || root->rightChild == node) {
        return root;
    }

    else {
        Node* leftParent = parentRecursive(root->leftChild, node);
        return leftParent;

        Node* rightParent = parentRecursive(root->rightChild, node);
        return rightParent;
    }

    return NULL;
}

Node* parent(BST* tree, Node* node)
{
    if (tree == NULL || tree->root == NULL || tree->root == node) {
        return NULL;
    }

    return parentRecursive(tree->root, node);
}
Node* minRightTree(Node* node)
{
    Node* current = node->rightChild;

    while (current->leftChild != NULL) {
        current = current->leftChild;
    }

    return current;
}

void bstDelete(BST* tree, int value)
{
    if (tree == NULL || tree->root == NULL) {
        return;
    }

    Node* current = tree->root;

    while (current->value != value) {

        if (value < current->value) {
            current = current->leftChild;
        } else {
            current = current->rightChild;
        }
    }

    if (current == NULL) {
        return;
    }

    if (current->leftChild == NULL && current->rightChild == NULL) {
        Node* parnt = parent(tree, current);

        if (parnt == NULL) {
            tree->root = NULL;
        }

        else if (parnt->leftChild == current) {
            parnt->leftChild = NULL;

        } else {
            parnt->rightChild = NULL;
        }
        free(current);
    }

    else if (current->leftChild == NULL || current->rightChild == NULL) {

        Node* temp = NULL;

        if (current->rightChild != NULL) {
            temp = current->rightChild;

        } else {
            temp = current->leftChild;
        }

        Node* parnt = parent(tree, current);

        if (parnt == NULL) {
            tree->root = temp;
        }

        else if (parnt->leftChild == current) {
            parnt->leftChild = temp;
        } else {
            parnt->rightChild = temp;
        }
        free(current);
    }

    else {
        Node* minRight = minRightTree(current);

        int minRightValue = minRight->value;

        Node* minRightParent = parent(tree, minRight);

        if (minRightParent->leftChild == minRight) {
            minRightParent->leftChild = minRight->rightChild;
        } else {
            minRightParent->rightChild = minRight->rightChild;
        }
        current->value = minRightValue;
        free(minRight);
    }
}
