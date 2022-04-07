#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#define MAX 100
/*
	원형 연결리스트 구현
*/

typedef struct Cir {
	int num;
	struct Cir* link;\
}cir;

typedef struct List {
	cir* head;
	cir* tail;
}list;

void init(list* lp) {
	lp->head = (cir*)malloc(sizeof(cir));
	lp->tail= (cir*)malloc(sizeof(cir));
	if (lp->head == NULL)
		return;
	lp->head->link = NULL;
	lp->tail->link = NULL;
}


void add(list* lp,int item) {
	cir* newNode = (cir*)malloc(sizeof(cir));
	if (newNode == NULL)
		return;
	
	newNode->num = item;
	
	if (lp->head->link == NULL) {
		lp->head->link = newNode;
		lp->tail->link = newNode;
		newNode->link =newNode;
	}
	lp->tail->link->link = newNode;
	newNode->link = lp->head->link;
	lp->tail->link = newNode;
	return;
}

void pop(list* lp) {
	cir* current = lp->head->link->link;

	cir* prev = current;
	 do{
		if ((current->num) % 2 == 1) {
			printf("%d ", current->num);
			prev->link = current->link;
			cir* temp = current;
			current = current->link;
			free(temp);
		}
		else {
			prev = current;
			current = current->link;
		}
	}while (current != lp->head->link);

	return;
}

void printList(list* lp) {
	cir* current = lp->head->link;
	printf("The Circularly Linked List contains:\n");
	int cnt = 0;
	 do{
		printf("(%p,   %d,  %p )", current, current->num, current->link);
		current = current->link;
		cnt++;
		if (cnt == 3) {
			printf("\n");
			cnt = 0;
		}
	}while (current != lp->head->link);
}

int main(void) {
	list lp;
	init(&lp);

	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	int temp[12]={0};
	for (int i = 0; i < 12; i++)
		fscanf_s(fp, "%d", &temp[i]);

	for (int i = 0; i < 12; i++)
		add(&lp, temp[i]);
	printList(&lp);
	pop(&lp);
	printf("\nAfter deleting nodes with odd value\n");
	printList(&lp);

	free(lp.head);
}




