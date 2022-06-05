#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE 100
typedef struct node* link;

typedef struct node {
	link left;
	link right;
	char data;
} node;
link root = NULL;
link queue[MAX_QUEUE];
int front = -1, rear = -1;

void preorder(node* root) {
	if (root) {
		printf("%c ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
void inorder(node* root) {
	if (root) {
		inorder(root->left);
		printf("%c ", root->data);
		inorder(root->right);
	}
}
void postorder(node* root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%c ", root->data);
	}
}
int isFull() {
	return rear == MAX_QUEUE - 1;
}
void enqueue(char data) {
	if (isFull())
		printf("queue is full!");
	else {
		node* nNode = (node*)malloc(sizeof(node));
		if (!nNode) return;

		nNode->data = data;
		nNode->left = NULL;
		nNode->right = NULL;
		queue[++rear] = nNode;
	}
}

void dequeue() {
	front++;
}

void insertNode(int n) {
	root = queue[++front];
	for (int i = 1; i < n; i++) {

		if (queue[front]->left == NULL) {
			queue[front]->left = queue[i];
		}
		else if (queue[front]->right == NULL) {
			queue[front]->right = queue[i];
			dequeue();
		}
	}
	return;
}

int main(void) {
	printf("creating a complete binary tree\n");
	
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	char temp;
	int cnt = 0;
	while (fscanf_s(fp, "%c", &temp, 1) != EOF) {
		enqueue(temp);
		cnt++;
	}
	insertNode(cnt);
	printf("three binary tree traversals\n");
	printf("inorder traversal\t: ");
	inorder(root);
	printf("\npreorder traversal\t: ");
	preorder(root);
	printf("\npostorder traversal\t: ");
	postorder(root);
}