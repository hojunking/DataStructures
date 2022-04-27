#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct node* link;

typedef struct node {
	link left, right;
	char item;
	int visited;
} node;

typedef enum {
	plus, minus, times, divide, mode, eos, operand
} precedence;

link stack[MAX_SIZE];
int top = -1;
link root = NULL;
char input[10];


int isEmpty() {
	return top == -1;
}
int isFull() {
	return top == MAX_SIZE - 1;
}

void push(link n) {
	if (isFull()) return NULL;
	else
		stack[++top] = n;
}

link pop() {
	if (isEmpty()) return NULL;
	else
		return stack[top--];
}
int iterative_preorder(link root) {
	int cnt = 0;
	while (1)
	{
		for (; root; root = root->left)
		{
			printf("%c", root->item);
			cnt++;
			push(root);
		}
		root = pop();

		if (!root) break;

		//printf("%c ", root->item);
		root = root->right;
	}
	return cnt;
}
int iterative_postorder(link root) {
	top = -1;
	int cnt = 0;
	while (1)
	{	
		while(root != NULL && root->visited != 1)
		{
			push(root);
			cnt++;
			root = root->left;
		}
		root = pop();

		if (!root) break;

		if (root->right != NULL) {
			if (root->right->visited == 1) {
			printf("%c", root->item);
			root->visited = 1;
			root = NULL;
			}
			else {
				cnt++;
				push(root);
				root = root->right;
			}
		}
		else {
			printf("%c", root->item);
			root->visited = 1;
			root = NULL;
		}
	}
	return cnt;
}

precedence getToken(char* symbol, int* n) {
	*symbol = input[(*n)++];
	switch (*symbol) {
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mode;
	case '\0': return eos;
	default: return operand;
	}
}

link eval(void) {

	char symbol;
	int n = 0;
	precedence token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand) {
			link nNode = (link)malloc(sizeof(node));
			if (!nNode) return;

			nNode->item = symbol;
			nNode->left = NULL;
			nNode->right = NULL;
			push(nNode);
		}
		else {
			//operator
			link nNode = (link)malloc(sizeof(node));
			if (!nNode) return;

			nNode->item = symbol;
			nNode->right = pop();
			nNode->left = pop();
			push(nNode);
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}


int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	char temp;
	int cnt = 0;
	printf("the length of input string should be less than 80\n");
	printf("input string (postfix expression) : ");

	while (fscanf_s(fp, "%c", &temp, 1) != EOF) {
		//fputc(temp,stdout);
		input[cnt++] = temp;
	}
	for (int i = 0; i < cnt; i++)
		printf("%c", input[i]);
	root = eval();
	printf("\ncreating its binary tree\n");
	printf("\niterative preorder traversal\t: ");
	cnt = iterative_preorder(root);
	printf("\npush_cnt =%d", cnt);
	printf("\niterative postorder traversal\t: ");
	cnt = iterative_postorder(root);
	printf("\npush_cnt =%d", cnt);

}