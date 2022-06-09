#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#define MAX 10

typedef struct node* link;
typedef struct node {
	link left, right;
	int key;
} node;

link root = NULL;

void insert_node(int item) {
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) return;

	nNode->left = nNode->right = NULL;
	nNode->key = item;

	link tmp = root;
	while (tmp) {
		if (tmp->key == item) return;
		
		else if (tmp->key > item) 
			if (tmp->left) tmp = tmp->left;
			else {
				tmp->left = nNode;
				return;
			}
		else {
			if (tmp->right) tmp = tmp->right;
			else {
				tmp->right = nNode;
				return;
			}
		}
	}
	if (!root) root = nNode;
}

int bin_search_re(link root, int key) {
	if (root) {
		if (key == root->key) return 1;
		else if (key > root->key)
			return bin_search_re(root->right, key);
		else 
			return bin_search_re(root->left, key);
	}
	return 0;
}

int bin_search(link root, int key) {
	while (root) {
		if (key == root->key) return 1;
		else if (key > root->key) root = root->right;
		else root = root->left;
	}
	return 0;
}

void inorder(link root) {
	if (root) {
		inorder(root->left);
		printf("%d ", root->key);
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
		result = bin_search_re(root, b);
		result ? printf("Yes\n") : printf("No\n");

	} while (b);
	return 0;
}