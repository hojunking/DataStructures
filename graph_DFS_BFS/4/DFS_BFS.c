#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 50


typedef struct node* link;
typedef struct node {
	link path;
	int vertax;
}node;
int n, l; //vertax num, edge l

link graph[MAX] = { NULL };
bool visited[MAX];
/* make queue*/
int front, rear;
int queue[MAX];

void AdjList(int v, int e) { //Make Adjacemt List
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) exit(1);
	
	nNode->vertax = e;
	nNode->path = graph[v];
	graph[v] = nNode;
}


void printAdjList() {
	for (int i = 0; i < n; i++) {
		printf("adj[%d] : ",i);
		link tmp = graph[i];
		while (tmp) {
			printf(" %d ", tmp->vertax);
			tmp = tmp->path;
		}
		printf("\n");
	}
}

void DFS(int v) {
	visited[v] = true;
	link tmp = graph[v];
	printf("%3d ", v);
	while (tmp) {
		if (!visited[tmp->vertax])
			DFS(tmp->vertax);
		tmp = tmp->path;
	}
}
void push(int v) {
	if (rear == MAX - 1) exit(1);
	queue[++rear] = v;
}

int pop() {
	if (front == rear) exit(1);
	return queue[++front];
}

void BFS(int v) {
	front = rear = -1;

	visited[v] = true;
	link tmp = graph[v];
	printf("%3d ", v);
	push(v);
	while (front != rear) {
		v = pop();
		tmp = graph[v];
		while (tmp) {
			if (!visited[tmp->vertax]) {
				printf("%3d ", tmp->vertax);
				push(tmp->vertax);
				visited[tmp->vertax] = true;
			}
			tmp = tmp->path;
		}
	}
}


int main() {
	FILE* fp;
	int v, e; // vertax & edge
	
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	fscanf_s(fp, "%d %d", &n, &l);
	
	while (fscanf_s(fp, "%d %d", &v, &e) != EOF) {
		AdjList(v, e);
		AdjList(e, v);
	}
	printAdjList();
	printf("\n<<<<<<<<<< Depth First Search >>>>>>>>>>\n");
	for (int i = 0; i < n; i++) {
		printf("dfs [%d] => ",i);
		memset(visited, false, MAX);
		DFS(i);
		printf("\n");
	}

	printf("\n<<<<<<<<<< Breath First Search >>>>>>>>>>\n");
	for (int i = 0; i < n; i++) {
		printf("bfs [%d] => ", i);
		memset(visited, false, MAX);
		BFS(i);
		printf("\n");
	}

	return 0;
}

