#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define IS_EMPTY(top) (top == -1)
#define IS_FULL(top) (top == MAX-1)

typedef struct node* link;
typedef struct node {
	link left, right;
	char item;
} node;

typedef enum {
	plus, minus, times, divide, eos, operand, mod
} precedence;

link root = NULL;
link stack[MAX] = { NULL };
char input[10];
int top = -1;

void push(link nNode) {
	if (IS_FULL(top)) exit(1);

	stack[++top] = nNode;
}

link pop() {
	if (IS_EMPTY(top)) return NULL;

	return stack[top--];
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
		if (top == -1) break;
		
		root = pop();
		if (!root) break;
		tmp = root;

		if (root->right) {
			root = root->right; //자식
			printf("%c", root->item); //형제
			printf("%c", tmp->item); //부모
			root = root->right; // right or NULL
		}
		else {
			printf("%c", tmp->item); //부모만
			root = root->right; //right or NULL;
		}
	}
}


precedence getToken(int* n, char* symbol) {
	*symbol = input[(*n)++];
	switch (*symbol) {
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}


link eval(void) {
	int n = 0;
	char symbol;

	precedence token = getToken(&n, &symbol);
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
		token = getToken(&n, &symbol);
	}
	return pop();
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

	return 0;
}

