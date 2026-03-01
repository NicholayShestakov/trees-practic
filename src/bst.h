#pragma once

#include <stdbool.h>

typedef struct BST BST;

typedef struct Iterator Iterator;

// Создаёт двоичное дерево поиска без узлов и возвращает указатель на него.
BST* bstCreate(void);

// Вставка значения в дерево.
void bstInsert(BST* tree, int value);

// Проверка на наличие значения в дереве.
// Возвращает true, если значение есть, и false, если нет.
bool bstContains(BST* tree, int value);

// Освобождение памяти, занимаемой деревом.
void bstFree(BST* tree);

// Создание итератора, обходящего дерево в порядке in-order, и возврат указателя на итератор.
// Итератор итерируется по дереву, так что просьба дерево не менять в процессе пользования итератором, иначе UB будет.
Iterator* iteratorInit(BST* tree);

// Проверка, остались ли непроитерированные элементы в итераторе.
bool iteratorHasNext(Iterator* iterator);

// Выдача текущего элемента итератора и переход к следующему.
// Если элемента нету, вызывает ошибку, так что советуется перед вызовом данной функции проверять итератор с помощью iteratorHasNext.
int iteratorNext(Iterator* iterator);

// Освобождает всю память, выделенную под итератор.
void iteratorFree(Iterator* iterator);
