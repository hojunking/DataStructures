#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*
	present transpose matrix
*/

typedef struct {
	int col;
	int row;
	int value;
} term;


int main(void) {
	int sec = time(NULL); //시간에 따라
	srand(sec);

	int list[20][20];
	memset(list, 0, sizeof(list));

	int n; printf("원소의 개수를 쓰시오 ..");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
		list[rand() % 20][rand() % 20] = rand() % 100 + 1;
	
	//printMatrix(list);
	
	term sp[400];
	sp[0].row = 20; sp[0].col = 20;
	sp[0].value = n;
	
	printf("Random generated Matrix(20,20)\n");
	int k = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (list[i][j] != 0) {
				sp[++k].row = i;
				sp[k].col = j;
				sp[k].value = list[i][j];
			}
			printf("  %2d", list[i][j]);
		}
		printf("\n");
	}
	printf("\nsparse matrix\n");
	for (int i = 0; i <= k; i++)
		printf("  %2d  %2d   %2d\n", sp[i].row, sp[i].col, sp[i].value);
}
