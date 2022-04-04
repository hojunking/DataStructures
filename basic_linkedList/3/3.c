#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#define MAX 50

/*
	연결리스트 응용 - str 저장
*/


typedef struct listNode* listPointer;

typedef struct Info {
	char name[MAX];
	char work[MAX];
	char sex[MAX];
}Info;

struct listNode {
	Info info;
	listPointer link;

}listNode;

listPointer first = NULL;
listPointer end = NULL;
listPointer xy = NULL;
listPointer xx = NULL;

int init();
int init2();
int add(listPointer t);
void printList();
int del();
int infoCpy();


int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	//init
	init();
	
	struct listNode t;

	for (int i = 0; i < 6; i++){
		fscanf_s(fp, "%s %s %s", t.info.name,MAX, t.info.work,MAX, t.info.sex,MAX);
		add(&t);
	}
	
	printf("전체 리스트\n");
	printList();

	init2();
	infoCpy();

	listPointer current = xx;
	printf("남자 리스트\n");

	while (current->link != NULL) {
		current = current->link;
		printf("( %p, %5s, %5s, %3s %p )\n"
			, current, current->info.name, current->info.work, current->info.sex, current->link);
	}
	printf("\n");
	printf("여자 리스트\n");
	current = xy;

	while (current->link != NULL) {
		current = current->link;
		printf("( %p, %5s, %5s, %3s %p )\n"
			, current, current->info.name, current->info.work, current->info.sex, current->link);
	}
	printf("\n");

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

int init2() {
	xx = (listPointer*)malloc(sizeof(listNode));
	if (first == NULL)
		return 0;

	xy = (listPointer*)malloc(sizeof(listNode));
	if (end == NULL)
		return 0;
	xx->link = NULL;
	xy->link = NULL;
	return 1;
}

int add(listPointer t) {
	listPointer nNode = (listPointer*)malloc(sizeof(listNode));
	if (nNode == NULL)
		return 0;
	nNode->info = t->info;
	nNode->link = first->link;
	first->link = nNode;
	return 1;
}




int infoCpy() {
	listPointer current = first;

	while (current->link != end) {
			current = current->link;
		if (!strcmp(current->info.sex, "남자")) {
			listPointer nNode = (listPointer*)malloc(sizeof(listNode));
			if (nNode == NULL)
				return 0;
			nNode->info = current->info;
			nNode->link = xx->link;
			xx->link = nNode;
		}
		else if (!strcmp(current->info.sex, "여자")) {
			listPointer nNode = (listPointer*)malloc(sizeof(listNode));
			if (nNode == NULL)
				return 0;
			nNode->info = current->info;
			nNode->link = xy->link;
			xy->link = nNode;
		}
	}
	return 0;
}

void printList() {
	listPointer current = first;
	
	while (current->link != end) {
		current = current->link;
		printf("( %p, %5s, %5s, %3s %p )\n"
			, current, current->info.name, current->info.work, current->info.sex, current->link);
	}
	printf("\n");
}




