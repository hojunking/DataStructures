#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#define MAX 100
/*
	연결리스트를 통한 스택구현
*/

typedef struct Data {
	int num;
	int class;
	int grade;
}data;

typedef struct Stack {

	data info;
	struct Stack* link;
	
}stack;


stack* s[3] = { NULL };

void push(int num, data info) {
	stack* newNode = (stack*)malloc(sizeof(stack));
	newNode->info = info;
	newNode->link = s[num];
	s[num] = newNode;
	return;
}

void pop(int num) { 
	stack* current = s[num];
	stack* temp;
	printf("*****************\n");
	while (current != NULL) {
		printf("    %d    %d   %d\n", current->info.class, current->info.grade, current->info.num);
		temp = current;
		current = current->link;
		free(temp);
	}
	return;
}



int main(void) {
	//입력

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
	printf("과목번호, 학반, 성적\n");
	pop(0);
	pop(1);
	pop(2);
}




