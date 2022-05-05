#include <stdio.h>	
#include <stdlib.h>
#define MAX_SIZE 500

typedef struct node* link;
typedef struct element {
	int item;
	int key;
} element;

typedef struct node{
	link left, right;
	element data;
} node;


int n;
link iterBinSearch(link root,int k) {
	while (root) {
		if (k == root->data.key) {
			printf("%d => ", root->data.item);
			printf("\nthe element is in BST\n");
			return root;
		}
		if (k < root->data.key) {
			printf("%d => ", root->data.item);
			root = root->left;
		}
		else {
			printf("%d => ", root->data.item);
			root = root->right;
		}
	}
}

void inorder(link root) {
	if (root) {
		inorder(root->left);
		printf("%4d ", root->data.item);
		inorder(root->right);
	}
}

link insert(link root, int k, int item) {
	printf("%3d ", item);
	link ptr;
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) return;
	nNode->data.key = k;
	nNode->data.item = item;
	nNode->left = nNode->right = NULL;
	if (!root) {
		root = nNode;
		return root;
	}
	ptr = root;

	while (ptr) {
		if (k == ptr->data.key) return root;//중복값!
		else if (k < ptr->data.key) {
			if (ptr->left == NULL) { //왼쪽노드가 비어 있다면 추가
				ptr->left = nNode;
				return root;
			}
			else ptr = ptr->left;
		}
		else {
			if (ptr->right == NULL) { //right
				ptr->right = nNode;
				return root;
			}
			else ptr = ptr->right;
		}
	}
}

int main(void) {
	link root = NULL;

	long seed;
	printf("random number generation (1 ~ %d)\n", MAX_SIZE);
	printf("%s", "the number of nodes in BST (less than and equal to 50) : ");
	scanf_s("%d", &n);
	printf("%s", "seed : ");
	scanf_s("%u", &seed);
	printf("\ncreating a BST from random numbers\n");
	srand(seed);

	int temp;
	printf("generating number : ");
	for (int i = 0; i < n; i++) {
		temp = rand() % 500;
		root = insert(root, temp, temp);
	}
	int search;
	printf("\nthe key to search : ");
	scanf_s("%d", &search);
	printf("the search process : ");
	iterBinSearch(root,search);
	printf("\n\ninorder traversal of the BST show the sorted sequence\n");
	inorder(root);

}