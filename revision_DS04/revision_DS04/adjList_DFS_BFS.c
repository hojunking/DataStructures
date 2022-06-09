#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#define MAX 50
#define Q_FULL(rear) (rear == MAX-1)
#define Q_EMPTY(front, rear) (front == rear)
#define S_FULL(top)	(top == MAX-1)
#define S_EMPTY(top) (top == -1)

typedef struct node* link;
typedef struct node {
	link path;
	int vertax;
} node;

link root = NULL;
link graph[MAX] = { NULL };
int n, l, front, rear, top;
int visited[MAX] = { 0 };
int queue[MAX];

void makeAdj(int v, int e) {
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) return;

	nNode->vertax = e;
	nNode->path = graph[v];
	graph[v] = nNode;
}

void printList() {
	for (int i = 0; i < n; i++) {
		link tmp = graph[i];
		printf("[%d] ->",i);
		while (tmp) {
			printf("%d ", tmp->vertax);
			tmp = tmp->path;
		}
		printf("\n");
	}
}

void DFS(int v){
	visited[v] = 1;
	link tmp = graph[v];
	printf("%d ", v);

	while (tmp) {
		if (!visited[tmp->vertax])
			DFS(tmp->vertax);
		tmp = tmp->path;
	}
}

void enqueue(int v) {
	if (Q_FULL(rear)) return;
	queue[++rear] = v;
}

int dequeue() {
	if (Q_EMPTY(front, rear)) return 0;
	return queue[++front];
}

void BFS(int v) {
	front = rear = -1;
	visited[v] = 1;
	link tmp = graph[v];
	printf("%d ", v);
	enqueue(v);

	while (!Q_EMPTY(front, rear)) {
		v = dequeue();
		tmp = graph[v];
		while (tmp) {
			if (!visited[tmp->vertax]) {
				printf("%d ", tmp->vertax);
				enqueue(tmp->vertax);
				visited[tmp->vertax] = 1;
			}
			tmp = tmp->path;
		}
	}
}


int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	int v, e;
	fscanf_s(fp, "%d %d", &n, &l);

	while (fscanf_s(fp, "%d %d", &v, &e) != EOF) {
		makeAdj(v, e);
		makeAdj(e, v);
	}
	printList();

	printf("\n");
	for (int i = 0; i < n; i++) {
		memset(visited, 0, MAX);
		printf("[%d] -> ", i);
		DFS(i);
		printf("\n");
	}

	printf("\n");
	for (int i = 0; i < n; i++) {
		memset(visited, 0, MAX);
		printf("[%d] -> ", i);
		BFS(i);
		printf("\n");
	}
	return 0;
}