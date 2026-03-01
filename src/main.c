#include "bst.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    BST* tree = bstCreate();
    assert(!bstContains(tree, 1));
    bstInsert(tree, 1);
    assert(bstContains(tree, 1));
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

    bstFree(tree);

    return 0;
}
