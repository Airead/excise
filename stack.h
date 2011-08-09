#ifndef STACK_H
#define STACK_H

#define STACKSIZE 100
#define STACKINCRESESIZE 20

typedef struct{
    int *contents;		/* stack contents */
    int *top;			/* stack length */
    int stackSize;		/* stack current size */
}*Stack, StackNode;

int stackInit(Stack *stack);
int stackDestroy(Stack *stack);
int stackClear(Stack stack);
int stackIsExist(const Stack stack);
int stackIsEmpty(const Stack stack);
int stackIsFull(const Stack stack);
int stackShow(const Stack stack);
int stackGetTop(const Stack stack);
int stackPush(Stack stack, int i);
int stackPop(Stack stack);

#endif
