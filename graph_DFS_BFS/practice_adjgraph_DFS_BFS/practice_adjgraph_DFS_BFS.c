#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
#define ISFULL(x) (x == MAX_SIZE-1)
#define ISEMPTY(x) (!x)

typedef struct node* link;
typedef struct node {
	int vertax;
	link path;
} node;

int n, l, rear, front;
int visited[MAX_SIZE], queue[MAX_SIZE];
link graph[MAX_SIZE] = { NULL };

void adjList(int v, int e) {
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) exit(1);
	
	nNode->vertax = e;
	nNode->path = graph[v];
	graph[v] = nNode;
}

void printList() {
	for (int i = 0; i < n; i++) {
		printf("Graph[%d] : ", i);
		link tmp = graph[i];
		while (tmp) {
			printf(" %d ", tmp->vertax);
			tmp = tmp->path;
		}
		printf("\n");
	}
}
void push(int v) {
	if(ISFULL(++rear)) exit(1);
	queue[rear] = v;
}

int pop() {
	if (front == rear) exit(1);
	return queue[++front];
}

void DFS(int v) {
	visited[v] = 1;
	link tmp = graph[v];
	printf("%d ", v);

	while (tmp) {
		if (!visited[tmp->vertax])
			DFS(tmp->vertax);
		tmp = tmp->path;
	}
}

void BFS(int v) {
	rear = front = -1;
	visited[v] = 1;
	link tmp = graph[v];
	printf("%d ", v);
	push(v);
	while (rear != front) {
		v = pop();
		tmp = graph[v];
		while (tmp) {
			if (!visited[tmp->vertax]) {
				printf("%d ", tmp->vertax);
				visited[tmp->vertax] = 1;
				push(tmp->vertax);
			}
			tmp = tmp->path;
		}
	}
}


int main(void) {
	FILE* fp;
	int v, e; // vertax & edge

	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	fscanf_s(fp, "%d %d", &n, &l);
	
	while (fscanf_s(fp, "%d %d", &v, &e) != EOF) {
		adjList(v, e);
		adjList(e, v);
	}
	printList();
	memset(visited, 0, MAX_SIZE);
	DFS(0);
	return 0;
}
