#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_BST 20

typedef struct node* link;

typedef struct  {
	int key, item;
} element;

typedef struct node {
	element data;
	link left, right;
} node;

link root = NULL;

void insert_node(int key) {
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) return;
	
	nNode->left = NULL;
	nNode->right = NULL;
	nNode->data.key = key;

	if (!root) {
		root = nNode;
		return;
	}

	link path = root;
	while (path) {
		if (key == path->data.key) return;
		else if (key < path->data.key) {
			if (!path->left) {
				path->left = nNode;
				return;
			}
			else path = path->left;
		}
		else {
			if (!path->right) {
				path->right = nNode;
				return;
			}
			else path = path->right;
		}
	}
}

int BST_search(int key) {
	link tmp = root;

	while (tmp) {
		if (key == tmp->data.key) return 1;
		else if (key > tmp->data.key) {
			tmp = tmp->right;
		}
		else tmp = tmp->left;
	}
	return 0;
}

void inorder(link root) {
	if (root) {
		inorder(root->left);
		printf("%d ", root->data.key);
		inorder(root->right);
	}
}

int main(void) {
	int list[10] = { 21,12,32,23,43,34,1,9,7,65 };
	
	for (int i = 0; i < 10; i++)
		insert_node(list[i]);

	inorder(root);

	int b, result;
	do {
		scanf_s("%d", &b);
		BST_search(b) ? printf("있다\n") : printf("없다\n");
	} while (b);


	return 0;
}