#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 7
#define INF 999

int weight[MAX][MAX];
int distance[MAX]; // shortest distance from source node
int found[MAX]; // visited vertex information
int path[MAX];
int n, m;

int choose() {
	int i, min, minpos;
	min = INF + 1;
	minpos = -1;
	for(i=0; i <n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void shortest(int v, int cost[][MAX]) {
	int ary[7][7] ={0,};
	int index[7];

	int i, u=v, w,j;
	for (i = 0; i < n; i++) {
		found[i] = 0;
		distance[i] = cost[v][i];
	}

	found[v] = 1;
	distance[v] = 0;
	for (i = 0; i < n - 1; i++) {
		
		printf("%d : ", u);
		for(int k=0; k<n; k++){
			printf("  %3d  ", distance[k]);
			ary[i][k] = distance[k];
		}
		printf("\n");
		index[i] = u;
		 
		
		u = choose();
		found[u] = 1;
		for (w = 0; w < n; w++) {
			if (!found[w])
				if (distance[u] + cost[u][w] < distance[w]) {
					distance[w] = distance[u] + cost[u][w];
				}
		}
		
	}
	printf("\n");
	for (i = 1; i < n; i++)
	{
		printf("distance[%d-%d]=%d    : ", 0, i, ary[5][i]);
		for (int k = 1; k <= 6; k++)
		{
			for (j = 1; j <= 6; j++)
			{
				if (ary[j - 1][i] != ary[5][i])
					if (index[j] == 6)
						printf("<%d->%d> ", index[j - 1], i - 1);
					else if (index[j - 1] == 6)
						break;
					else
						printf("<%d->%d> ", index[j - 1], index[j]);
				else break;
			}
			if (index[j - 1] == 6)
				printf("<%d->%d> ", i - 1, i);
			else
				printf("<%d->%d> ", index[j - 1], i);
			if (j != 6) break;
		}
		printf("\n");
	}

}

int main(void) {
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);
	int v, e, w;
	fscanf_s(fp, "%d %d", &n, &m);

	for (int j = 0; j < n; j++) 
		for (int k = 0; k < n; k++) 
			weight[j][k] = INF;

	for (int i = 0; i < n; i++)
		weight[i][i] = 0;

	for (int i = 0; i < m; i++) {
		fscanf_s(fp, "%d %d %d", &v, &e, &w);
		weight[v][e] = w;
		weight[e][v] = w;
	}

	/*for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			printf("%4d ", weight[j][k]);
		}
		printf("\n");
	}*/

	shortest(0, weight);


	return 0;
}


