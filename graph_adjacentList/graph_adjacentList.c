#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50


int graph[MAX_SIZE][MAX_SIZE] = { 0, };
int n, w, v, e;
int adjList[MAX_SIZE][MAX_SIZE];

void makeAdjList() {
	for (int i = 0; i < n; i++) {
		int k = 0;
		for (int j = n-1; 0 <=j; j--) {
			if (graph[i][j]) {
				adjList[i][k++] = j;
			}
		}
	}
}

int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	char g;

	fscanf_s(fp,"%c",&g);

	fscanf_s(fp, "%d %d", &n, &w);
	//printf("%c %d %d", g, n, w);

	if (g == 'd')
		while (fscanf_s(fp, "%d %d", &v, &e) != EOF)
			graph[v][e] = 1;
	else if (g == 'u')
		while (fscanf_s(fp, "%d %d", &v, &e) != EOF)
			graph[v][e] = graph[e][v] = 1;
	else printf("failed!\n");

	makeAdjList();
	printf("<<<<<<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>>>>>\n");
	for (int i = 0; i < n; i++) {
		printf("adjList[%d]  :  ",i);
		for (int j = 0; j < n-1; j++)
			if (j < n - 2)
				printf("  %d ", adjList[i][j]);
			else printf("  %d\n", adjList[i][j]);
	}
	return 0;
}