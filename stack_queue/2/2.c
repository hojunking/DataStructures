#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20
#define MAX_LEN 50
typedef struct Element {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

void dataShift() {
	printf("data shift\n");
	int sub = front + 1;
	int count = MAX_QUEUE_SIZE - 1 - front;
	rear -= sub;
	front = -1;
	//shift
	for (int i = 0; i < count; i++, sub++) {
		queue[i].id = queue[sub].id;
		strcpy(queue[i].name, queue[sub].name);
	}
}

void add(element student) {
	if (rear != MAX_QUEUE_SIZE-1) {
		rear++;
		queue[rear].id = student.id;
		strcpy(queue[rear].name, student.name);
	}
	else if(front == -1 && rear == MAX_QUEUE_SIZE -1) {
		printf("queue is full, not added\n");
	}
	else {
		dataShift();
		rear++;
		queue[rear].id = student.id;
		strcpy(queue[rear].name, student.name);
	} 
}

void delete() {
	if (front == MAX_QUEUE_SIZE -1) {
		printf("Queue empty, cannot delete a element\n");
		exit(0);
	}
	else
		front++;
}

void qprint() {
	for (int i = front+1; i <= rear; i++)
		printf("%d %s\n", queue[i].id, queue[i].name);
	
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

		if (!strcmp(op, "add")) {
			sscanf_s(context, "%d %s", &student.id, &student.name, (unsigned int)sizeof(student.name));
			add(student);
		}
		else if (!strcmp(op, "delete")) {
			delete();
		}
		else if (!strcmp(op, "qprint")) {
			qprint();
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

