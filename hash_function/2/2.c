#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TABLE_SIZE 8

typedef struct {
	int key;
}element;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}


void print_randNum(int* pa)
{
	int i;
	for (i = 1; i < MAX_TABLE_SIZE; i++)
	{
		printf("randNum[%d] : %d\n", i, pa[i]);
	}
	printf("\n");

}

void init_hash(element* a)
{
	int i;
	for (i = 0; i < MAX_TABLE_SIZE; i++)
	{
		a[i].key = 0;
	}
}


void add_random(element* e, int* randNum, int key)
{
	int hash_value, i;
	i = hash_value = key % MAX_TABLE_SIZE;
	int j = 1;
	while (e[i].key != 0)
	{
		i = (hash_value + randNum[j++]) % MAX_TABLE_SIZE;

		if (j == 7)
		{
			error("overflow");
		}
	}

	e[i].key = key;
}


void search_random(element* e, int* randNum, int key)
{
	int hash_value, i;
	i = hash_value = key % MAX_TABLE_SIZE;
	int j = 1;
	int count = 1;
	while (e[i].key != key)
	{
		count++;
		i = (hash_value + randNum[j++]) % MAX_TABLE_SIZE;

		if (j == 7)
		{
			printf("dosen't exist!\n");
			return;
		}
	}

	printf("key : %d, the number of comparisions : %d\n", key, count);
}

void print_hash(element* e)
{
	int i;
	printf("         key\n");

	for (i = 0; i < MAX_TABLE_SIZE; i++)
	{
		if (e[i].key == 0)
		{
			printf("ht[%2d] :\n", i);
		}
		else
		{
			printf("ht[%2d] : %d\n", i, e[i].key);
		}
	}

}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	int i = 0;
	int j;
	int seedNum;
	int randNum[MAX_TABLE_SIZE];
	int ht[MAX_TABLE_SIZE];
	int data;

	element hash[MAX_TABLE_SIZE];
	init_hash(hash);


	printf("key sequence from file : ");
	while (fscanf(fa, "%d", &data) != EOF)
	{
		printf("%5d", data);
		ht[i++] = data;
	}
	printf("\n");

	printf("input seed >> ");
	scanf("%d", &seedNum);

	srand(seedNum);

	printf("\n");
	for (i = 1; i < MAX_TABLE_SIZE; i++)
	{
		data = (rand() % (MAX_TABLE_SIZE - 1)) + 1;
		randNum[i] = data;

		for (j = 1; j < i; j++)
		{
			if (randNum[j] == data)
			{
				i--;
				break;
			}
		}



	}

	print_randNum(randNum);

	for (i = 0; i < 6; i++)
	{
		add_random(hash, randNum, ht[i]);
	}

	print_hash(hash);

	while (1)
	{
		printf("\ninput 0 to quit\n");
		printf("key to search >> ");
		scanf("%d", &data);

		if (data == 0)
		{
			break;
		}

		search_random(hash, randNum, data);
	}

	return 0;

}