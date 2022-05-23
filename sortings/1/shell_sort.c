#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SWAP (x,y,t) (t=x,x=y,y=t)
#define MAX 12

void inc_insertion_sort(int list[], int first, int last, int gap) {
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap) {
        key = list[i]; 

        for (j = i - gap; j >= first && list[j] > key; j = j - gap)
            list[j + gap] = list[j]; 
        list[j + gap] = key;
    }
}
void shell_sort(int list[], int n) {
    int i, gap;
    for (gap = n / 2; gap > 0; gap = gap / 2) {
        if ((gap % 2) == 0)
            gap++; 
        printf("\ngap is\t%d ====> \n", gap);
        for (i = 0; i < gap; i++) 
            inc_insertion_sort(list, i, n - 1, gap);
        
        for (int i = 0; i < n; i++)
            printf("     %d", list[i]);
        printf("\n");
    }
}


int main(void) {
	int n,tmp,list[MAX];
	
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	fscanf_s(fp, "%d", &n);
	int idx = 0;
	while (fscanf_s(fp, "%d ", &tmp) != EOF)
		list[idx++] = tmp;

	printf("list[] data\n");
	for (int i = 0; i < n ;i++)
		printf("    %d", list[i]);

    printf("\n");
    shell_sort(list, n);
	return 0;
}