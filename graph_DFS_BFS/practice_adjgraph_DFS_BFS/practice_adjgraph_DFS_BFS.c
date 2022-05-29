#define _CRT_SECURE_NO_WARNINIGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define ISFULL(x) (x == MAX-1)

typedef struct node* link;
typedef struct node {
	int vertax;
	link path;
} node;
int n, l;

link graph[MAX] = { NULL };
int visited[MAX], queue[MAX];
int rear, front;

void adjList(int v, int e) {
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) exit(1);

	nNode->vertax = e;
	nNode->path = graph[v];
	graph[v] = nNode;
}

void printList() {
	for (int i = 0; i < n; i++) {
		link tmp = graph[i];
		printf("graph[%d] : ", i);
		while (tmp) {
			printf("%d ", tmp->vertax);
			tmp = tmp->path;
		}
		printf("\n");
	}
}

void DFS(int v) {
	visited[v] = 1;
	link tmp = graph[v];
	printf("%d  ", v);
	while (tmp) {
		if (!visited[tmp->vertax])
			DFS(tmp->vertax);
		tmp = tmp->path;
	}
}

void push(int v) {
	if (ISFULL(rear)) exit(1);
	queue[++rear] = v;
}

int pop() {
	if (front == rear) exit(1);
	return queue[++front];
}


void BFS(int v) {
	memset(visited, 0, MAX);
	front = rear = -1;
	visited[v] = 1;
	printf("%d  ", v);
	push(v);
	while (rear != front) {
		v = pop();
		link tmp = graph[v];
		while (tmp) {
			if (!visited[tmp->vertax]) {
				printf("%d  ", tmp->vertax);
				push(tmp->vertax);
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
		adjList(v, e);
		adjList(e, v);
	}
	printList();
	for (int i = 0; i < n; i++) {
		memset(visited, 0, MAX);
		DFS(i);
		printf("\n");
	}

	printf("\n\n");
	for (int i = 0; i < n; i++) {
		BFS(i);
		printf("\n");
	}
}
