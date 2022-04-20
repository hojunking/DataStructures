#define _CRT_SECURE_NO_WARNINGS
/*
    중위표기법 -> 후위표기로 변환
    및 연산 프로그램
    
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_STACK 100
#define MAX_EXPR_SIZE 80
#define FALSE 0
#define TRUE 0
char expr[MAX_EXPR_SIZE];
int stack[MAX_SIZE_STACK];
int top;

void init() {
    top = -1;
}

int is_empty() {
    return top == -1;
}

int is_full() {
    return top == MAX_SIZE_STACK - 1;
}

void push(int item) {
    if (is_full())
        exit(1);
    stack[++top] = item;
}

int pop() {
    if (is_empty())
        exit(1);
    return stack[top--];
}

int peek() {
    if (is_empty())
        exit(1);
    return stack[top];
}

int prec(char op) {
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

void postfix(char exp[]) {
    FILE* fpw;
    if (fopen_s(&fpw, "output.txt", "w"))
        exit(1);
    int i;
    char ch, top;
    int len = (int)strlen(exp);
    init();

    for (i = 0; i < len; i++) {
        ch = (int)exp[i];

        switch (ch) {
        case '+': case '-': case '*': case '/':
            while (!is_empty() && prec(peek()) >= prec(ch)) {
                top = pop();
                printf("%c", top);
                fputc(top, fpw);
            }
            push(ch);
            break;

        case '(':
            push(ch);
            break;
        case ')':
            top = pop();
            while (top != '(') {
                printf("%c", top);
                fputc(top, fpw);
                top = pop();
            }
            break;

        default:
            printf("%c", ch);
            fputc(ch, fpw);
            break;
        }
    }

    while (!is_empty()) {
        char temp = pop();
        printf("%c", temp);
        fputc(temp, fpw);

    }
    fclose(fpw);
}

int main() {
    FILE* fp;
    
    

    char ch;
    if (fopen_s(&fp, "input.txt", "r"))
        exit(1);
    printf("<<<<<<<< infix to posfix >>>>>>>>\n");
    printf("infix expression   :");
    int a = 0;
    
    while (EOF != (ch = fgetc(fp))) {
        expr[a++] = ch;
        fputc(ch, stdout);
    }
    printf("\npost expression   :");
    postfix(expr);
    fclose(fp);
    return 0;
}