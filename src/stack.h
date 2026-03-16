#pragma once

#include <stdbool.h>

typedef struct Stack Stack;

typedef struct Node Node;

/*
 * Создаёт стек и передаёт указатель на него.
 * Внимание! Стек предназначен для хранения объектов типа Node*.
 * Если память под стек была выделена некорректно, возвращает NULL.
 */
Stack* createStack(void);

/*
 * Удаляет стек и очищает всю память, что была им занята.
 */
void deleteStack(Stack* stack);

/*
 * Кладёт на верхушку стека ссылку на ноду.
 * Если память не выделилась корректно, возвращает false.
 */
bool push(Stack* stack, Node* node);

/*
 * Проверяет, есть ли в стеке хоть один элемент.
 */
bool isEmpty(Stack* stack);

/*
 * Удаляет элемент с верхушки стека и возвращает его.
 * Возвращает NULL, если стек пуст.
 */
Node* pop(Stack* stack);
