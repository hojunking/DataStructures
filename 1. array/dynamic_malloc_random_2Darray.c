#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* make2dArray(int rows, int cols) {
	int** temp = (int**)malloc(sizeof(int) * rows);
	int sec = time(NULL);
	srand(sec);

	for (int i = 0; i < rows; i++) {
		temp[i]=(int*)malloc(sizeof(int) * cols);
		//printf("%d ", temp[i]);
	}	
	
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			temp[i][j] = rand() % 45 + 1;

	return temp; //�ּҰ��� ������ ������ ���� �н�
}
int main(void) {

	int** ipp;
	int i,j, rows, cols;
	
	printf("������ �迭�� ���� �Է��ϼ���: ");
	scanf_s("%d %d", &rows, &cols);

	ipp = make2dArray(rows,cols); //������ ������ �ޱ�

	for (i = 0; i < rows; i++) {
		for(j =0; j < cols; j++)
			printf("ipp[%d][%d] = %2d ", i,j, ipp[i][j]);
		if ((j % 3) == 2)
			printf("\n");
	}
	return 0;
}