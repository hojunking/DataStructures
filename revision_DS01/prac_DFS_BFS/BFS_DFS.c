#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50
#define IS_FULL(rear) (rear == MAX-1)
#define IS_EMPTY(front,rear) (front == rear)


typedef struct node* link;
typedef struct node {
	link path;
	int vertax;
} node;

link graph[MAX] = { NULL };
int visited[MAX] = { 0, };
int queue[MAX];
int n, l, front, rear;

void makeAdj(int v, int e) {
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) exit(1);

	nNode->vertax = e;
	nNode->path = graph[v];
	graph[v] = nNode;
}

void printList() {
	for (int i = 0; i < n; i++) {
		link tmp = graph[i];
		printf("[%d] -> ", i);
		while (tmp) {
			printf("%d ", tmp->vertax);
			tmp = tmp->path;
		}
		printf("\n");
	}
}

void push(int item) {
	if (IS_FULL(rear)) {
		printf("IS FULL!\n");
		return;
	}
	queue[++rear] = item;
}

int pop() {
	if (IS_EMPTY(front, rear)) {
		printf("IS_EMPTY!\n");
		return 0;
	}
	return queue[++front];
}

void BFS(int v) {
	front = rear = -1;
	visited[v] = 1;
	link tmp = graph[v];
	printf("%d ", v);
	push(v);
	while (!IS_EMPTY(front, rear)) {
		v = pop();
		tmp = graph[v];
		while (tmp) {
			if (!visited[tmp->vertax]) {
				printf("%d ", tmp->vertax);
				push(tmp->vertax);
				visited[tmp->vertax] = 1;
			}
			tmp = tmp->path;
		}
	}
}

void DFS(int v) {
	visited[v] = 1;
	link tmp = graph[v];
	printf("%d ", v);

	while (tmp) {
		if (!visited[tmp->vertax])
			BFS(tmp->vertax);
		tmp = tmp->path;
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
