#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#define MAX 100

//typedef struct listNode* listPointer;
/*
	연결리스트 응용 2
*/


typedef struct listNode {
	int data;
	struct listNode* link;
}listNode;


listNode* first = NULL;
listNode* end = NULL;

void bubble_sort(int list[], int n);
void printList();
int del();
int delAll();

int main(void) {
	int iList[MAX] = { 0, };

	FILE* fp;
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

	int hList[12] = { 0, };
	int c = 0;
	for (int i = 0; i < 12; i++)
		if (iList[i] % 2 == 1)
			hList[c++] = iList[i];
	printList();

	del();
	printf("After deleting nodes with odd value\n\n");

	printList();

	delAll();
	printList();

}

int init() {
	first = (listNode*)malloc(sizeof(listNode));
	if (first == NULL)
		return 0;

	end = (listNode*)malloc(sizeof(listNode));
	if (end == NULL)
		return 0;
	first->link = end;
	end->link = end;
	return 1;
}

int add(int data) {
	listNode* nNode = (listNode*)malloc(sizeof(listNode));
	if (nNode == NULL)
		return 0;
	nNode->data = data;
	nNode->link = first->link;
	first->link = nNode;
	return 1;
}

int del() {
	listNode* current = first;
	listNode* prev = NULL;
	while (current->link != end) {
		prev = current;
		current = current->link;
		if ((current->data) % 2==1) {
			prev->link = current->link;
			prev = current;
			current = first;
			free(prev);
		}
	}
	return 0;
}

int delAll() {
	listNode* current = first;
	listNode* prev = NULL;
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
	listNode* current = first;
	while (current->link != end) {
		current = current->link;
		printf("(%p, %2d, %p)", current, current->data, current->link);
	}
	printf("\n");
}

// 버블 정렬
void bubble_sort(int list[], int n) {
	int i, j, temp;

	for (i = n - 1; i > 0; i--) {
		// 0 ~ (i-1)까지 반복
		for (j = 0; j < i; j++) {
			// j번째와 j+1번째의 요소가 크기 순이 아니면 교환
			if (list[j] < list[j + 1]) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}