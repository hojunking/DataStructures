#include <stdio.h>
#define MAX 10
#define SWAP(x,y,t) (t=x, x=y, y=t)

int tmp;
void insertion_sort(int list[]) {
	int n = MAX;
	for (int i = 1; i < n; i++)
		for (int j = i; 0 < j; j--)
			if (list[j] < list[j - 1])
				SWAP(list[j], list[j - 1], tmp);
}

void printList(int list[]) {
	int n = MAX;
	printf("[");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("]\n");
}

void merge(int list[], int left, int mid, int right) {
	int low = left, high = mid + 1;
	int help[MAX], k = left;

	while (low <= mid && high <= right) {
		if (list[low] > list[high])
			help[k++] = list[high++];
		else help[k++] = list[low++];
	}

	while (low <= mid) 
		help[k++] = list[low++];

	for (int i = left; i < k; i++)
		list[i] = help[i];
}

void merge_sort(int list[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

int partition(int list[], int left, int right) {
	int j = left, pivot = list[left];

	for (int i = j + 1; i <= right; i++) {
		if (list[i] < pivot) {
			j++;
			SWAP(list[j], list[i], tmp);
		}
	}
	SWAP(list[left], list[j], tmp);
	return j;
}

void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int p = partition(list, left, right);
		quick_sort(list, left, p - 1);
		quick_sort(list, p + 1, right);
	}
}
int main(void) {
	int list[MAX] = { 10,1,9,2,8,3,7,4,6,5 };
	printf("before : \n");
	printList(list);

	//insertion_sort(list);
	//merge_sort(list, 0, MAX - 1);
	quick_sort(list, 0, MAX - 1);

	printf("\nsorted : \n");
	printList(list);

}