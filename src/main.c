#include "bst.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    BST* tree = bstCreate();
    bstInsert(tree, 1);
    bstInsert(tree, 5);
    assert(bstContains(tree, 5));

    // Блок кода для теста итератора.
    bstInsert(tree, 4);
    bstInsert(tree, 2);
    bstInsert(tree, 3);
    Iterator* iter = iteratorInit(tree);
    while (iteratorHasNext(iter)) {
        printf("%d ", iteratorNext(iter));
    }
    printf("\n");
    iteratorFree(iter);

    bstInsert(tree, 3);
    bstInsert(tree, 8);
    bstInsert(tree, 11);
    bstInsert(tree, 42);
    bstInsert(tree, 15);
    // Прямой обход, должно напечатать: 1, 5, 3, 8, 11, 42, 15
    bstPreorder(tree);
    // Симметричный обход, должно напечатать: 1, 3, 5, 8, 11, 15, 42
    bstInorder(tree);
    // Обратный обход, должно напечатать: 3, 15, 42, 11, 8, 5, 1
    bstPostorder(tree);

    // провbstMax() ерка на максимальное и минимальные значения
    assert(bstMax(tree) == 42 && "Ошибка в выявлении максимального узла");
    assert(bstMin(tree) == 1 && "Ошибка в выявлении минимального узла");

    // проверка на корректность дерева
    assert(bstIsValid(tree) && "Ошибка в проверке корректности дерева");

    bstFree(tree);

    return 0;
}
