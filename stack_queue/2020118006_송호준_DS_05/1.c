#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 20
#define MAX_LEN 50
typedef struct Element{
	int id;
	char name[MAX_NAME_SIZE];
} element;

element stack[MAX_STACK_SIZE];
int top = -1;



int isFull() {
	if (top == MAX_STACK_SIZE - 1) {
		printf("stack is full, cannot add element\n");
		printf("cuurent stack elements\n");
		for (int i = top; i > -1; i--) {
			printf("%d %s\n", stack[i].id, stack[i].name);
		}
		return 1;
	}
	return -1;
}

int isEmpty() {
	if (top == -1) {
		printf("wrong command! try again!\n");
		return 1;
	}
	return -1;
}

void pop() {
	if (isEmpty()==-1) {
		//printf("%d %s\n", stack[top].id, stack[top].name);
		--top;
		return;
	}
	return;
}
void push(element student) {
	if (isFull()==-1) {
		++top;
		//printf("top = %d\n", top);
		stack[top].id = student.id;
		strcpy(stack[top].name , student.name);
		return;
	}
	else return;
}
void sprint() {
	for (int i = top; -1 <i  + 1; i--) {
		printf("%d %s\n", stack[i].id, stack[i].name);
	}
}


int main(void) {
	char* delimiter = " \n";
	char* context;
	char* op = NULL;
	element student;
	FILE* fp;
	char line[MAX_LEN];

	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	while (1) {
		if (!(fgets(line, MAX_LEN, fp)))
			break;
		op = strtok_s(line, delimiter, &context);

		if (!strcmp(op, "push")) {
			sscanf_s(context,"%d %s", &student.id, &student.name,(unsigned int)sizeof(student.name));
			push(student);
		}
		else if (!strcmp(op,"pop")) {
			pop();
		}
		else if (!strcmp(op, "sprint")) {
			sprint();
			printf("\n");
			
		}
		else if (!strcmp(op, "quit")) {
			printf("Á¾·á");
			break;
		}
		else
			printf("wrong command! try again!\n");
	}
	fclose(fp);
}