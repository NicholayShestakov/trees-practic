#include "bst.h"

#include "stack.h"
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

/* Задача A — Структура и вставка */

BST* bstCreate(void)
{
    return calloc(1, sizeof(BST));
}

bool bstInsert(BST* tree, int value)
{
    Node* newNode = calloc(1, sizeof(*newNode));
    if (newNode == NULL) {
        return false;
    }

    newNode->value = value;
    Node* currentNode = tree->root;
    while (currentNode != NULL) {
        if (currentNode->value == value) {
            free(newNode);
            return false;
        }
        if (currentNode->value > value) {
            if (currentNode->leftChild == NULL) {
                currentNode->leftChild = newNode;
                tree->size++;
                return true;
            }
            currentNode = currentNode->leftChild;
        }
        if (currentNode->value < value) {
            if (currentNode->rightChild == NULL) {
                currentNode->rightChild = newNode;
                tree->size++;
                return true;
            }
            currentNode = currentNode->rightChild;
        }
    }
    tree->root = newNode;
    tree->size++;

    return true;
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
    bstFreeRecursion(tree->root);
    free(tree);
}

/* Задача B — Обходы */

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
    bstPostorderRecursion(tree->root);
    printf("\n");
}

/* Задача C — Статистика дерева */

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

int bstSize(BST* tree)
{
    return tree->size;
}

int bstMin(BST* tree, bool* err)
{
    if (tree->root == NULL) {
        *err = true;
        return -1;
    }
    Node* currentNode = tree->root;
    while (currentNode->leftChild != NULL) {
        currentNode = currentNode->leftChild;
    }
    return currentNode->value;
}

int bstMax(BST* tree, bool* err)
{
    if (tree->root == NULL) {
        *err = true;
        return -1;
    }
    Node* currentNode = tree->root;
    while (currentNode->rightChild != NULL) {
        currentNode = currentNode->rightChild;
    }
    return currentNode->value;
}

/* Задача D — Удаление */

Node* parentRecursive(Node* parent, Node* node)
{
    if (parent == NULL) {
        /* Функция всегда возвращает NULL, если достигли конца дерева, узел не найден
         * или узел не найден в поддереве.
         * Это означает, что NULL может расцениваться как "родитель не найден",
         * так и "узел не существует в этом поддереве".
         */
        return NULL;
    } else if (parent->leftChild == node || parent->rightChild == node) {
        return parent;
    } else {
        Node* leftParent = parentRecursive(parent->leftChild, node);
        if (leftParent != NULL) {
            return leftParent;
        }

        return parentRecursive(parent->rightChild, node);
    }
}

Node* findParent(BST* tree, Node* node)
{
    if (tree == NULL || tree->root == NULL || tree->root == node) {
        /* При некорректных входных данных и в случае если узел не найден в дереве функция возвращает NULL
         * Это означает, что NULL может расцениваться как некорректно введенные данные,
         * случай узел является корнем и узел не найден в дереве.
         * Замечание: при использовании всегда нужно проверять дерево на корректность,
         * а также убедиться, что узел принадлежит дереву
         */
        return NULL;
    }

    return parentRecursive(tree->root, node);
}

Node* minRightTree(Node* node) // Функция, находящая минимальный элемент в правом поддереве
{
    // При отсутствии самого узла или правого поддерева функция возвращает NULL

    if (node == NULL || node->rightChild == NULL) {
        return NULL;
    }

    Node* current = node->rightChild;

    while (current->leftChild != NULL) {
        current = current->leftChild;
    }

    return current;
}

