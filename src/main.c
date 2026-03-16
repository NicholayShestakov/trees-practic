#include "bst.h"
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    BST* tree = bstCreate();
    if (tree == NULL) {
        printf("Память под дерево не смогла выделиться.\n");
        return 1;
    }

    printf("Корректность отработки функций на пустом дереве:\n");
    printf("bstContains(tree, 42) = %d\n", bstContains(tree, 42));
    printf("bstPostorder(tree): ");
    bstPostorder(tree);
    printf("bstInorder(tree): ");
    bstInorder(tree);
    printf("bstPreorder(tree): ");
    bstPreorder(tree);
    printf("bstHeight(tree) = %d\n", bstHeight(tree));
    printf("bstSize(tree) = %d\n", bstSize(tree));
    bool minErr = false;
    printf("bstMin(tree, &minErr) = %d\n", bstMin(tree, &minErr));
    printf("minErr = %d\n", minErr);
    bool maxErr = false;
    printf("bstMax(tree, &maxErr) = %d\n", bstMax(tree, &maxErr));
    printf("maxErr = %d\n", maxErr);
    printf("bstDelete(tree, 42) = %d\n", bstDelete(tree, 42));
    printf("bstIsValid(tree) = %d\n", bstIsValid(tree));
    bool kthMinErr = false;
    printf("bstKthMin(tree, 1, &kthMinErr) = %d\n", bstKthMin(tree, 1, &kthMinErr));
    printf("kthMinErr = %d\n", kthMinErr);

    Iterator* emptyIter = iteratorInit(tree);
    if (emptyIter == NULL) {
        printf("Память под итератор не смогла выделиться.\n");
        return 1;
    }
    printf("iteratorHasNext(emptyIter) = %d\n", iteratorHasNext(emptyIter));
    bool iterErr = false;
    printf("iteratorNext(emptyIter) = %d\n", iteratorNext(emptyIter, &iterErr));
    printf("iterErr = %d\n\n", iterErr);
    iteratorFree(emptyIter);

    printf("Проверка функций в обычных условиях:\n");
    printf("bstInsert(tree, 42) = %d\n", bstInsert(tree, 42));
    printf("bstInsert(tree, 42) = %d\n", bstInsert(tree, 42));
    printf("bstInsert(tree, 41) = %d\n", bstInsert(tree, 41));
    printf("bstInsert(tree, 43) = %d\n", bstInsert(tree, 43));
    printf("bstContains(tree, 42) = %d\n", bstContains(tree, 42));
    printf("bstPostorder(tree): ");
    bstPostorder(tree);
    printf("bstInorder(tree): ");
    bstInorder(tree);
    printf("bstPreorder(tree): ");
    bstPreorder(tree);
    printf("bstHeight(tree) = %d\n", bstHeight(tree));
    printf("bstSize(tree) = %d\n", bstSize(tree));
    minErr = false;
    printf("bstMin(tree, &minErr) = %d\n", bstMin(tree, &minErr));
    printf("minErr = %d\n", minErr);
    maxErr = false;
    printf("bstMax(tree, &maxErr) = %d\n", bstMax(tree, &maxErr));
    printf("maxErr = %d\n", maxErr);
    printf("bstDelete(tree, 42) = %d\n", bstDelete(tree, 42));
    printf("bstPostorder(tree): ");
    bstPostorder(tree);
    printf("bstIsValid(tree) = %d\n", bstIsValid(tree));
    kthMinErr = false;
    printf("bstKthMin(tree, 2, &kthMinErr) = %d\n", bstKthMin(tree, 2, &kthMinErr));
    printf("kthMinErr = %d\n", kthMinErr);

    BST* treeToMerge = bstCreate();
    if (treeToMerge == NULL) {
        printf("Память под дерево для слияния не смогла выделиться.\n");
        return 1;
    }
    printf("Создано еще одно дерево для слияния.\n");
    printf("bstInsert(treeToMerge, 43) = %d\n", bstInsert(treeToMerge, 43));
    printf("bstInsert(treeToMerge, 42) = %d\n", bstInsert(treeToMerge, 42));
    BST* mergedTree = bstMerge(tree, treeToMerge);
    if (mergedTree == NULL) {
        printf("Память под слияние не смогла выделиться.\n");
        return 1;
    }
    printf("Деревья слиты.\n");
    printf("bstPostorder(mergedTree): ");
    bstPostorder(mergedTree);
    bstFree(treeToMerge);
    bstFree(mergedTree);

    Iterator* iter = iteratorInit(tree);
    if (iter == NULL) {
        printf("Память под итератор не смогла выделиться.\n");
        return 1;
    }
    printf("iteratorHasNext(iter) = %d\n", iteratorHasNext(iter));
    iterErr = false;
    printf("iteratorNext(iter) = %d\n", iteratorNext(iter, &iterErr));
    printf("iterErr = %d\n\n", iterErr);
    iteratorFree(iter);

    bstFree(tree);

    return 0;
}
