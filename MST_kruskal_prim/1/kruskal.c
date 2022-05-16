#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 50
#define HEAP_FULL(n) (n == MAX_SIZE -1)
#define HEAP_EMPTY(n) (!n)

typedef struct edge {
	int u, v, w, cnt;
} edge;

edge heap[MAX_SIZE];

int disjoint_set[MAX_SIZE];

int n, en,add_weight;
void push(edge edge_t) {
	if (HEAP_FULL(++n)) exit(1);
	int i = n;

	while ((i != 1) && (edge_t.w < heap[i / 2].w)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = edge_t;
	//printf("%d %d %d\n", heap[i].v, heap[i].u, heap[i].w);
}

edge pop() {
	if (HEAP_EMPTY(n)) exit(1);
	int parent = 1, child = 2;
	edge tmp = heap[n--];
	edge pop_edge = heap[1];

	while (child <= n) {
		if ((child < n) && heap[child].w > heap[child + 1].w)
			child++;
		if (tmp.w <= heap[child].w) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = tmp;
	return pop_edge;
}

void disjoint_set_init() {
	for (int i = 1; i < en + 1; i++)
		disjoint_set[i] = i; //자기 자신 바라보게
}

int disjoint_set_find(int i) {
	while (disjoint_set[i] != i) //자기자신(root) or 자기가 가르키는 root 찾기
		i = disjoint_set[i];
	return i;
}
void disjoint_set_merge(int p, int q) {
	disjoint_set[p] = q;
}

void Kruskal() {
	int p, q, len = 0;
	disjoint_set_init();
	edge tmp;

	add_weight = 0;
	while (len < en-1) {
		tmp = pop();
		p = disjoint_set_find(tmp.u);
		q = disjoint_set_find(tmp.v);
		if (p != q) {
			disjoint_set_merge(p, q);
			add_weight += tmp.w;
			printf("(%d,%d) %d\n", tmp.v, tmp.u, tmp.w);
		}
		len++;
	}
	printf("\n최소비용 : %d\n", add_weight);
}


int main() {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	
	n = 0;
	edge tmp;

	fscanf_s(fp, "%d", &en);
	while (fscanf_s(fp,"%d %d %d", &tmp.v, &tmp.u, &tmp.w) != EOF) {
		push(tmp);
	}
	/*for (int i = 1; i <= en; i++) {
		tmp = pop();
		printf("%d %d %d\n", tmp.v, tmp.u, tmp.w);
	}*/
	Kruskal();


	return 0;
}
