#include <stdio.h>
#include <stdlib.h>

typedef struct node* link;

typedef struct node{
	link left;
	link right;
	char data;
} node;


void init(link root, char data) {
	node* nNode = (node*)malloc(sizeof(node));
	if (!nNode) return;

	nNode->data = data;
	root = nNode;
	nNode->left = NULL;
	nNode->right = NULL;
	printf("init good = %c\n", root->data);
}

void insertNode(link root,char data) {
	node* nNode = (node*)malloc(sizeof(node));
	if (!nNode) return;
	nNode->data = data;
	nNode->left = NULL;
	nNode->right = NULL;

	if (root->left == NULL) {
		root->left = nNode;
	}
	else if (root->right == NULL) {
		root->right = nNode;
	}
	else {
		printf("»ðÀÔ½ÇÆÐ\n");
	return;
	}
}

void preorder(node* root) {
	if (root) {
		printf("(%p : %p  %c  %p)\n", root->left, root->right, root->data, root);
		preorder(root->left);
		preorder(root->right);
	}
}
void inorder(node* root) {
	if (root) {
		inorder(root->left);
		printf("(%p : %p  %c  %p)\n", root->left, root->right, root->data, root);
		inorder(root->right);
	}
}
void postorder(node* root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("(%p : %p  %c  %p)\n", root->left, root->right, root->data, root);
	}
}

int main(void) {
	printf("creating a complete binary tree\n");
	link root = (link)malloc(sizeof(node));
	root->left = NULL;
	root->right = NULL;
	root->data = 'A';

	insertNode(root, 'B');
	insertNode(root, 'C');
	insertNode(root->left, 'D');
	insertNode(root->left, 'E');
	printf("three binary tree traversals\n");
	printf("inorder traversal\t:\n");
	inorder(root);
	printf("\npreorder traversal\t:\n");
	preorder(root);
	printf("\npostorder traversal\t:\n");
	postorder(root);

}