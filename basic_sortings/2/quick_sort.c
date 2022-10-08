#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SWAP(x,y,t) (t=x,x=y,y=t)
#define MAX 13


int cnt,n;
void printList(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf(" %2d ", list[i]);
    printf("\n");
}

int partition2(int list[], int left, int right) {
    int pivot = list[left];
    int j = left, tmp;
    for (int i = left + 1; i <= right; i++) {
        if (list[i] < pivot) {
            j++;
            SWAP(list[i], list[j], tmp);
        }
    }
    SWAP(list[left], list[j], tmp);

    printf("pivot = %d :  ", j);
    for (int i = 1; i < n + 1; i++)
        printf("%d ", list[i]);
    printf("\n");
    return j;
}



int partition(int list[], int left, int right) {
    cnt++;
    
    int temp, pivot = list[left];
    int low = left, high = right + 1;
    do {
        do {
            low++;
        } while (low <= right && list[low] < pivot);
        do {
            high--;
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            SWAP(list[low], list[high], temp);
        }
    } while (low < high);
    SWAP(list[left], list[high], temp);

    printf("pivot = %d :  ", list[high]);
    printList(list, n);
    return high;
}



void quick_sort(int list[], int left, int right) {
    
    int p;
    if (left < right) {
        p = partition(list, left, right);
        quick_sort(list, left, p - 1);
        quick_sort(list, p + 1, right);
    }
    
    
}

int main(void) {
    int tmp, list[MAX];
    FILE* fp;
    if (fopen_s(&fp, "input.txt", "r"))
        exit(1);

    fscanf_s(fp, "%d", &n);
    int idx = 0;
    while (fscanf_s(fp, "%d ", &tmp) != EOF)
        list[idx++] = tmp;

    printf("<<<<<<<<< Input List >>>>>>>>>>\n");
    printList(list, n);

    printf("\n");
    cnt = 0;
    printf("execution of quick sort ...\n");
    quick_sort(list, 0, n-1);

    printf("\ncalls of quick sort : %d\n",cnt);

    printf("\n<<<<<<<<< Sorted List >>>>>>>>>>\n");
    printList(list, n);

    return 0;
}