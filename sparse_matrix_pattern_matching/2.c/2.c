#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 25
/*
matrix transpose(row & col swapping)
*/
typedef struct {
	int row;
	int col;
	int value;
}info;

void printMatix(info m[], int list[][10], char a) {
	printf("%c\n", a);
	for (int i = 0; i < m[0].row; i++) {
		for (int j = 0; j < m[0].col; j++)
			printf(" %3d ", list[i][j]);
		printf("\n");
	}
}
void transpose(info A[], info B[]) {
	B[0].col = A[0].row;
	B[0].row = A[0].col;
	B[0].value = A[0].value;
	int k = 1;
	for (int i = 0; i < A[0].row; i++) {
		for(int j =1; j < A[0].value+1; j++)
			if (A[j].col == i) {
				B[k].col = A[j].row;
				B[k].row = A[j].col;
				B[k].value = A[j].value;
				k++;
			}
	}
}

int main(void) {
	info A[MAX], B[MAX];
	FILE* fp;
	FILE* fp2;
	if (fopen_s(&fp, "a.txt", "r"))
		exit(1);
	if (fopen_s(&fp2, "b.txt", "w"))
		exit(1);

	int k = 0;
	while (fscanf_s(fp, "%d %d %d", &A[k].row, &A[k].col, &A[k].value) != EOF)
		k++;
	
	int a[10][10], b[10][10];
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));

	for (int i = 1; i < A[0].value + 1; i++)
		a[A[i].row][A[i].col] = A[i].value;

	printMatix(A, a, 'A');
	transpose(A, B);
	
	for (int i = 0; i < B[0].value + 1; i++)
		b[B[i].row][B[i].col] = B[i].value;

	k = -1;
	while (k++ != B[0].value)
		fprintf(fp2,"%d %d %d\n", B[k].row, B[k].col, B[k].value);
	
	printMatix(B, b, 'B');
	
}