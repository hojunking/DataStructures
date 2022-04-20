#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80
/*
	후위표기식 연산 프로그램
*/


typedef enum 
{
	lparen,rparen,plus, minus,times, divide,
	mod,eos,operand
} precedence;

int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top;


void push(int item);
int pop();
precedence getToken(char* symbol, int* n);
int eval(void);

void push(int item) {
	stack[++top] = item;
	return;
}
int pop() {
	return stack[top--];
}

int main(void) {
	FILE* fp;
	FILE* fpw;
	char ch;
	if (fopen_s(&fpw, "output.txt", "w"))
		exit(1);

	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	printf("postfix expression : ");
	int a = 0;
	fputs("postfix expression : ",fpw);
	while (fscanf_s(fp,"%c",&ch,1) != EOF) {
		expr[a++] = ch;
		fputc(ch, stdout);
		fputc(ch, fpw);
	}
	fclose(fp);
	
	char result = eval() + '0';
	printf("\nthe evaluation value : %c", result);
	fputs("\nthe evaluation value : ", fpw);
	fputc(result, fpw);
	
	fclose(fpw);
}

int eval(void) {
	precedence token;

	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;

	token = getToken(&symbol, &n);
	while (token != eos) { //end of stack -'/0'
		if (token == operand)
			push(symbol - '0');//숫자로 바꿔준다
		else {
			op2 = pop();
			op1 = pop();
			switch (token) {
			case plus: push(op1 + op2);
				break;
			case minus: push(op1 - op2);
				break;
			case times: push(op1 * op2);
				break;
			case divide: push(op1 / op2);
				break;
			case mod: push(op1 % op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}

precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}
