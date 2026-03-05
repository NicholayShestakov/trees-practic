#include "bst.h"
#include <assert.h>

int main(void)
{
    BST* tree = bstCreate();
    assert(!bstContains(tree, 1));
    bstInsert(tree, 1);
    assert(bstContains(tree, 1));
    bstInsert(tree, 5);
    bstInsert(tree, 6);
    bstInsert(tree, 7);
    assert(bstContains(tree, 5));
    assert(bstHeight(tree) == 3 && "Неправильная высота дерева");
    bstFree(tree);
    return 0;
}
