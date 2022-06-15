#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct node* nodePointer;
/*
	doubly_linkedList
*/

typedef struct node {
	nodePointer next;
	nodePointer prev;
	int data;
}node;

void printForward(nodePointer header) {
	nodePointer current = header->next;
	int cnt = 0;
	printf("forward\n");
	do{
		cnt++;
		printf("(%p   %d  %p)  ", current, current->data, current->next);
		current = current->next;
		if (cnt == 4) {
			printf("\n");
			cnt = 0;
		}
	}while (current != header);
	printf("\n");
}

void printBack(nodePointer header) {
	nodePointer current = header->prev;
	int cnt = 0;
	printf("backward\n");
	do{
		cnt++;
		printf("(%p   %d  %p)  ", current, current->data, current->next);
		current = current->prev;
		if (cnt == 4) {
			printf("\n");
			cnt = 0;
		}

	}while(current != header);
	printf("\n");
}

void insertData(nodePointer header, int item) {
	nodePointer nNode = (nodePointer)malloc(sizeof(node));
	if (!nNode) return;
	nNode->data = item;

	nodePointer node = header->prev;
	nNode->prev = node;
	nNode->next = node->next;

	node->next->prev = nNode; //header-> Nnode
	node->next = nNode;
}

void deleteData(nodePointer header) {
	nodePointer current = header->next;
	printf("After deleting numbers less than and equal to 50 : \n");
	 do{
		if (current->data <= 50) { 
			nodePointer temp = current;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current = current->next;
			free(temp);
		}
		else current = current->next;
	 } while (current != header);
	 
}

int main(void) {
	nodePointer header = NULL;
	header = (nodePointer)malloc(sizeof(node));
	if (!header) return;
	header->next = header , header->prev = header;
	
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	int temp;
	while (fscanf_s(fp, "%d", &temp) !=EOF)
		insertData(header, temp);


	printf("After creating a doubly linked circular list with a head node : \n");
	printForward(header);
	printBack(header);
	deleteData(header);
	printForward(header);
	printBack(header);
}