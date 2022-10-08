#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 200
#define HEAP_FULL(n) (n==MAX_SIZE-1)
#define HEAP_EMPTY(n) (!n)

typedef struct element {
	int key;
} element;

element heap[MAX_SIZE];
int n = 0;

void push(int data) {
	int i;
	if (HEAP_FULL(n)) exit(1);

	i = ++n;
	while ((i != 1) && (data < heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i].key = data;
}


int pop() {
	if (HEAP_EMPTY(n)) exit(1);

	int parent, child;
	element item, temp;
	item = heap[1];
	temp = heap[n--];
	parent = 1;
	child = 2;
	while (child <= n) {
		if ((child < n) && (heap[child].key > heap[child + 1].key))
			child++;
		if (temp.key <= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item.key;
}


int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	int t;
	printf("***** insertion into a max heap *****\n");
	while (fscanf_s(fp, "%d ", &t) != EOF) {
		push(t, n);
		for (int i = 1; i <= n; i++) {
			printf("%2d ", heap[i].key);
		}
		printf("\n");
	}
	printf("***** deletion from a max heap *****\n");
	t = n;
	int del;
	for (int i = 1; i <= t; i++) {
		del = pop();
		printf("delete data = %d\n", del);
		for (int i = 1; i <= n; i++) {
			printf("%2d ", heap[i].key);
		}
		printf("\n");
	}
}