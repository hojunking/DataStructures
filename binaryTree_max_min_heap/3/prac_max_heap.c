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
	
	int parent = 1; //1�� �ε������� ����
	int child = 2; 
	element item = heap[1]; //pop()�� 1�� �ε���(return)
	element tmp = heap[n--]; //������ �ε���

	//
	while (child <= n) {
		if ((child < n) && (heap[child].key < heap[child+1].key))
			child++; //������ ��尡 �� ũ�� child++
		
		if (tmp.key >= heap[child].key) break; //tmp�� �θ��尡 �ȴ�.

		heap[parent] = heap[child]; //����Ʈ�� ����
		parent = child; //�ڽ� -> �θ�
		child *= 2; //�ڽ� �ε��� *2
	}
	heap[parent] = tmp; //������ �ε������� ���� ����� �θ� �ȴ�.
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