#pragma once

#include <stdbool.h>

typedef struct BST BST;

// Создаёт двоичное дерево поиска без узлов и возвращает указатель на него.
BST* bstCreate();

// Вставка значения в дерево.
void bstInsert(BST* tree, int value);

// Проверка на наличие значения в дереве.
// Возвращает true, если значение есть, и false, если нет.
bool bstContains(BST* tree, int value);

// Освобождение памяти, занимаемой деревом.
void bstFree(BST* tree);

// Возвращает высоту дерева. Высота пустого дерева равна 0.
int bstHeight(BST* tree);

// Возвращает количество узлов дерева.
int bstSize(BST* tree);

// Возвращает минимальное значение дерева. Если дерево пустое, возвращает -1.
int bstMin(BST* tree);

// Возвращает максимальное значение дерева. Если дерево пустое, возвращает -1.
int bstMax(BST* tree);
