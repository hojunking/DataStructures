#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 10
#define SWAP(x,y,t) (t=x, x=y, y=t)

void radixSort(int list[], int d, int n) {
	int queue[MAX], maxValue = 0;
	int exp = 1, k = 0;
	for (int i = 0; i < n; i++)
		if (list[i] > maxValue) maxValue = list[i];

	int store[MAX][MAX] = { 0, };

	while (maxValue / exp > 0) { 
		int bucket[MAX] = { 0 };
		++k;
		printf("\nstep %d 자리  ---\n\n",k);
		for (int i = 0; i < n; i++)
			printf("     %d ", i);
		printf("\n\n");

		for (int i = 0; i < n; i++) {
			int idx = list[i] / exp % 10;
			store[bucket[idx]][idx] = list[i];
			bucket[idx]++;
		}

		////////////////////////////////////
		printf("Queue의 내용  ---\n");
		for (int i = d - 1; 0 <= i; i--) {
			for (int j = 0; j < n; j++) {
				if (store[i][j])
					printf("   %3d ", store[i][j]);
				else printf("       ");
			}
			printf("\n\n");
		}
		printf("---------------------------------------------------------------------\n");

		
		for (int i = 1; i < 10; i++) 
			bucket[i] += bucket[i - 1];
		printf("\n");

		for (int i = n - 1; i >= 0; i--) { 
			queue[--bucket[list[i] / exp % 10]] = list[i];
		}
		///////////결과////////////////
		for (int i = 0; i < n; i++) {
			list[i] = queue[i];
			printf("   %3d ", list[i]);
		}
		printf("\n");
		exp *= 10;
	}
}


int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	int d, n;
	int tmp, k = 0, list[MAX];
	fscanf_s(fp, "%d", &d);
	fscanf_s(fp, "%d", &n);

	while (fscanf_s(fp, "%d", &tmp) != EOF)
		list[k++] = tmp;
	printf("input data ---\n");
	for (int i = 0; i < n; i++)
		printf("   %3d ", list[i]);
	printf("\n\n");

	radixSort(list,d, n);

	printf("\nresult ---\n");
	for (int i = 0; i < n; i++)
		printf("   %3d ", list[i]);
	printf("\n\n"); 

	return 0;
}