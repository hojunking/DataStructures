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
int front = 0;
int rear = 0;

void add(element student) {
	if (((rear + 1) % MAX_QUEUE_SIZE) == front)
		printf("queue is full, not added\n");
	else{
		rear = (rear + 1) % MAX_QUEUE_SIZE;
		queue[rear].id = student.id;
		strcpy(queue[rear].name, student.name);
	}
}

void delete() {
	if (((front+1) % MAX_QUEUE_SIZE) == rear) {
		printf("Queue empty, cannot delete a element\n");
		exit(0);
	}
	else
		front = (front+1) % MAX_QUEUE_SIZE;
}

void qprint() {
	for (int i = (front + 1) % MAX_QUEUE_SIZE; i <= (rear % MAX_QUEUE_SIZE); i++)
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

