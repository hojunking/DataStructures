#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SWAP(x,y,t) (t=x,x=y,y=t)
#define MIN(x,y) ((x < y) ? x : y)
#define MAX 13

int n;
void printList(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf(" %2d ", list[i]);

    printf("\n");
}

void merge(int list[], int temp[] ,int left, int mid, int right) {
    int low = left;
    int high = mid + 1, k = left;
   
    while (low <= mid && high <= right) {
        if (list[low] < list[high])
            temp[k++] = list[low++];
        else temp[k++] = list[high++];
    }

    while (low <= mid)
        temp[k++] = list[low++];
   
    for (int i = left; i < k; i++)
        list[i] = temp[i];

}

void merge_sort(int list[],int temp[],int low, int high){
    for (int m = 1; m <= high - low; m = 2 * m) {
        printf("segment size : %d\n", m);
        printf("\t   a : ");
        printList(list, n);
       
        for (int i = low; i < high; i += 2 * m){
            int from = i;
            int mid = i + m - 1;
            int to = MIN(i + 2 * m - 1, high);
            
            merge(list, temp,from, mid, to);
        }
        printf("\ttemp : ");
        printList(temp, n);
        printf("\n");
    }
}

int main(void) {
    int tmp, list[MAX];
    int temp[MAX];
    FILE* fp;
    if (fopen_s(&fp, "input.txt", "r"))
        exit(1);

    fscanf_s(fp, "%d", &n);
    int idx = 0;
    while (fscanf_s(fp, "%d ", &tmp) != EOF) {
        temp[idx] = tmp;
        list[idx++] = tmp;
    }

    printf("<<<<<<<<< Input List >>>>>>>>>>\n");
    printList(list, n);

    printf("\n<<<< executing iterative merge sort >>>>\n");
    merge_sort(list,temp, 0, n - 1);

    printf("\n<<<<<<<<< Sorted List >>>>>>>>>>\n");
    printList(list, n);

    return 0;
}