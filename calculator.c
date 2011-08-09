#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int isSymbol(char ch){
    /* symbol return 1, else return 0 */
    char symbols[10] = "+-*/()#";
    char *p;

    p = symbols;
    while(*p != '\0'){
	if(ch == *p++){
	    return 1;
	}
    }
    return 0;
}

int execute2(int num1, int num2, char sym){
    /* execute operation */
    switch(sym){
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    case '/': return num1 / num2;
    }
}

int symToNum(char sym){
    if(sym == '+') return 0;
    if(sym == '-') return 1;
    if(sym == '*') return 2;
    if(sym == '/') return 3;
    if(sym == '(') return 4;
    if(sym == ')') return 5;
    if(sym == '#') return 6;
}

char precede(char sym1, char sym2){
    /* + - * / ( ) # */
    char pre[7][7] = {{'>', '>', '<', '<', '<', '>', '>'},
		      {'>', '>', '<', '<', '<', '>', '>'},
		      {'>', '>', '>', '>', '<', '>', '>'}, 
		      {'>', '>', '>', '>', '<', '>', '>'},
		      {'<', '<', '<', '<', '<', '=', ' '}, 
		      {'>', '>', '>', '>', ' ', '>', '>'}, 
		      {'<', '<', '<', '<', '<', ' ', '='}};
    return pre[symToNum(sym1)][symToNum(sym2)];
}

int evaluateExpression(const char *exp){
    /* 自述表达式算符优先算法。 */
    Stack numStack;
    Stack symbolStack;
    const char *p;
    int num1,num2,sym;
    
    /* init Stack */
    stackInit(&numStack);
    stackInit(&symbolStack);

    p = exp;
    stackPush(symbolStack, *p++);
    while(*p != '#' || stackGetTop(symbolStack) != '#'){
	if(!isSymbol(*p)){	/* 不是运算符则进栈 */
	    stackPush(numStack, *p-'0');
	    p++;
	}else{
	    switch(precede(stackGetTop(symbolStack), *p)){
	    case '<':		/* 栈顶元素优先权低 */
		stackPush(symbolStack, *p);
		p++;
		break;		/* 脱括号并接收下一字符 */
	    case '=':
		stackPop(symbolStack); 
		*p++;
		break;
	    case '>':		/* 退栈并将运算结果入栈 */
		num1 = stackPop(numStack);
		num2 = stackPop(numStack);
		sym = stackPop(symbolStack);
		stackPush(numStack, execute2(num1, num2, sym));
		break;
	    }
	}
    }
    return stackGetTop(numStack);
}

int main(void){
    int res;
    char str[100];
    char buf[100];
    
    gets(str);
    sprintf(buf, "#%s#", str);
    printf("%s\n", buf);
        while(strcmp(str, "")){
	    res = evaluateExpression(buf);
	    printf("result = %d\n", res);
	    gets(str);
	    sprintf(buf, "#%s#", str);
	}
}
