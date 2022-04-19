#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int findCompare(char* str, char* cmp) {
	int strLen = strlen(str)-1;
	int cmpLen = strlen(cmp)-1;

	for (int i = cmpLen; i < strLen + 1; i++) {
		int k = cmpLen, cnt = 0;
		
		for (int j = i; 0 <= j; j--) {
			if (str[j] == cmp[k--]) {
				cnt++;
				if (cnt == cmpLen+1)
					return j;
				continue;
			}
			else break;
		}
	}
	return -1;
}

int main(void) {
	char str[MAX];
	char cmp[MAX];

	printf("���ڿ��� �Է��ϼ��� : ");
	scanf_s("%s", str, MAX);
	
	printf("���� ������ �Է��ϼ��� : ");
	scanf_s("%s", cmp, MAX);
	
	printf("���ڿ� %d��°���� ���� ���۵�..", findCompare(str, cmp));
}