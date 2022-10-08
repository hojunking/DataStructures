#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK 100
typedef struct node* link;
typedef struct node{
	link right, left;
	char data;
}node;
link stack[MAX_STACK];
char list[10];
int top = -1;
link root = NULL;

typedef enum {
	plus,minus,divide,mod,eos,mult,operand
} precedence;
/* 
	postfix to expression infix, prefix
	recursively using Binary tree
*/
int isEmpty() {
	return top == -1;
}
int isFull() {
	return top == MAX_STACK - 1;
}

void push(link nNode) {
	if (isFull()) return;
	else {
		stack[++top] = nNode;
		return;
	}
}

link pop() {
	if (isEmpty()) return NULL;
	else return stack[top--];
}


precedence getToken(char* symbol,int *n) {
	*symbol = list[(*n)++];
	switch (*symbol) {
	case '+': return plus;
	case '-': return minus;
	case '*': return mult;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

link eval(void) {
	char symbol;
	int n =0;
	precedence token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand) {
			link nNode = (link)malloc(sizeof(node));
			if (!nNode) exit(1);
			nNode->data = symbol;
			nNode->right = NULL;
			nNode->left = NULL;
			push(nNode);
		}
		else {
			link nNode = (link)malloc(sizeof(node));
			if (!nNode) return;
			nNode->data = symbol;
			nNode->right = pop();
			nNode->left = pop();
			push(nNode);
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}

void iterPreorder(link root) {
	top = -1;
	while (1) {
		while (root) {
			printf("%c", root->data);
			push(root);
			root = root->left;
		}
		root = pop();
		if (!root) break;
		root = root->right;
	}
}
void iterInorder(link root) {
	top = -1;
	while (1) {
		while (root) {
			push(root);
			root = root->left;
		}
		root = pop();
		if (!root) break;
		printf("%c", root->data);
		root = root->right;
	}
}
void iterPostorder(link root) {
	top = -1;
	int cnt = 0;
	link temp =NULL;
	while (1) {
		while (root) {
			push(root);
			root = root->left;
		}
		if (top == -1) break;
		root = pop();
		temp = root;
		if (!root) break;

		if (root->right != NULL) {
			root = root->right;
			cnt++;
			printf("%c", root->data);
			cnt++;
			printf("%c", temp->data);
			root = root->right;
		}
		else {
			root = root->right;
			cnt++;
			printf("%c", temp->data);
		}
	}
	printf("\n%d", cnt);
}


int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	int cnt = 0;
	while (fscanf_s(fp, "%c", &list[cnt++], 1) != EOF);

	printf("input string (postfix expression) : ");
	for (int i = 0; i < cnt; i++)
		printf("%c", list[i]);

	printf("\ncreating its binary tree\n");
	root = eval();
	printf("\npreorder traversal\t:");
	iterPreorder(root);
	printf("\ninorder traversal\t:");
	iterInorder(root);
	printf("\npostorder traversal\t:");
	iterPostorder(root);
		
}