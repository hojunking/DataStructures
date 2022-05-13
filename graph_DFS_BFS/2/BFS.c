#define _CRT_SECURE_NO_WARININGS
#include <stdio.h>	
#include <stdlib.h>
#define MAX 100

typedef struct node* link;

typedef struct node {
	int vertax;
	link path;
} node;

link graph[MAX] = { NULL };
int queue[MAX] = { NULL };
int visited[MAX] = { 0, };
int n, l;

int front, rear;

node makeEdge(int v, int e) {
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) exit(1);

	nNode->vertax = e;
	nNode->path = graph[v];
	graph[v] = nNode;
}
void addq(int v) {
	if (rear == MAX - 1) exit(1);
	queue[++rear] = v;
}

int deleteq() {
	if (front == rear) exit(1);
	return queue[++front];
}


void BFS(int v) {
	link w;
	front = rear = -1;
	printf("%d ", v);
	visited[v] = 1;
	addq(v);
	while (front != rear) {
		v = deleteq();
		for(w = graph[v]; w; w= w->path)
			if (!visited[w->vertax]) {
				printf("%5d", w->vertax);
				addq(w->vertax);
				visited[w->vertax] = 1;
			}
	}
}

void printAdjList() {
	for (int i = 0; i < n; i++) {
		link temp = graph[i];
		printf("adList[%d] : ", i);
		while (temp) {
			printf("%3d", temp->vertax);
			temp = temp->path;
		}
		printf("\n");
	}
}

int main() {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	int v, e;
	fscanf_s(fp, "%d %d", &n, &l);

	while (fscanf_s(fp, "%d %d", &v, &e) != EOF) {
		makeEdge(v, e);
		makeEdge(e, v);
	}
	printf("<<<<<<<<<< Adjacency List >>>>>>>>>>\n");
	printAdjList();
	
	printf("\n<<<<<<<<<< Breadth First Search >>>>>>>>>>\n");
	for (int i = 0; i < n; i++) {
		printf("dfs<%d> : ", i);
		BFS(i);
		for (int j = 0; j < 10; j++)
			visited[j] = 0;
		printf("\n");
	}
	return 0;
}