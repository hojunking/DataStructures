#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 50
typedef struct node* link;
typedef struct node {
	link path;
	int vertax;
} node;
link graph[MAX] = { NULL };
int visited[MAX] = { 0, };
int n, l;


void insert(int v, int e) {
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) exit(1);

	nNode->vertax = e;
	nNode->path = graph[v];
	graph[v] = nNode;
}


void printAdjList() {
	for (int i = 0; i < n; i++) {
		link temp = graph[i];
		printf("adList[%d] : ", i);
		while (temp) {
			printf("%5d", temp->vertax);
			temp = temp->path;
		}
		printf("\n");
	}
}

void DFS(int v) {
	link w = graph[v];
	visited[v] = 1;
	printf("%2d ", v);
	while (w) {
		if (!visited[w->vertax])
			DFS(w->vertax);
		w = w->path;
	}
}

void connected(void) {
	int cnt = 0;
	for (int i=0; i < n; i++) {
		if (!visited[i]) {
			printf("connected component %d : ",++cnt);
			DFS(i);
			printf("\n");
		}
	}
}

int main() {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	int e, v;
	fscanf_s(fp, "%d %d", &n, &l);

	for (int i = 0; i < l; i++) {
		fscanf_s(fp, "%d %d", &v, &e);
		insert(v, e);
		insert(e, v);
	}
	printf("<<<<<<<<<< Adjacency List >>>>>>>>>>\n");
	printAdjList();
	printf("\n<<<<<<<<<< Connected Components >>>>>>>>>>\n");
	connected();
	return 0;
}