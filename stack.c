#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define STACKTEST 0

int stackInit(Stack *pstack){
    /* init stack */
    Stack stack;
    
    stack = malloc(sizeof(StackNode)); /* return a pointer of Stack */
    if(!stack){
	printf("StackInit error: init stack fail\n");
	exit(0);
    }
    /* init stack contents */
    stack->contents = malloc(STACKSIZE * sizeof(int));
    if(stack->contents == NULL){ /* fail */
	printf("stackInit error: fail to malloc\n"); 
    }
    stack->top = stack->contents;
    stack->stackSize = STACKSIZE;    
    *pstack = stack;
    return 0;
}

int stackDestroy(Stack *pstack){
    /* destroy stack */
    Stack stack = *pstack;

    if(!stackIsExist(stack)){	/* not exist */
	printf("stackDestroy error: stack not exist\n");
	exit(0);
    }
    free(stack->contents);	/* free contents */
    free(*pstack);	/* free stack */
    *pstack = NULL;	/* set NULL */
    return 0;
}

int stackClear(Stack stack){
    /* clear stack */
    if(!stackIsExist(stack)){		/* not exist */
	printf("statckClear error: stack not exist\n");
	exit(0);
    }
    stack->top = stack->contents;
    
    return 0;
}

int stackIsExist(const Stack stack){
    /* if stack exist return 1, else return 0 */
    if(stack != NULL){
	return 1;
    }else{
	return 0;
    }
}

int stackIsEmpty(const Stack stack){
    /* if stack emtpy return 1, else return 0 */
    if(!stackIsExist(stack)){		/* not exist */
	printf("stackIsEmpty error: stack not exist\n");
	exit(0);
    }
    if(stack->contents == stack->top){
	return 1;
    }else{
	return 0;
    }
}

int stackIsFull(const Stack stack){
    /* stack full return 1, else return 0 */
    if(!stackIsExist(stack)){		/* not exist */
	printf("stackIsFull error: stack not exist\n");
	exit(0);
    }
    
    if(stack->top - stack->contents == stack->stackSize){
	return 1;
    }else{
	return 0;
    }
}

int stackShow(const Stack stack){
    /* show contents of stack */
    int *p;
    if(!stackIsExist(stack)){
	printf("stack not exist\n");
	return 0;
    }
    if(stackIsEmpty(stack)){
	printf("stack empty\n");
	return 0;
    }
    p = stack->contents;
    printf("stack contents:\n");
    while(p < stack->top){
	printf("%4d", *p++);
    }
    printf("\n");
    return 0;
}

int stackGetTop(const Stack stack){
    /* return top elem */
    if(!stackIsExist(stack)){		/* not exist */
	printf("stackGetTop error: stack not exist\n");
	exit(0);
    }
    if(stackIsEmpty(stack)){
	printf("stackGetTop error: stack empty\n");
	exit(0);
    }
    return *(stack->top - 1);
}

int stackPush(Stack stack, int i){
    /* push elem into stack */
    int *newBase;

    if(!stackIsExist(stack)){		/* not exist */
	printf("stackPush error: stack not exist\n");
	exit(0);
    }
    if(stackIsFull(stack)){	/* full and realloc */
	newBase = (int *)realloc(stack->contents, (stack->stackSize + STACKINCRESESIZE) * sizeof(int));
	if(newBase == NULL){
	    printf("stackPush error: fail to relloc\n");
	    return 0;
	}
	stack->top = newBase + stack->stackSize; /* important! changed top */
	stack->contents = newBase;
	stack->stackSize = stack->stackSize + STACKINCRESESIZE;
    }
    *stack->top++ = i;
    return 1;
}

int stackPop(Stack stack){
    /* pop elem from stack */
    if(!stackIsExist(stack)){		/* not exist */
	printf("stackPop error: stack not exist\n");
	exit(0);
    }
    if(stackIsEmpty(stack)){	/* empty */
	printf("stackPop error: stack empty\n");
	exit(0);
    }
    return *--stack->top;
}


#if STACKTEST

int pt(char *str){
    /* test print */
    printf("*******");
    printf("%s", str);
    printf("*******\n");
    return 0;
}

int main(void){
    /* test stack */
    Stack st = NULL;
    int i;
    
    pt("test stackInit()");
    stackInit(&st);
    stackShow(st);
    stackPush(st, 1);
    stackShow(st);
    stackDestroy(&st);
    stackShow(st);
    /* init stack again */
    stackInit(&st);
    pt("test stackPush()");
    for(i = 0; i < 5; i++){
	stackPush(st, i);
    }
    stackShow(st);
    pt("test stackPop()");
    for(i = 0; i < 3; i++){
	printf("%4d", stackPop(st));
    }
    printf("\n");
    stackShow(st);
    pt("test stackGetTop()");
    printf("%d\n",stackGetTop(st));
    printf("%d\n",stackGetTop(st));
    pt("test stackClear()");
    stackClear(st);
    stackShow(st);
    pt("test stack Full");
    for(i = 0; i < 800; i++){
	stackPush(st, i);
    }
    for(i = 0; i < 500; i++){
	printf("%4d",stackPop(st));
    }
    printf("\n");
    stackShow(st);
    pt("Clear");
    stackClear(st);
    stackShow(st);
    pt("Destroy");
    stackDestroy(&st);
    stackShow(st);
}

#endif
