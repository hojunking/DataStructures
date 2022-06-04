#include <stdio.h>
#define MAX 10
#define SWAP(x,y,t) (t=x, x=y, y=t)


void insertion_sort(int list[]) {
	int tmp, n = MAX;
	for (int i = 1; i < n; i++)
		for (int j = i; 0 < j; j--)
			if (list[j] < list[j - 1])
				SWAP(list[j], list[j - 1], tmp);
}

void selection_sort(int list[]) {
	int tmp,n = MAX;
	for (int i = 0; i < n-1; i++) {
		int least = i;
		for (int j = i; j < n; j++) 
			if (list[least] > list[j])
				least = j;
		
		if (least != i)
			SWAP(list[least], list[i], tmp);
	}
}

int partition(int list[], int left, int right) {
	int pivot = list[left];
	int tmp, j = left;
	for (int i = j + 1; i <= right ; i++) 
		if (pivot > list[i]) {
			j++;
			SWAP(list[j], list[i], tmp);
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

void merge(int list[], int left, int mid, int right) {
	int low = left, high = mid + 1;
	int tmp, k = left;
	int help[MAX];

	while (low <= mid && high <= right) {
		if (list[low] > list[high])
			help[k++] = list[high++];
		else help[k++] = list[low++];
	}

	while (low <= mid) {
		help[k++] = list[low++];
	}

	for (int j = left; j < k; j++)
		list[j] = help[j];
}

void merge_sort(int list[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

void printList(int list[]) {
	printf("[ ");
	for (int i = 0; i < MAX; i++)
		printf("%2d ", list[i]);
	printf(" ]\n");
}

void makeSorted(int a[])
{
	int i = 0, j = 0, temp = 0;
	while (a[i] != -1)
	{
		for (j = 0; i < MAX - j; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				break;
			}
		}
		i++;
	}

}


int main(void) {
	int list[MAX] = { 10,1,9,2,8,3,7,4,6,-1 };
	printf("before : \n");
	printList(list);

	makeSorted(list);
	//merge_sort(list, 0, MAX - 1);

	printf("\nsorted : \n");
	printList(list);

}