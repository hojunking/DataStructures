#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE 100

typedef struct node* nodeLink;

typedef struct node {
	nodeLink left, right;
	char item;
}node;

nodeLink queue[MAX_QUEUE];
nodeLink root = NULL;
int front = -1, rear = -1;
int isFull() {
	return rear == MAX_QUEUE - 1;
}

int isEmpty() {
	return front == rear;
}
void dequeue() {
	front++;
}

void makeTree(int n) {
	root = queue[++front];
	for (int i = 1; i < n; i++) {
		if (queue[front]->left == NULL)
			queue[front]->left = queue[i];
		
		else if(queue[front]->right == NULL) {
			queue[front]->right = queue[i];
			dequeue();
		}
		else {
			printf("queueisEmpty!\n");
			return;
		}
	}
	return;
}

void enqueue(char item) {
	if (isFull()) printf("queue is Full!\n");

	nodeLink nNode = (nodeLink)malloc(sizeof(node));
	if (!nNode) return;
	nNode->item = item;
	nNode->left = NULL;
	nNode->right = NULL;
	queue[++rear] = nNode;
	return;
}

void preorder(nodeLink root) {
	if (root) {
		printf("(%p %p %c %p)\n", root->left, root->right, root->item, root);
		preorder(root->left);
		preorder(root->right);
	}
}
void inorder(nodeLink root) {
	if (root) {
		inorder(root->left);
		printf("(%p %p %c %p)\n", root->left, root->right, root->item, root);
		inorder(root->right);
	}
}
void postorder(nodeLink root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("(%p %p %c %p)\n", root->left, root->right, root->item, root);
	}
}


int main(void) {
	char list[] = { 'A','B','C','D','E' };
	int n = sizeof(list);
	for (int i = 0; i < n; i++)
		enqueue(list[i]);
	printf("creating a complete binary tree\n");
	printf("three binary tree traversals\n");
	makeTree(n);
	printf("inorder traversal\t:\n");
	inorder(root);
	printf("\npreorder traversal\t:\n");
	preorder(root);
	printf("\npostorder traversal\t:\n");
	postorder(root);
}