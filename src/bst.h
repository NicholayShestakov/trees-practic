#pragma once

#include <stdbool.h>

typedef struct BST BST;

// Создаёт двоичное дерево поиска без узлов и возвращает указатель на него.
BST* bstCreate(void);

// Вставка значения в дерево.
void bstInsert(BST* tree, int value);

// Проверка на наличие значения в дереве.
// Возвращает true, если значение есть, и false, если нет.
bool bstContains(BST* tree, int value);

// Освобождение памяти, занимаемой деревом.
void bstFree(BST* tree);
