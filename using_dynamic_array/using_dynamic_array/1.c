#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* makeIdArray(int num) {
	int* temp = (int*)malloc(sizeof(int) * num);
	int sec = time(NULL);
	srand(sec);

	for (int i = 0; i < num; i++) {
		 temp[i] = rand() % 100 +1;
		 //printf("%d ", temp[i]);
	}

	return temp; //주소값을 저장한 포인터 변수 패스
}

int main(void) {

	int* ipp;
	int i, num;


	printf("일차원 배열의 수를 입력하세여: ");
	scanf_s("%d", &num);

	ipp = makeIdArray(num); //포인터 변수가 받기

	for (int i = 0; i < num; i++) {
		printf("ipp[ %2d] = %2d ", i, ipp[i]);
		if ((i % 5) == 4)
			printf("\n");
	}
	return 0;
}