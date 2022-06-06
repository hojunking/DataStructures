#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 10
#define SWAP(x,y,t) (t=x, x=y, y=t)

int tmp, n = MAX;

void insertion_sort(int list[]) {
	for (int i = 1; i < n; i++)
		for (int j = i; 0 < j; j--)
			if(list[j] < list[j-1])
				SWAP(list[j], list[j - 1], tmp);
}

int partition(int list[], int left, int right) {
	int j = left, pivot = list[left];
	for (int i = j + 1; i < n; i++)
		if (list[i] < pivot) {
			j++;
			SWAP(list[i], list[j], tmp);
		}
	SWAP(list[left], list[j], tmp);
}

void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int p = partition(list, left, right);
		quick_sort(list, left, p - 1);
		quick_sort(list, p + 1, right);
	}
}

void printList(int list[]) {
	printf("[");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("]\n");
}

int main(void) {
	int list[MAX] = { 1,9,2,8,3,7,4,6,5,10 };

	printf("before : \n");
	printList(list);

	//insertion_sort(list);
	//merge_sort(list, 0, MAX - 1);
	quick_sort(list, 0, n - 1);

	printf("\nsorted : \n");
	printList(list);

	return 0;
}