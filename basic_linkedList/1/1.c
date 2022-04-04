#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct listNode* listPointer;

/*
	���Ḯ��Ʈ ���� - typedef ����
*/


struct listNode {
	int data;
	listPointer link;
}listNode;

listPointer first = NULL;
listPointer end = NULL;

void bubble_sort(int list[], int n);
void printList();
int del();
int delAll();


int main(void) {
	int iList[MAX] = { 0, };

	FILE* fp;
	int ch;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	int a = 0;

	for (int i = 0; i < 12; i++)
		fscanf_s(fp, "%d", &iList[i]);

	bubble_sort(iList, 12);

	//init
	init();

	//input
	for (int i = 0; i < 12; i++)
		add(iList[i]);
	
	//��ü ���
	printList();

	//Ȧ�� ����
	del();
	printf("\n");
	printf("After deleting nodes with odd value\n\n");
	printList();
	
	//��ü ����
	delAll();
	printList();
}

int init() {
	first = (listPointer*)malloc(sizeof(listNode));
	if (first == NULL)
		return 0;

	end = (listPointer*)malloc(sizeof(listNode));
	if (end == NULL)
		return 0;
	first->link = end;
	end->link = end;
	return 1;
}

int add(int data) {
	listPointer nNode = (listPointer*)malloc(sizeof(listNode));
	if (nNode == NULL)
		return 0;
	nNode->data = data;
	nNode->link = first->link;
	first->link = nNode;
	return 1;
}

int del() {
	listPointer current = first, prev = NULL;
	while (current->link != end) {
		prev = current;
		current = current->link;
		//printf("spot1\n");
		if ((current->data) % 2 == 1) {
			prev->link = current->link;
			prev = current;
			current = first;
			free(prev);
		}
	}
	return 0;
}

int delAll() {
	listPointer current = first, prev = NULL;
	while (current->link != end) {
		prev = current;
		current = current->link;
		prev->link = current->link;
		prev = current;
		current = first;
		free(prev);
	}
	return 0;
}

void printList() {
	printf("The odderd list contains:\n");
	listPointer current = first;
	while (current->link != end) {
		current = current->link;
		printf("(%p, %2d, %p)", current, current->data, current->link);
	}
	printf("\n");
}

// ���� ����
void bubble_sort(int list[], int n) {
	int i, j, temp;

	for (i = n - 1; i > 0; i--) {
		// 0 ~ (i-1)���� �ݺ�
		for (j = 0; j < i; j++) {
			// j��°�� j+1��°�� ��Ұ� ũ�� ���� �ƴϸ� ��ȯ
			if (list[j] < list[j + 1]) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}