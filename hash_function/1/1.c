#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct element {
	char data[10];
	int key;
} element;

element ht[11] = { NULL };


unsigned int stringToInt(char* key) {
	int number = 0;
	while (*key) {
		number += *key++;
		//if (*key) number += ((int)*key++) << 8;
	}
	//printf("%d ", number);
	return number;
}

int f(int k) {
	return k % 11;
}

int place(int t) {
	while (ht[t].key) {
		t++;
		if (t >= 11) t %= 11;
		
		if (ht[t].key == 0) {
			return t;
		}
	}
	return t;
}

int find(int t, int key) {
	//printf("%d %d ", t, key);
	int cnt = 0;
	if (ht[t].key == key) return 1;
	
	while (1) {
		t++; cnt++;

		//printf("!!%d", cnt);
		if (cnt >= 11) return 0;

		if (t >= 11) t %= 11;
		if (ht[t].key == key) return cnt+1;
		
	}
}
int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	char str[MAX];
	int key, t;
	printf("input strings : ");
	
	while (fscanf_s(fp, "%s ", str, 10) != EOF) {
		printf("%s ", str);
		key = stringToInt(str);
		t = place(f(key));
		//printf("-%d\n", t);

		strcpy(ht[t].data, str);
		ht[t].key = key;
	}

	printf("\n\n\t\titem\tkey\n");
	for (int i = 0; i < 11; i++) {
		printf("ht[  %d] :\t", i);
		printf("%5s\t", ht[i].data);
		printf("%d\n", ht[i].key);
	}
	printf("string to search >>");
	scanf_s("%s", str,10);
	key = stringToInt(str);
	
	int count = find(f(key), key);

	//printf("count : %d\n", count);
	if (count) {
		printf("item : %s, key : %d, the number of comparisons : ", str, key);
		printf("%d\n", count);
	}
	else printf("it dosent't exit!");
	return 0;
}