#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
#define IS_FULL(top) (top == MAX-1)
#define IS_EMPTY(top) (top == -1)

typedef struct node* link;
typedef struct node {
	link left, right;
	char data;
	int visited;
} node;

link S[MAX] = { NULL };
link root = NULL;
char input[MAX];
int top;

void push(link nNode) {
	if (IS_FULL(top)) exit(1);
	S[++top] = nNode;
}

link pop() {
	if (IS_EMPTY(top)) return NULL;
	return S[top--];
}

link eval(void) {
	char symbol;
	int n = 0; top = -1;
	symbol = input[n++];
	while (symbol != '\0') {
		link nNode = (link)malloc(sizeof(node));
		if (!nNode) exit(1);

		nNode->data = symbol;
		nNode->visited = 0;

		if (symbol == '+' || symbol == '-' ||
			symbol == '%' || symbol == '/' || symbol == '*') {
			nNode->right = pop();
			nNode->left = pop();
			push(nNode);
		}
		else {
			nNode->right = NULL;
			nNode->left = NULL;
			push(nNode);
		}
		symbol = input[n++];
	}
	return pop();
}

void iterative_preorder(link root) {
	memset(S, NULL, MAX);
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

void iterative_postorder(link root) {
	top = -1;
	link tmp = NULL;
	while (1) {
		while (root) {
			push(root);
			root = root->left;
		}
		root = pop();
		if (!root) break;
		tmp = root;

		if (root->right && root->right->visited == 0) {
			root = root->right;

			if (!root->right) {
				printf("%c", root->data);
				printf("%c", tmp->data);
				tmp->visited = 1;
				root = root->right;
			}
			else push(tmp);
		}
		else {
			printf("%c", tmp->data);
			root->visited = 1;
			root = NULL;
		}
	}
}

int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	char temp;
	int cnt = 0;
	printf("the length of input string should be less than 80\n");
	printf("input string (postfix expression) : ");

	while (1) {
		temp = fgetc(fp);
		if (temp == EOF)
			break;
		input[cnt++] = temp;
	}

	for (int i = 0; i < cnt; i++)
		printf("%c", input[i]);
	root = eval();
	printf("\ncreating its binary tree\n");
	printf("\niterative preorder traversal\t: ");
	iterative_preorder(root);
	printf("\niterative postorder traversal\t: ");
	iterative_postorder(root);

}