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
int visited[MAX] = { 0, };
int n, l;

node makeEdge(int v, int e) {
	link nNode = (link)malloc(sizeof(node));
	if (!nNode) exit(1);

	nNode->vertax = e; //vertax 생성 시 edge를 포함(다음 vertax)
	nNode->path = graph[v];
	graph[v] = nNode;
}


void DFS(int v) {
	link w = graph[v];
	visited[v] = 1;
	printf("%3d", v);

	while(w){
		if (!visited[w->vertax])//visited = 0 -> DFS
			DFS(w->vertax);
		w = w->path;
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
	printf("\n<<<<<<<<<< Depth First Search >>>>>>>>>>\n");
	for (int i = 0; i < n; i++) {
		printf("dfs<%d> : ", i);
		DFS(i);
		for (int j = 0; j < 10; j++)
			visited[j] = 0;
		printf("\n");
	}
	return 0;
}