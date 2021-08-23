#define _CRT_SECURE_NO_WARNINGS   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#define MAX_LENGTH 128

typedef struct _element {
	char word[MAX_LENGTH];
	char meaning[MAX_LENGTH];
} element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

int GoLeft(TreeNode* node) // 트리 길이 반환 함수
{
	int left = 0;
	//int right;
	while (node->left != NULL)
	{
		node = node->left;
		left++;
	}
	return left;
}

int GoRight(TreeNode* node) // 트리 길이 반환 함수
{
	//int left;
	int right = 0;
	while (node->right != NULL)
	{
		node = node->right;
		right++;
	}
	return right;
}

int GetHeight(TreeNode* root)
{
	int a = GoLeft(root);
	int b = GoRight(root);

	return max(a, b) + 1;
}
int CompareWord(char word[], element e1) // 단어 비교
{
	return strcmp(word, e1.word);
}

TreeNode* SearchWord(TreeNode* root, char word[])
{
	TreeNode* p = root;
	while (p != NULL)
	{
		if (CompareWord(word, p->key) == 0) //두 단어가 같음
			return p;
		else if (CompareWord(word, p->key) < 0) //단어가 루트보다 더 앞에 있음
			p = p->left;
		else if (CompareWord(word, p->key) > 0) //단어가 루트보다 더 뒤에 있음
			p = p->right;
	}
	return p; //검색에 실패하면 NULL 반환
}

int SearchHeight(TreeNode* root, char word[])
{
	TreeNode* p = root;
	int height = 0;
	while (p != NULL)
	{
		if (CompareWord(word, p->key) == 0) //두 단어가 같음
			break;
		else if (CompareWord(word, p->key) < 0)
		{//단어가 루트보다 더 앞에 있음
			p = p->left;
			height++;
		}
		else if (CompareWord(word, p->key) > 0)
		{//단어가 루트보다 더 뒤에 있음
			p = p->right;
			height++;
		}
	}
	return height;
}
void PrintWord(TreeNode* p, char word[])
{
	if (p != NULL) {
		TreeNode* tmp = malloc(sizeof(TreeNode));
		int length = 0;
		tmp = SearchWord(p, word);
		length = SearchHeight(p, word);
		printf("(레벨 %d) %s\n", length, tmp->key.meaning);
	}

}

TreeNode* InsertNode(element* data, int first, int last)
{
	TreeNode* newnode = malloc(sizeof(TreeNode));
	int mid;
	if (first > last) return NULL;
	mid = (first + last) / 2;
	strcpy(newnode->key.meaning, data[mid].meaning);
	strcpy(newnode->key.word, data[mid].word);
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->left = InsertNode(data, first, mid - 1);
	newnode->right = InsertNode(data, mid + 1, last);
	return newnode;

}

int main()
{
	int line_count = 0;
	char buffer[MAX_LENGTH];    // 파일을 읽을 때 사용할 임시 공간
	char del[] = ":";
	char del2[] = "\n";
	char del3[] = " ";
	char* word;
	char* realword;
	char* meaning;
	TreeNode* root = NULL;
	element* p = malloc(sizeof(element) * 51844);


	FILE* fp = NULL;
	if (0 == fopen_s(&fp, "D:\\20-1\\자료구조\\dict_test.txt", "rt"))
	{

		while (fgets(buffer, sizeof(buffer), fp) != NULL) // 문자열 읽기
		{
			line_count++;

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
		}
		printf("사전 파일을 모두 읽었습니다.\n%d개의 단어가 있습니다.\n", line_count);
		fclose(fp);

		root = InsertNode(p, 1, 51844);
		int height = GetHeight(root);

		printf("트리의 전체 높이는 %d입니다.\n단어를 입력하세요.\n", height);
		while (1) {
			scanf("%s", buffer);
			PrintWord(root, buffer);
			printf("\n");
		}

		return 0;
	}
	free(p);
}