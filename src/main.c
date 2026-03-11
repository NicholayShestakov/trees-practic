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
    // проверка на размер дерева
    assert(bstSize(tree) == 7 && "Ошибка в подсчете размера дерева");
    BST* emptyTree = bstCreate();
    assert(bstSize(emptyTree) == 0 && "Ошибка в подсчете размера пустого дерева");

    // Прямой обход, должно напечатать: 1, 5, 3, 8, 11, 42, 15
    bstPreorder(tree);
    // Симметричный обход, должно напечатать: 1, 3, 5, 8, 11, 15, 42
    bstInorder(tree);
    // Обратный обход, должно напечатать: 3, 15, 42, 11, 8, 5, 1
    bstPostorder(tree);
    bstFree(tree);

    // проверка на слияние деревьев
    BST* tree1 = bstCreate();
    BST* tree2 = bstCreate();
    bstInsert(tree1, 1);
    bstInsert(tree1, 5);
    bstInsert(tree1, 3);
    bstInsert(tree1, 8);

    bstInsert(tree2, 11);
    bstInsert(tree2, 42);
    bstInsert(tree2, 15);

    BST* tree1MergeTree2 = bstMerge(tree1, tree2);
    assert(bstContains(tree1MergeTree2, 1) && "В дереве нет нужного элемента");
    assert(bstContains(tree1MergeTree2, 5) && "В дереве нет нужного элемента");
    assert(bstContains(tree1MergeTree2, 3) && "В дереве нет нужного элемента");
    assert(bstContains(tree1MergeTree2, 8) && "В дереве нет нужного элемента");
    assert(bstContains(tree1MergeTree2, 11) && "В дереве нет нужного элемента");
    assert(bstContains(tree1MergeTree2, 42) && "В дереве нет нужного элемента");
    assert(bstContains(tree1MergeTree2, 15) && "В дереве нет нужного элемента");
    // должно напечатать 1, 5, 3, 8, 11, 42, 15
    bstPreorder(tree1MergeTree2);
    free(tree1MergeTree2);
    free(emptyTree);
    bstFree(tree1);
    bstFree(tree2);
    return 0;
}
