#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
/*
	연결리스트 - 다항식 계산프로그램
*/


typedef struct polyNode* polyPointer;

typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;


void inputF(polyPointer T, int coef, int expon) {
	polyPointer nNode = (polyPointer)malloc(sizeof(polyNode));
	if (nNode == NULL)
		return;
	polyPointer temp = T;
	nNode->coef = coef;
	nNode->expon = expon;

	while (temp->link != NULL)
		temp = temp->link;

	nNode->link = NULL;
	temp->link = nNode;
}


void inputL(polyPointer T, int coef, int expon) {
	polyPointer nNode = (polyPointer)malloc(sizeof(polyNode));
	if (nNode == NULL)
		return;
	nNode->coef = coef;
	nNode->expon = expon;
	/*while (temp->link != NULL) 
		temp = temp->link;*/
	
	if (T->link == NULL) {
		nNode->link = NULL;
		T->link = nNode;
	}
	else {
		nNode->link = T->link;
		T->link = nNode;
	}
}

void attach(int coef, int exp, polyPointer * ptr) {
	polyPointer temp;
	temp = (polyPointer)malloc(sizeof(polyNode));
	if (temp == NULL)
		return;
	temp->coef = coef;
	temp->expon = exp;
	(*ptr)->link = temp;
	*ptr = temp;
}

void deleteAll(polyPointer T) {
	polyPointer current = T->link;
	polyPointer temp;

	while (current->link != NULL) {
		temp = current;
		current = current->link;
		free(temp);
	}
}


void printNode(polyPointer T, char t) {
	if (t == 'c')
		printf("a+b=c :\n");
	else
		printf("%c : \n", t);
	polyPointer current = T;

	while (current->link != NULL) {
		current = current->link;
		printf("(%p :   +%dx^%d  : %p)\n", current,
		current->coef, current->expon, current->link);
	}
	printf("\n");
}
int compare(int a, int b) {
	if (a > b) return 1;
	else if (a == b) return 0;
	else return -1;
}

polyPointer padd(polyPointer a, polyPointer b) {
	polyPointer c, rear, temp;
	int sum;
	rear = (polyPointer)malloc(sizeof(polyNode));
	c = rear;

	while (a && b) {

		switch (compare(a->expon, b->expon)) {
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0: 
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
			a = a->link; b = b->link; break;
		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
		}
	}
	for (; a; a = a->link) attach(a->coef, a->expon, &rear);
	for (; b; b= b->link) attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c; c = c->link; free(temp);
	return c;
}


int main(void) {
	FILE* fp1;
	FILE* fp2;
	polyPointer A = (polyPointer)malloc(sizeof(polyNode));
	A->link = NULL;
	polyPointer B = (polyPointer)malloc(sizeof(polyNode));
	B->link = NULL;
	polyPointer C = (polyPointer)malloc(sizeof(polyNode));
	C->link = NULL;

	if (fopen_s(&fp1, "a.txt", "r"))
		exit(1);
	

	int coef, expon;
	char input;
	fscanf_s(fp1, "%c", &input);
	if (input = 'a') {
		while (fscanf_s(fp1,"%d %d", &coef, &expon)!= EOF) {
			inputL(A, coef, expon);
		}
	}
	else {
		while (fscanf_s(fp1,"%d %d", &coef, &expon) != EOF) {
			inputL(A, coef, expon);
		}

	}
	if (fopen_s(&fp2, "b.txt", "r"))
		exit(1);


	fscanf_s(fp2, "%c", &input);
	if (input = 'a') {
		while (fscanf_s(fp2,"%d %d", &coef, &expon) != EOF) {
			inputF(B, coef, expon);
		}
	}
	else {
		while (fscanf_s(fp2,"%d %d", &coef, &expon) != EOF) {
			inputF(B, coef, expon);
		}
	}
	printNode(A, 'a');
	printNode(B, 'b');
	C->link = padd(A->link, B->link);
	printNode(C, 'c');
	deleteAll(A);
	deleteAll(B);
	deleteAll(C);
}