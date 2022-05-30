#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLE_SIZE 11
#define MAX_SIZE 10

typedef struct listNode {
	char data[MAX_SIZE];
	int key;
	struct listNode* link;
}listNode;

typedef struct listType {
	listNode* chain[MAX_TABLE_SIZE];
}listType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_chain(listType* l)
{
	int i;
	for (i = 0; i < MAX_TABLE_SIZE; i++)
	{
		l->chain[i] = NULL;
	}
}

int stringToInt(char* key)
{
	int number = 0;

	while ((*key) != NULL)
	{
		number += *key++;
	}

	return number;
}

void insert_node(listType* l, char* data)
{
	listNode* new_node = (listNode*)malloc(sizeof(listNode));
	strcpy(new_node->data, data);
	new_node->key = stringToInt(data);
	new_node->link = NULL;

	int i, hash_value;
	i = hash_value = stringToInt(data);
	i = i % MAX_TABLE_SIZE;


	if (l->chain[i] == NULL)
	{
		l->chain[i] = new_node;
	}
	else
	{
		listNode* temp = l->chain[i];

		while (temp->link != NULL)
		{
			temp = temp->link;
		}

		temp->link = new_node;
	}
}

void search_chain(listType* l, char* data)
{
	int i, hash_value;
	i = hash_value = stringToInt(data);
	i = i % MAX_TABLE_SIZE;

	int count = 1;

	listNode* temp = l->chain[i];

	while (temp != NULL)
	{
		if (strcmp(temp->data, data) == 0)
		{
			printf("item: %s, key : %d, the number of comparisions : %d\n\n", data, hash_value, count);
			break;
		}
		count++;
		temp = temp->link;

	}

	if (count == 0)
	{
		printf("dosen't exist!\n");
	}
}
void display_chain(listType* l)
{
	int i;
	listNode* temp;
	printf("          item key\n");

	for (i = 0; i < MAX_TABLE_SIZE; i++)
	{
		temp = l->chain[i];
		printf("ht[%2d] : ", i);
		while (temp != NULL)
		{
			printf("(%s %d)  ", temp->data, temp->key);
			temp = temp->link;
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	char line[100];
	char* delimieter = " \n";
	char* op = NULL;
	char searchNum[MAX_SIZE];

	listType hash;
	init_chain(&hash);

	fgets(line, 100, fa);

	printf(" input strings : %s\n\n", line);

	op = strtok(line, delimieter);
	insert_node(&hash, op);

	while (op != NULL)
	{
		op = strtok(NULL, delimieter);
		if (op == NULL)
		{
			break;
		}
		insert_node(&hash, op);
	}
	display_chain(&hash);

	while (1)
	{
		printf("input \"quit\" to quit\n");
		printf("string to search >> ");
		scanf("%s", searchNum);

		if (strcmp(searchNum, "quit") == 0)
		{
			break;
		}

		search_chain(&hash, searchNum);

	}
}
