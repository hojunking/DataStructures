#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 100
#define HEAP_FULL(n) (n == MAX_SIZE -1)
#define HEAP_EMPTY(n) (!n)

typedef struct element {
	int key;
} element;

element heap[MAX_SIZE];
int n = 0;

void pushHeap(int item) {
	if (HEAP_FULL(++n)) exit(1);
	
	int i = n;
	while ((i != 1) && (item > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i].key = item;
}

int popHeap() {
	if (HEAP_EMPTY(n)) exit(1);
	
	int parent = 1; //1번 인덱스부터 시작
	int child = 2; 
	element item = heap[1]; //pop()할 1번 인덱스(return)
	element tmp = heap[n--]; //마지막 인덱스

	//
	while (child <= n) {
		if ((child < n) && (heap[child].key < heap[child+1].key))
			child++; //오른쪽 노드가 더 크면 child++
		
		if (tmp.key >= heap[child].key) break; //tmp가 부모노드가 된다.

		heap[parent] = heap[child]; //서브트리 진행
		parent = child; //자식 -> 부모
		child *= 2; //자식 인덱스 *2
	}
	heap[parent] = tmp; //마지막 인덱스보다 작은 노드의 부모가 된다.
	return item.key;
}


int main(void) {
	FILE* fp;
	if(fopen_s(&fp,"input.txt","r"))
		exit(1);

	int tmp;
	printf("***** insertion into a max heap *****\n");
	while (fscanf_s(fp, "%d", &tmp) != EOF) {
		pushHeap(tmp);
		for (int i = 1; i <= n; i++)
			printf("%2d ", heap[i].key);
		printf("\n");
	}
	tmp = n;
	printf("***** deletion from a max heap *****\n");
	for (int i = 0; i <= tmp; i++) {
		printf("delete data = %d\n", popHeap());
		for (int j = 1; j <= n; j++)
			printf("%2d ", heap[j].key);
		printf("\n");
	}
}