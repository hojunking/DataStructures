#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 20
#define HEAP_FULL(n) (n == MAX-1)
#define HEAP_EMPTY(n) (!n)

typedef struct element {
	int key;
} element;

element heap[MAX] = { NULL };
int n;

void push(int item) {
	if (HEAP_FULL(n)) exit(1);
	int i = ++n;
	
	while ((i != 1) && (item > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i].key = item;
}

int pop() {
	if (HEAP_EMPTY(n)) exit(1);
	int child = 2, parent = 1;
	element data = heap[parent];
	element tmp = heap[n--];

	while (child <= n) {
		if ((child < n) && (heap[child].key < heap[child+1].key))
			child++;
		if (tmp.key > heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent].key = tmp.key;
	return data.key;
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