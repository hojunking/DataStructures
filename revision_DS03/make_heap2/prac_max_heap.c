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

void heap_insertion(int item) {
	if (HEAP_FULL(n)) exit(1);

	int i = ++n;
	while ((i != 1) && (item > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
		//heap 올라가기
	} // Min_heap은 item < heap[i / 2].key
	heap[i].key = item;
}

int heap_deletion() {
	if (HEAP_EMPTY(n)) exit(1);

	int parent = 1, child = 2;
	element temp = heap[n--], pop_data = heap[parent];
	// temp는 heap의 마지막 인덱스, pop_data는 root

	while (child <= n) {
		if ((child < n) && (heap[child].key < heap[child + 1].key))
			child++;
		if (temp.key > heap[child].key) break;
		// root로 간 temp가 자식노드와 비교, 크다면 정지한다.
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
		//heap 내려가기
	}
	heap[parent] = temp;
	return pop_data.key; //root return
}

int main(void) {
	FILE* fp;

	if (fopen_s(&fp, "input.txt", "r")) exit(1);
	int t;
	printf("***** insertion into a max heap *****\n");
	while (fscanf_s(fp, "%d ", &t) != EOF) {
		heap_insertion(t, n);
		for (int i = 1; i <= n; i++) {
			printf("%2d ", heap[i].key);
		}
		printf("\n");
	}
	printf("***** deletion from a max heap *****\n");
	t = n;
	int del;
	for (int i = 1; i <= t; i++) {
		del = heap_deletion();
		printf("delete data = %d\n", del);
		for (int i = 1; i <= n; i++) {
			printf("%2d ", heap[i].key);
		}
		printf("\n");
	}
}