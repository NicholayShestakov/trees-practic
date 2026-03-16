1.
В публичный интерфейс войдут функции:

BST* bstCreate(void);
void bstInsert(BST* tree, int value);
bool bstContains(BST* tree, int value);
void bstFree(BST* tree);
int bstSize(BST* tree);
void bstDelete(BST* tree, int value);
int bstMin(BST* tree);
int bstMax(BST* tree);

// Итератор
Iterator* iteratorInit(BST* tree);
bool iteratorHasNext(Iterator* iterator);
int iteratorNext(Iterator* iterator);
void iteratorFree(Iterator* iterator);

Функции как детали реализации:

// Рекурсивные вспомогательные функции
void bstFreeRecursion(Node* node);
int bstHeightRecursion(Node* node);
void addLeftStickInStack(Stack* stack, Node* node);

// Обходы (детали)
void bstPreorderRecursion(Node* node);
void bstInorderRecursion(Node* node);
void bstPostorderRecursion(Node* node);

// Проверка инвариантов (отладка)
bool bstIsValidRecursion(Node* node, int* min, int* max);
bool bstIsValid(BST* tree);

// Вспомогательные для удаления
Node* parentRecursive(Node* parent, Node* node);
Node* findParent(BST* tree, Node* node);
Node* minRightTree(Node* node);

// Специфические/опасные функции
int* getAllNodesFromTree(BST* tree);
BST* bstMerge(BST* tree1, BST* tree2);
int bstKthMin(BST* tree, int k);
int bstKthMinRecursion(Node* node, int* k);

// Высота — специфична для дерева
int bstHeight(BST* tree);

// Конкретные обходы
void bstPostorder(BST* tree);
void bstInorder(BST* tree);
void bstPreorder(BST* tree);

Да, функции публичного интерфейса могут и даже должны иметь более абстрактные имена. Если мы реализуем АТД «множество», названия должны соответствовать именно этой абстракции, а пользователю не обязательно знать, что внутри оно реализовано с помощью бинарного дерева поиска. Например, вместо bstCreate и bstFree можно было бы объявить setCreate, setFree и т.д.

2.
Следующие функции не имеют смысла в интерфейсе множества, так как отражают специфику древовидной реализации:

bstPreorder, bstInorder, bstPostorder — порядки обхода характерны только для деревьев
bstHeight — высота есть у дерева, но не у множества
bstKthMin — поиск k-го минимального элемента предполагает упорядоченность
bstIsValid — проверка корректности структуры дерева
bstMerge — операция слияния, специфичная для деревьев (хотя объединение множеств может быть полезно, но реализация должна быть универсальной)

3.
Чтобы можно было безболезненно заменить BST на другую реализацию, не меняя исходный код, требуется обеспечить полную инкапсуляцию через единый интерфейс АТД. В нашей реализации в публичном заголовочном файле находятся функции специфичные для бинарных деревьев поиска. Поэтому в интерфейсе нужно оставить только универсальные операции: создание, вставка, проверка на наличие элемента, удаление, получение размера и итератор для обхода элементов. Функции, отражающие внктреннюю структуру дерева(например, нахождение k - го минимального элемента или слияния деревьев) должны быть убраны из публичного интерфейса, так как для других реализаций они не понадобятся.
