#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define S_FULL(top) (top == MAX-1)
#define S_EMPTY(top) (top == -1)
#define Q_FULL(rear) (rear == MAX-1)
#define Q_EMPTY(rear, front) (rear == front)

typedef struct node* link;
typedef struct node {
	link left, right;
	char item;
}node;

link S[MAX] = { NULL };
link root = NULL;
char input[MAX];
int top =-1, rear, front;

void push(link nNode) {
	if (S_FULL(top)) exit(1);
	S[++top] = nNode;
}

link pop() {
	if (S_EMPTY(top)) return NULL;
	return S[top--];
}

void enqueue(link nNode) {
	if (Q_FULL(rear)) exit(1);
	S[++rear] = nNode;
}

link dequeue() {
	if (Q_EMPTY(front, rear)) return NULL;
	return S[++front];
}

link eval() {
	int n = 0;
	char symbol = input[n++];
	
	while (symbol != '\0') {
		link nNode = (link)malloc(sizeof(node));
		if (!nNode) exit(1);
		nNode->left = nNode->right = NULL;
		nNode->item = symbol;

		if (symbol == '+' || symbol == '-' ||
			symbol == '%' || symbol == '/' ||
			symbol == '*') {
			nNode->right = pop();
			nNode->left = pop();
			push(nNode);
		}
		else {
			push(nNode);
		}
		symbol = input[n++];
	}
	return pop();
	
}

void iterative_preorder(link root) {
	//top = -1;
	while (1) {
		while (root) {
			printf("%c", root->item);
			push(root);
			root = root->left;
		}
		root = pop();
		if (!root) break;
		root = root->right;
	}
}

void levelorder(link root) {
	rear = front = -1;
	enqueue(root);
	while (1) {
		root = dequeue();
		if (root) {
			printf("%c", root->item);
			if (root->left) enqueue(root->left);
			if (root->right) enqueue(root->right);
		}
		else break;
	}
}

int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	char tmp;
	int k = 0;

	printf("the length of input string should be less than 80\n");
	printf("input string (postfix expression) : ");

	while (fscanf_s(fp, "%c", &tmp, 1) != EOF)
		input[k++] = tmp;

	for (int i = 0; i < k; i++)
		printf("%c", input[i]);

	root = eval();

	printf("\ncreating its binary tree\n");
	/*printf("\ninorder traversal\t: ");
	inorder(root);*/
	printf("\npreorder traversal\t: ");
	iterative_preorder(root);
	/*printf("\npostorder traversal\t: ");
	iterative_postorder(root);*/
	printf("\nlevelorder traversal\t: ");
	levelorder(root);
	return 0;
}