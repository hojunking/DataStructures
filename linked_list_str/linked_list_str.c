#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#define MAX 50

/*
	file input str, make linked_list, print str
*/
typedef struct node* link;
typedef struct info {
	char name[20];
	char unv[30];
	char gender[5];
}info;

typedef struct node {
	info data;
	link next;
} node;

link head = NULL;

void connection(link nNode) {
	if (!head) {
		head = nNode;
		return;
	}
	link current = head;
	while (current->next) current = current->next;
	current->next = nNode;
	return;
}

void makeList(info* getInfo) {
	if (!getInfo) printf("No Data");
	
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) return;
	nNode->data = *(getInfo);
	nNode->next = NULL;
	connection(nNode);
	return;
}

void printList(char key) {
	link cur = head;
	printf("이름\t학교\t   성별\n\n");
	
	while (cur && cur->next) {
		if (key == 'm' && !strcmp(cur->data.gender, "여자"))
			cur = cur->next;
		if (key == 'w' && !strcmp(cur->data.gender, "남자"))
			cur = cur->next;
		printf("(%3s %10s %s)\n", cur->data.name, cur->data.unv, cur->data.gender);
		
		cur = cur->next;
	}

	printf("\n");
}

int main(void) {
	FILE* fp = NULL;
	//file open
	if (fopen_s(&fp, "input.txt", "r")) {
		printf("open failed\n");
		exit(1);
	}
	info getInfo;
	while (fscanf_s(fp, "%s %s %s", getInfo.name, 20, getInfo.unv, 30, getInfo.gender, 5) != EOF)
		makeList(&getInfo);
	
	//print all
	char key = 'a';
	printList(key);
	
	//print woman
	key = 'w';
	printList(key);
	
	//print man
	key = 'm';
	printList(key);
}