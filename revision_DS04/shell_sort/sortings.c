#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 11
#define SWAP(x,y,t) (t=x,x=y,y=t)


int n = MAX;

void insertion_sort(int list[], int first, int gap) {
	int j;
	for (int i = first+gap; i < n; i+=gap) {
		int key = list[i];
		for (j = i - gap; first <= j && list[j] > key; j -= gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}

void shell_sort(int list[]) {

	for (int gap = n / 2; 0 < gap; gap /= 2) {
		if (gap % 2 == 0) gap++;

		for (int i = 0; i < gap; i++)
			insertion_sort(list, i, gap);
	}
}

int partition(int list[], int left, int right) {
	int j = left, tmp,pivot = list[left];
	for(int i = j +1; i <=right; i++)
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

int main(void) {
	
	int list[MAX] = { 10, 8, 6, 20, 4, 3, 22, 1,
		0, 15, 16 };

	printf("list[] data\n");
	for (int i = 0; i < n; i++)
		printf("%5d", list[i]);
	printf("\n");

	//shell_sort(list);
	quick_sort(list, 0, n - 1);

	for (int i = 0; i < n; i++)
		printf("%5d", list[i]);
}