bool bstDelete(BST* tree, int value)
{
    if (tree == NULL || tree->root == NULL) {
        return false;
    }

    Node* current = tree->root;

    while (current != NULL && current->value != value) {
        if (value < current->value) {
            current = current->leftChild;
        } else {
            current = current->rightChild;
        }
    }

    if (current == NULL) {
        return false;
    }

    if (current->leftChild == NULL && current->rightChild == NULL) {

        Node* parent = findParent(tree, current);

        if (parent == NULL) {
            if (tree->root == current) {
                tree->root = NULL;
            } else {
                return false;
            }
        } else if (parent->leftChild == current) {
            parent->leftChild = NULL;
        } else {
            parent->rightChild = NULL;
        }
        free(current);
        tree->size--;
    } else if (current->leftChild == NULL || current->rightChild == NULL) {

        Node* temp = NULL;

        if (current->rightChild != NULL) {
            temp = current->rightChild;
        } else {
            temp = current->leftChild;
        }

        Node* parent = findParent(tree, current);

        if (parent == NULL) {
            tree->root = temp;
        } else if (parent->leftChild == current) {
            parent->leftChild = temp;
        } else {
            parent->rightChild = temp;
        }
        free(current);
        tree->size--;
    } else {
        Node* minRight = minRightTree(current);

        int minRightValue = minRight->value;

        Node* minRightParent = findParent(tree, minRight);

        if (minRightParent->leftChild == minRight) {
            minRightParent->leftChild = minRight->rightChild;
        } else {
            minRightParent->rightChild = minRight->rightChild;
        }
        current->value = minRightValue;
        free(minRight);
        tree->size--;
    }

    return true;
}

/* Задача E — Слияние двух деревьев */

/*
 * Рекурсивно добавляет элементы в переданный массив.
 */
void bstPreorderRecursionAddingNodesInArr(Node* node, int* arr, int* index)
{
    if (node == NULL || arr == NULL) {
        return;
    }
    arr[(*index)++] = node->value;
    bstPreorderRecursionAddingNodesInArr(node->leftChild, arr, index);
    bstPreorderRecursionAddingNodesInArr(node->rightChild, arr, index);
}

/*
 * Функция, которая создает массив из всех значений узлов дерева в порядке прямого обхода.
 * На вход принимает само дерево, а возвращает указатель на массив с значениями всех узлов дерева.
 * Если дерево пустое, возвращает NULL.
 * Если не выделилась память внутри функции тоже возвращается NULL.
 */
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
    if (newTree == NULL) {
        free(nodes1);
        free(nodes2);
        return NULL;
    }

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

/* Задача F — Проверка корректности */

bool bstIsValidRecursion(Node* node, int* min, int* max)
{
    if (node == NULL) {
        return true;
    }
    if (min != NULL && node->value <= *min) {
        return false;
    }
    if (max != NULL && node->value >= *max) {
        return false;
    }
    return bstIsValidRecursion(node->leftChild, min, &node->value) && bstIsValidRecursion(node->rightChild, &node->value, max);
}

bool bstIsValid(BST* tree)
{
    if (tree == NULL) {
        return false;
    }
    return bstIsValidRecursion(tree->root, NULL, NULL);
}

/* Задача G — k-й минимальный элемент */

int bstKthMinRecursion(Node* node, int* k, bool* err)
{
    if (node == NULL) {
        *err = true;
        return -1;
    }

    int res = bstKthMinRecursion(node->leftChild, k, err);
    if (res != -1) {
        return res;
    }

    (*k)--;
    if (*k == 0) {
        return node->value;
    }

    return bstKthMinRecursion(node->rightChild, k, err);
}

int bstKthMin(BST* tree, int k, bool* err)
{
    if (tree == NULL) {
        *err = true;
        return -1;
    }

    if (k > bstSize(tree) || k < 1) {
        *err = true;
        return -1;
    }

    return bstKthMinRecursion(tree->root, &k, err);
}

/* Задача H — Итератор */

/*
 * Добавляет всю левую палку данной ноды в стек, начиная от ближайшего.
 * Под палкой здесь подразумеваются элементы, по которым мы проходим, идя всё время именно влево, включая саму ноду.
 */
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
    if (iterator == NULL) {
        return NULL;
    }

    Stack* stack = createStack();
    addLeftStickInStack(stack, tree->root);

    iterator->nodeStack = stack;
    return iterator;
}

bool iteratorHasNext(Iterator* iterator)
{
    return !isEmpty(iterator->nodeStack);
}

int iteratorNext(Iterator* iterator, bool* err)
{
    if (!iteratorHasNext(iterator)) {
        *err = true;
        return -1;
    }

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
