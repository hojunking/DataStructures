#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 100
#define HEAP_FULL(n) (n == MAX_SIZE -1)
#define HEAP_EMPTY(n) (!n)

typedef struct node {
	int key;
}node;

node heap[MAX_SIZE];
int n;

void heap_push(int item) {
	if (HEAP_FULL(++n)) exit(1);
	int i = n; //last node of heap

	while ((i != 1) && (item < heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i].key = item;
}

int heap_pop() {
	if (HEAP_EMPTY(n)) exit(1);
	int parent = 1, child = 2;
	node tmp = heap[n--];
	node item = heap[1];
	
	while (child <= n) {
		if ((child < n) && (heap[child].key > heap[child + 1].key))
			child++;
		if (tmp.key <= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = tmp;
	return item.key;
}

int main() {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	
	n = 0; //init_heap
	int tmp;
	
	printf("***** insertion into a min heap *****\n");
	while (fscanf_s(fp, "%d", &tmp) != EOF) {
		heap_push(tmp);
		for (int i = 1; i <= n; i++) 
			printf("%2d ", heap[i].key);
		printf("\n");
	}
	tmp = n;
	printf("***** deletion from a min heap *****\n");
	for (int i = 0; i <= tmp; i++) {
		printf("delete data = %d\n", heap_pop());
		for (int j = 1; j <= n; j++)
			printf("%2d ", heap[j].key);
		printf("\n");
	}
	return 0;
}