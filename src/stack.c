#include "stack.h"

#include <assert.h>
#include <stdlib.h>

typedef struct StackNode {
    Node* node;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* head;
} Stack;

Stack* createStack(void)
{
    Stack* stack = calloc(1, sizeof(*stack));
    assert(stack != NULL && "Ошибка выделения памяти :)");
    return stack;
}

void deleteStack(Stack* stack)
{
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}

void push(Stack* stack, Node* node)
{
    StackNode* newStackNode = malloc(sizeof(*newStackNode));
    assert(newStackNode != NULL && "Ошибка выделения памяти... оу сэд...");
    newStackNode->node = node;
    newStackNode->next = stack->head;
    stack->head = newStackNode;
}

bool isEmpty(Stack* stack)
{
    return stack->head == NULL;
}

Node* pop(Stack* stack)
{
    assert(!isEmpty(stack) && "Ошибка! Стек был пуст словно моя душа...");
    StackNode* popStackNode = stack->head;
    stack->head = popStackNode->next;
    Node* popNode = popStackNode->node;
    free(popStackNode);
    return popNode;
}

Node* peek(Stack* stack)
{
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->head->node;
}
