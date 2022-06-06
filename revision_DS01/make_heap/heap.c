#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 20
#define MAX_LIST 10
#define HEAP_FULL(n) (n == MAX-1)
#define HEAP_EMPTY(n) (!n)

typedef struct element {
	int key;
} element;

element heap[MAX] = { NULL };
int n;

void init() {
	n = 0;
}

void push(int item) {
	if (HEAP_FULL(n)) exit(1);
	int i = ++n;

	while (i != 1 && item < heap[i / 2].key) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i].key = item;
}

int pop() {
	if (HEAP_EMPTY(n)) exit(1);
	
	int parent = 1, child = 2;
	element tmp = heap[n--];
	element data = heap[parent];

	while (child <= n) {
		if (child <n && heap[child].key > heap[child + 1].key)
			child++;
		if (tmp.key < heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = tmp;
	return data.key;
}

void printList(int list[]) {
	int ln = MAX_LIST;
	printf("[");
	for (int i = 0; i < ln; i++)
		printf("%d ", list[i]);
	printf("]\n");
}

int main(void) {
	int list[MAX_LIST] = { 9,1,8,2,7,3,4,5,6,10 };
	int ln = MAX_LIST;
	printf("before\n");
	printList(list);
	init(); 

	for (int i = 0; i < ln; i++)
		push(list[i]);
	for (int i = 0; i < ln; i++)
		list[i] = pop();
	
	
	printf("after\n");
	printList(list);


}