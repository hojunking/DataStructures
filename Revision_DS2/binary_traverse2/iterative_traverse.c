#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define IS_FULL(top) (top == MAX-1)
#define IS_EMPTY(top)	(top == -1)
#define Q_FULL(rear) (rear == MAX-1)
#define Q_EMPTY(front, rear) (front == rear)

typedef struct node* link;
typedef struct node {
	link right, left;
	char item;
} node;

typedef enum {
	plus, minus, mult, divide, mod, operand, eos
} precedence;


link root = NULL;
link S[MAX] = { NULL };
char input[10]; 
int top, front, rear;

void push(link nNode) {
	if (IS_FULL(top)) exit(1);
	S[++top] = nNode;
}

link pop() {
	if (IS_EMPTY(top)) return NULL;
	return S[top--];
}

void enqueue(link nNode) {
	if (Q_FULL(rear)) exit(1);
	S[++rear] = nNode;
}

link dequeue() {
	if (Q_EMPTY(front,rear)) return NULL;
	return S[++front];
}

void levelorder(link root) {
	front = rear = -1;
	enqueue(root);
	while (1) {
		root = dequeue();
		if (root) {
			printf("%c", root->item);
			if (root->left)
				enqueue(root->left); 
			if (root->right)
				enqueue(root->right);
		}
		else break;
	}
}

void iterative_preorder(link root) {
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

void iterative_postorder(link root) {
	top = -1;
	link tmp = NULL;
	while (1) {
		while (root) {
			push(root);
			root = root->left;
		}
		root = pop();
		tmp = root;
		if (!root) break;

		if (root->right) {
			root = root->right;
			printf("%c", root->item);
			printf("%c", tmp->item);
			root = root->right;
		}
		else {
			root = root->right;
			printf("%c", tmp->item);
		}
	}
}

precedence getToken(int n, char* symbol) {
	*symbol = input[n];
	switch (*symbol) {
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return mult;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

link eval(void) {
	top = -1;
	int n = 0;
	char symbol;
	precedence token = getToken(n, &symbol);

	while (token != eos) {
		link nNode = (link)malloc(sizeof(node));
		if (!nNode) exit(1);
		nNode->item = symbol;

		if (token == operand) {
			nNode->left = NULL;
			nNode->right = NULL;
			push(nNode);
		}
		else {
			nNode->right = pop();
			nNode->left = pop();
			push(nNode);
		}
		token = getToken(++n, &symbol);
	}
	return pop(); //root
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