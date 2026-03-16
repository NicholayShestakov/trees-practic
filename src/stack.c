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
    return calloc(1, sizeof(Stack));
}

void deleteStack(Stack* stack)
{
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}

bool push(Stack* stack, Node* node)
{
    StackNode* newStackNode = malloc(sizeof(*newStackNode));
    if (newStackNode == NULL) {
        return false;
    }

    newStackNode->node = node;
    newStackNode->next = stack->head;
    stack->head = newStackNode;

    return true;
}

bool isEmpty(Stack* stack)
{
    return stack->head == NULL;
}

Node* pop(Stack* stack)
{
    if (isEmpty(stack)) {
        return NULL;
    }

    StackNode* popStackNode = stack->head;
    Node* popNode = popStackNode->node;
    stack->head = popStackNode->next;
    free(popStackNode);

    return popNode;
}
