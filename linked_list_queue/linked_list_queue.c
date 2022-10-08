#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#define MAX 100
/*
	���Ḯ��Ʈ�� ���� ť ����
*/

typedef struct Data {
	int num;
	int class;
	int grade;
}data;

typedef struct Queue {

	data info;
	struct Queue* link;

}queue;


queue* r[3] = { NULL };
queue* f[3] = { NULL };



void push(int num, data info) {
	queue* newNode = (queue*)malloc(sizeof(queue));
	newNode->info = info;
	newNode->link = NULL;
	if (f[num] == NULL) {
		r[num] = newNode;
		f[num] = newNode;
	}
	r[num]->link = newNode; //rear�� ����Ű�� node�� ���ο��带 ����Ŵ
	r[num] = newNode; //rear�� ���ο� ��带 ����Ŵ

	return;
}

void pop(int num) {
	printf("*****************\n");
	while (f[num] != NULL) {
		printf("    %d    %d   %d\n", f[num]->info.class, f[num]->info.grade, f[num]->info.num);
		queue* temp = f[num];
		f[num] = f[num]->link;
		free(temp);
	}
	return;
}



int main(void) {


	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	data temp[13];
	for (int i = 0; i < 13; i++) {
		fscanf_s(fp, "%d %d %d", &temp[i].class, &temp[i].grade, &temp[i].num);
	}
	for (int i = 0; i < 13; i++) {
		push(temp[i].class, temp[i]);
	}
	printf("�����ȣ, �й�, ����\n");
	pop(0);
	pop(1);
	pop(2);
}




