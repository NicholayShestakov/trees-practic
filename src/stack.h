#pragma once

#include <stdbool.h>

typedef struct Stack Stack;

typedef struct Node Node;

// Создаёт стек и передаёт указатель на него.
// Внимание! Стек предназначен для хранения объектов типа Node*. Просьба любить и жаловать.
Stack* createStack(void);

// Удаляет стек и очищает всю память, что была им занята.
void deleteStack(Stack* stack);

// Кладёт на верхушку стека ссылку на ноду.
void push(Stack* stack, Node* node);

// Проверяет, есть ли в стеке хоть один элемент.
bool isEmpty(Stack* stack);

// Удаляет элемент с верхушки стека и возвращает его.
// Вызывает ошибку, если элементов нет. Советуем проверять isEmpty перед использованием.
Node* pop(Stack* stack);

// Возвращает верхний элемент или NULL, если элементов нету.
Node* peek(Stack* stack);
