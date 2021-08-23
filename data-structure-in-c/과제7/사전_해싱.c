#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#define MAX_LENGTH 128
#define TABLE_SIZE 1999

typedef struct Dict
{
	char word[MAX_LENGTH];
	char meaning[MAX_LENGTH];
} Dict;

typedef struct TestWord
{
	char word[MAX_LENGTH];
} TestWord;

typedef struct Node
{
	Dict dict;
	struct Node* next;
} Node;

Node* HashTable[TABLE_SIZE];

int TransformWordtoNum(char* key) // ���ڷ� �� Ű�� ���ڷ� ��ȯ
{
	int number = 0;
	for (int i = 0; i < strlen(key); i++)
	{
		number += key[i];
	}
	return number;
}

int HashFunction(char* key)
{
	return TransformWordtoNum(key) % TABLE_SIZE;
}

void  MakeHashData(Dict dict, Node* node)
{
	int hash_key = HashFunction(dict.word);// table key
	if (HashTable[hash_key] == NULL)
	{
		HashTable[hash_key] = node; // �����Ͱ� ó�� ���Ա� ������ �ٷ� ����
	}
	else // ���� �̹� ��� �ִ� ���
	{
		node->next = HashTable[hash_key]; // ���� �߰��ϴ� ����� next�� �ؽ����̺���[key] point
		HashTable[hash_key] = node; // ���� �ؽ����̺��� �ؽ� Ű ���� ���� �߰��� ��带 ����Ű�� ������ �߰��� ������ ����
	}
}

void* FindPrintHashData(char* word)
{
	int hash_key = HashFunction(word);
	int cmpnum = 0;
	int totalcmp = 0;

	if (HashTable[hash_key] == NULL)
		return NULL;

	if (strcmp(HashTable[hash_key]->dict.word, word) == 0)
	{
		printf("%s ", HashTable[hash_key]->dict.meaning);
		printf("(%d)\n", cmpnum);
	}
	else
	{
		Node* node = HashTable[hash_key];
		while (node->next)
		{
			if (strcmp(node->next->dict.word, word) == 0)
			{
				printf("%s ",node->next->dict.meaning);
				printf("(%d)\n", cmpnum);
			}
			node = node->next;
			cmpnum++;
		}
	}
	return  NULL;
}


int main()
{
	srand((unsigned)time(NULL));
	int line_count = 0;
	char buffer[MAX_LENGTH];    // ������ ���� �� ����� �ӽ� ����
	char del[] = ":";
	char del2[] = "\n";
	char del3[] = " ";
	char* word;
	char* realword;
	char* meaning;
	int* num = malloc(sizeof(int) * 100);
	Dict* p = malloc(sizeof(Dict) * 34067);
	TestWord* test = malloc(sizeof(TestWord) * 100);


	FILE* fp = NULL;
	if (0 == fopen_s(&fp, "D:\\20-1\\�ڷᱸ��\\mod_dict.txt", "rt"))
	{

		while (fgets(buffer, sizeof(buffer), fp) != NULL) // ���ڿ� �б�
		{
			word = strtok(buffer, del);

			char* tmpmean = strtok(NULL, del);
			meaning = strtok(tmpmean, del2);
			realword = strtok(word, del3);
			strcpy(p[line_count].word, realword);
			if (meaning == NULL)
			{
				p[line_count].meaning[0] = NULL;
			}
			else strcpy(p[line_count].meaning, meaning);
			line_count++;
		}

		fclose(fp);
	
		for (int i = 0; i < 34067; i++)
		{
			Node* newnode = malloc(sizeof(Node));
			strcpy(newnode->dict.word, p[i].word);
			strcpy(newnode->dict.meaning, p[i].meaning);
			newnode->next = NULL;
			MakeHashData(newnode->dict, newnode);
		}

		for (int j = 0; j < 100; j++)
		{
			int temp = rand()% 34067 + 1;
			strcpy(test[j].word, p[temp].word);
		}

		for (int k = 0; k < 100; k++)
		{
			printf("�ܾ� %d : %s", k+1, test[k].word);
			FindPrintHashData(test[k].word);
		}

	}

}