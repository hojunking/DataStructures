#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define Q_FULL(rear) (rear == MAX-1)
#define Q_EMPTY(front, rear) (front == rear)
#define S_FULL(top) (top == MAX-1)
#define S_EMPTY(top) (top == -1)

typedef struct node* link;
typedef struct node {
	link left, right;
	char data;
	int visited;
} node;

link S[MAX] = { NULL };
link root;

int front, rear, top, n;

void enqueue(link nNode) {
	if (Q_FULL(rear)) exit(1);
	S[++rear] = nNode;
}

link dequeue() {
	if (Q_EMPTY(front, rear)) return NULL;
	return S[++front];
}

void push(link nNode) {
	if (S_FULL(top)) exit(1);
	S[++top] = nNode;
}

link pop() {
	if (S_EMPTY(top)) return NULL;
	return S[top--];

}

void makeTree() {
	root = S[0];
	link tmp = dequeue();
	for (int i = 1; i < n; i++) {
		if (!tmp->left) tmp->left = S[i];
		
		else if (!tmp->right) {
			tmp->right = S[i];
			tmp = dequeue();
		}
	}
}
void makeNode(char item) {
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) exit(1);
	nNode->left = NULL;
	nNode->right = NULL;
	nNode->data = item;
	nNode->visited = 0;
	enqueue(nNode);
}

void inorder(link root) {
	if (root) {
		inorder(root->left);
		printf("%c ", root->data);
		inorder(root->right);
	}
}

void iterative_preorder(link root) {
	top = -1;
	while (1) {
		while (root) {
			printf("%c ", root->data);
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

			if (root->right) push(tmp);
			else {
				printf("%c ", root->data);
				printf("%c ", tmp->data);
				tmp->visited = 1;
				root = NULL;
			}
		}
		else {
			printf("%c ", root->data);
			root->visited = 1;
			root = NULL;
		}
	}
}

void levelorder(link root) {
	rear = front = -1;

	enqueue(root);
	while (1) {
		root = dequeue();
		if (root) {
			printf("%c ", root->data);
			if (root->left) enqueue(root->left);
			if (root->right) enqueue(root->right);
		}
		else break;
	}
}

int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r")) exit(1);

	n = 0;
	char tmp;
	front = rear = -1;
	while (1) {
		n++;
		tmp = fgetc(fp);
		if (tmp == EOF) break;
		makeNode(tmp);
	}
	makeTree();
	printf("three binary tree traversals\n");
	printf("inorder traversal\t: ");
	inorder(root);
	printf("\npreorder traversal\t: ");
	iterative_preorder(root);
	printf("\npostorder traversal\t: ");
	iterative_postorder(root);
	//postorder(root);
	printf("\nlevel traversal\t\t: ");
	levelorder(root);

}