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

int TransformWordtoNum(char* key) // 문자로 된 키를 숫자로 변환
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
		HashTable[hash_key] = node; // 데이터가 처음 들어왔기 때문에 바로 저장
	}
	else // 값이 이미 들어 있던 경우
	{
		node->next = HashTable[hash_key]; // 현재 추가하는 노드의 next가 해시테이블의[key] point
		HashTable[hash_key] = node; // 이후 해시테이블의 해시 키 값이 새로 추가될 노드를 가리키면 기존에 추가된 노드들이 연결
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
	char buffer[MAX_LENGTH];    // 파일을 읽을 때 사용할 임시 공간
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
	if (0 == fopen_s(&fp, "D:\\20-1\\자료구조\\mod_dict.txt", "rt"))
	{

		while (fgets(buffer, sizeof(buffer), fp) != NULL) // 문자열 읽기
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
			printf("단어 %d : %s", k+1, test[k].word);
			FindPrintHashData(test[k].word);
		}

	}

}