#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct node* link;
typedef struct node {
	link left, right;
	char data;
}node;
link stack[MAX_SIZE];
link root = NULL;
char list[20];
int top = -1;

typedef enum 
{
	plus,minus,mult,mod,divide,operand,eos
}precedence;

precedence getToken(char* symbol, int* n) {
	*symbol = list[(*n)++];
	switch (*symbol) {
	case '+':return plus;
	case '-': return minus;
	case '*': return mult;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}
void push(link nNode) {
	if (top == MAX_SIZE - 1) return;
	else
	stack[++top] = nNode;
}

link pop() {
	if (top == -1) return NULL;
	else return stack[top--];
}

link eval(void) {
	char symbol;
	int n = 0;
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
			if (!nNode) exit(1);
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
	link temp;
	while (1) {
		while (root) {
			push(root);
			root = root->left;
		}
		root = pop();
		temp = root;
		if (!root) break;

		if (root->right != NULL) {
			root = root->right;
			printf("%c", root->data);
			printf("%c", temp->data);
			root = root->right;
		}
		else {
			root = root->right;
			printf("%c", temp->data);
		}
	}
}

void levelOrder(link root) {

}
int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	int k = 0;
	while (fscanf_s(fp, "%c", &list[k++],1) != EOF);
	for (int i = 0; i < k; i++)
		printf("%c", list[i]);

	root = eval();
	printf("\nPreorder: ");
	iterPreorder(root);
	printf("\nInorder: ");
	iterInorder(root);
	printf("\nPostorder: ");
	iterPostorder(root);

}