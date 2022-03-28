#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 100
#define MAX_LEN 100

#define  MALLOC(p,s)\
   if(!((p) = malloc(s))){\
   fprintf(stderr,"Insufficient memory");\
   exit(EXIT_FAILURE);\
}

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element* queue = NULL;
int capacity = 2;
int front;
int rear;



void qprint() {
	int p = (front + 1) % capacity;

	do {
		printf("%d %s\n", queue[p].id, queue[p].name);
		p = (p + 1) % capacity;
	} while (p != rear);
	printf("%d %s\n", queue[p].id, queue[p].name);
}


void copy(element* a, element* b, element* c) {
	while (a != b)
		*c++ = *a++;
}




void queueFull() {
	int start;
	element* newQueue;
	MALLOC(newQueue, 2 * capacity * sizeof(*queue));

	start = (front + 1) % capacity;
	if (start < 2)
		copy(queue + start, queue + start + capacity - 1, newQueue);
	else{
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}
	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;
	free(queue);
	queue = newQueue;

	printf("queue capacity is doubled,\n");
	printf("current queue capacity is %d.\n", capacity);

}

void add(element item) {

	rear = (rear + 1) % capacity;
	if (rear == front) {
		queueFull();
		queue[++rear] = item;
		qprint();
	}
	else queue[rear] = item;
}

void delete() {
	if ((front % capacity) == rear) {
		printf("Queue empty, cannot delete a element\n");
		exit(0);
	}
	else
		front = (front + 1) % capacity;
}
void initQueue() {
	front = 0;
	rear = 0;
	MALLOC(queue, capacity * sizeof(*queue));
}

int main(void) {
	initQueue();
	char* delimiter = " \n";
	char* context;
	char* op = NULL;
	element student;
	FILE* fp;
	char line[MAX_LEN];

	printf("<<  circular queue operations using dynamic allocated array, where the initial capacity is 2  >>\n");
	printf("add 1 Jung\n");
	printf("delete\n\n");
	printf("**************************************************\n");


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
			printf("end of program!!\n");
			break;
		}
		else
			printf("wrong command! try again!\n");
	}
	fclose(fp);
}

