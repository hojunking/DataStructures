#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX 7
#define INF 1000L

int en;
int W[MAX][MAX] = {
{ 0, 28, INF, INF, INF, 10, INF },
{ 28, 0, 16, INF, INF, INF, 14 },
{ INF, 16, 0, 12, INF, INF, INF },
{ INF, INF, 12, 0, 22, INF, 18 },
{ INF, INF, INF, 22, 0, 25, 24 },
{ 10, INF, INF, INF, 25, 0, INF },
{ INF, 14, INF, 18, 24, INF, 0 } };
int selected[MAX], distance[MAX];

int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) { v = i; break; }
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v]))
			v = i;
	return v;
}


void prim(int n) {
	int v =-1, bu, u =0;
	for (int i = 0; i < n; i++) {
		distance[i] = INF;
		selected[i] = 0;
	}
	distance[0] = 0;

	for (int j = 0; j < n; j++) {
		bu = u;
		u = get_min_vertex(n);
		selected[u] = 1;
		printf("선택 vertax : %d,   distance :\t", u);

		if (distance[u] == INF) return;
		
		for (int p = 0; p < n; p++)
			if (distance[p] == INF)
				printf("INF  ");
			else
				printf("%3d  ", distance[p]);
		
		if (v != -1)
			printf("선택 edge : (%d, %d) distance : %d\n", bu, u, distance[u]);
		else printf("\n");

		for (v = 0; v < n; v++)
			if (W[u][v] != INF)
				if (!selected[v] && W[u][v] < distance[v])
					distance[v] = W[u][v];
	}


}
int main() {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	int v, u, w;
	int n = MAX;

	fscanf_s(fp, "%d", &en);
	while (fscanf_s(fp, "%d %d %d", &v, &u, &w) != EOF) {
		W[v][u] = w;
		W[u][v] = w;
	}
	for (int i = 0; i < n; i++)
		W[i][i] = 0;
	 
	/*for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (W[i][j] == INF)
				printf("INF ");
			else
				printf("%2d ", W[i][j]);
		}
		printf("\n");
	}*/
	prim(n);
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += distance[i];
	printf("최소 비용 : %d ", sum);
	return 0;
}