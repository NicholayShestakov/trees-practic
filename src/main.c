#include "bst.h"
#include <assert.h>

int main(void)
{
    BST* tree = bstCreate();
    assert(!bstContains(tree, 1));
    bstInsert(tree, 1);
    assert(bstContains(tree, 1));
    bstInsert(tree, 5);
    assert(bstContains(tree, 5));
    bstFree(tree);

    return 0;
}
