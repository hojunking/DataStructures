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

link delete_node(link root,int key) {
	if (!root) return root;
	if (key < root->data.key)
		root->left = delete_node(root->left, key);
	else if (key > root->data.key)
		root->right = delete_node(root->right, key);
	else {
		if (!root->left) {
			link tmp = root->right;
			free(root);
			return tmp;
		}
		else if (!root->right) {
			link tmp = root->left;
			free(root);
			return tmp;
		}

		link current = root->right;
		while (current->left) 
			current = current->left;


		link tmp = current;
		root->data.key = tmp->data.key;
		root->right = delete_node(root->right, tmp->data.key);
	}
	return root;
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

int BST_search_recursive(link root, int key) {
	if (root) {
		if (key == root->data.key) return 1;
		else if (key > root->data.key)
			return BST_search_recursive(root->right, key);
		else return BST_search_recursive(root->left, key);
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
		result = BST_search_recursive(root, b);
		result ? printf("Yes\n") : printf("No\n");
		
		if (result) root = delete_node(root, b);
		inorder(root);
	} while (b);


	return 0;
}