#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 10
#define SWAP(x,y,t) (t=x, x=y, y=t)

void maxHeapfy(int list[], int parent, int n) {
	int temp, largest;
	int left = 2 * parent + 1;
	int right = 2 * parent + 2;
	
	if ((left < n) && (list[left] > list[parent]))
		largest = left;
	else largest = parent;

	if ((right < n) && (list[right] > list[largest]))
		largest = right;

	if (largest != parent) {
		SWAP(list[largest], list[parent], temp);
		maxHeapfy(list, largest, n);
	}
}


void buildMaxHeap(int list[], int n) {
	int parent;
	for (parent = n / 2 - 1; 0 <= parent; parent--)
		maxHeapfy(list, parent, n);
	
	printf("after initialization of max heap...\n");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n\n\n");
}


void heapSort(int list[], int n) {
	int tmp, step =1;
	buildMaxHeap(list, n);

	for (int i = n - 1; 0 <= i; i--) {
		SWAP(list[0], list[i], tmp);
		n--;
		maxHeapfy(list, 0, n);

		if (step < 10) {
			printf("step   %d: Ãâ·Â %d :  ",step++,list[i]);
			for (int j = 0; j < n; j++) {
				printf(" %2d ", list[j]);
			}
			printf("\n");
		}
	}
}

int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	int n;
	int tmp,k =0, list[MAX];
	fscanf_s(fp, "%d", &n);
	while (fscanf_s(fp, "%d", &tmp) != EOF)
		list[k++] = tmp;

	printf("<<<<<<<< Input List >>>>>>>>>\n");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n\n");
	printf("<<<<< excuting heap sort >>>>>\n");
	heapSort(list, n);


	printf("<<<<<<<< Sorted List >>>>>>>>>\n");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	

	return 0;
}