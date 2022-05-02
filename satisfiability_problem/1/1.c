#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STACK 100
#define FALSE 0
#define TRUE 1
typedef enum {
	not, and, or, operand, eos
} logical;

typedef struct node* link;
typedef struct node {
	link left, right;
	char data;
	bool value;
} node;

link stack[MAX_STACK];
char list[20];
link root = NULL;
int top = -1;

void preorder(link root) {
	if (root) {
		printf("%c ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
void push(link node) {
	if (top == MAX_STACK - 1) return;
	else stack[++top] = node;
}

link pop() {
	if (top == -1) return NULL;
	else return stack[top--];
}

logical getToken(char* symbol, int* n) {
	*symbol = list[(*n)++];
	switch (*symbol) {
	case '~': return not;
	case '&': return and;
	case '|': return or;
	case '\0': return eos;
	default: return operand;
	}
}

link makeNode() {
	char symbol;
	int n =0;
	logical tokken = getToken(&symbol, &n);
	
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) return;

	nNode->value = false;
	nNode->left = NULL;
	nNode->right = NULL;
	nNode->data = symbol;

	while (tokken != eos) {
		
		if (tokken == operand) { 
			push(nNode);
		}
		else if(tokken == not) {
			nNode->right = pop();
			push(nNode);
		}
		else {
			nNode->right = pop();
			nNode->left = pop();
			push(nNode);
		}
		tokken = getToken(&symbol, &n);

		nNode = (link)malloc(sizeof(node));
		if (!nNode) return;
		nNode->left = NULL;
		nNode->right = NULL;

		nNode->value = false;
		nNode->data = symbol;
	}

	return pop();
}

bool int_to_bool(int data)
{
	return data ? true : false;
}

void postOrderEval(link node, int a, int b, int c) {
	if (node) {
		postOrderEval(node->left,a,b,c);
		postOrderEval(node->right, a, b, c);


		switch (node->data)
		{
		case'a': node->value = int_to_bool(a); break;
		case'b': node->value = int_to_bool(b); break;
		case'c': node->value = int_to_bool(c); break;
		case'&': node->value = node->left->value && node->right->value; break;
		case'|': node->value = node->left->value || node->right->value; break;
		case'~': node->value = !node->right->value; break;
		}
	}


}

int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	
	int k = 0;
	while (fscanf_s(fp, "%c", &list[k++], 1) != EOF);
	
	printf("input string(postfix)\t:");
	for (int i = 0; i < k; i++)
		printf("%c", list[i]);
	printf("\nfind true condition\n");

	root = makeNode();
	//preorder(root);
	int a, b, c;
	
	for (a = 0; a <= 1; a++)
		for (b = 0; b <= 1; b++)
			for (c = 0; c <= 1; c++) {
				postOrderEval(root,a,b,c);
				//printf("%d\n", root->value);
				if(root->value)
					printf("a = %d, b= %d, c= %d\n", a, b, c);
			}
}