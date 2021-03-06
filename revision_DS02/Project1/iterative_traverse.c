#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define IS_FULL(top) (top == MAX-1)
#define IS_EMPTY(top)	(top == -1)
#define Q_FULL(rear) (rear == MAX-1)
#define Q_EMPTY(front, rear) (front == rear)

typedef struct node* link;
typedef struct node {
	char data;
	link left, right;
	int visited;
} node;

typedef enum {
	plus, minus, divide, mod, mult, operand, eos
} precedence;

link root = NULL;
link S[MAX] = { NULL };
int top, rear, front;
char input[10];

void push(link nNode) {
	if (IS_FULL(top)) exit(1);
	S[++top] = nNode;
}

link pop() {
	if (IS_EMPTY(top)) return NULL;
	return S[top--];
}

link eval(void) {
	int i = 0;

	char symbol = input[i];
	for (; symbol != '\0'; i++, symbol = input[i]) {
		
		link nNode = (link)malloc(sizeof(node));
		if (!nNode) exit(1);
		nNode->data = symbol;
		nNode->visited = 0;

		if (symbol =='+'|| symbol == '-'||
			symbol == '*'|| symbol == '%'||
			symbol == '/') {
			
			nNode->right = pop();
			nNode->left = pop();
			push(nNode);
		}
		else {
			nNode->left = NULL;
			nNode->right = NULL;
			push(nNode);
		}
	}
	return pop();
}

void iterative_preorder(link root) {
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
	//memset(S, NULL, MAX);
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

			if (!root->left) {
				printf("%c", root->data);
				printf("%c", tmp->data);
				tmp->visited = 1;
				root = root->right;
			}
			else push(tmp);
		}
		else {
			printf("%c", root->data);
			root->visited = 1;
			root = NULL;
		}
	}
}

void enqueue(link root) {
	if (Q_FULL(rear)) exit(1);
	S[++rear] = root;
}

link dequeue() {
	if (Q_EMPTY(front, rear)) return NULL;
	return S[++front];
}

void levelorder(link root) {
	memset(S, NULL, MAX);
	rear = front = -1;
	enqueue(root);

	while (1) {
		root = dequeue();
		if (root) {
			printf("%c", root->data);
			if (root->left)
				enqueue(root->left);
			if (root->right)
				enqueue(root->right);
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
	printf("\npostorder traversal\t: ");
	iterative_postorder(root);
	printf("\nlevelorder traversal\t: ");
	levelorder(root);
	return 0;
}