#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:4996)



typedef struct TreeNode
{
	char name[10];
	int snum;
	int pnum[11];
	int index;
	struct TreeNode* left;
	struct TreeNode* right;

} TreeNode;


TreeNode* Insert_node(TreeNode* node, TreeNode* newnode)
{
	if (node == NULL) //root가 생성되지 않음
	{
		return newnode;
	}

	else
	{
		if (node->snum > newnode->snum)
			node->left = Insert_node(node->left, newnode);
		else
			node->right = Insert_node(node->right, newnode);
	}
	return node;
}


TreeNode* Create_node()
{

	TreeNode* newnode = malloc(sizeof(TreeNode)); //새로운 노드 생성

	char name[50][6] = { "Mary", "Helen", "Anna", "Janet", "Clara",
						"Grace", "Nancy", "Abbie", "Julia", "Sarah" ,
						"Julie", "Helen", "Carol", "Betty", "Sally",
						"Susan", "Sammy", "Diane","Frank", "Owen",
						"Dona", "Bella", "Evan", "Harry", "Peter",
						"Jack", "Leon", "Fred", "Jim", "Mike",
						"Harry", "Ben", "James", "Henry", "Lily",
						"Annie","Liam", "Noah", "Lucas", "Chris",
						"James", "Luke", "Phil", "Josh", "Emma",
						"Jeff", "Lily", "Brit", "Jane", "Kai" };
	int num;

	num = rand() % (49 + 1);
	strcpy_s(newnode->name, sizeof(newnode->name) + 1, name[num]); //name

	int std_num;//student number
	int inttmp = 20100000;
	std_num = rand() % (90000 + 1 - 30000) + 30000;
	inttmp = inttmp + std_num;
	newnode->snum = inttmp;


	//phone number

	newnode->pnum[0] = 0;
	newnode->pnum[1] = 1;
	newnode->pnum[2] = 0;
	for (int k = 3; k < 11; k++)
	{
		int num = rand() % 10;
		newnode->pnum[k] = num;
	}

	newnode->left = newnode->right = NULL; // 화살표가 NULL을 가리키게 해준다~
	return newnode;	//newnode 의 주소값을 반환
}


void Print_title()
{
	printf(" NO.   ");
	printf("STUDENT ID    ");
	printf("PHONE NUMBER     ");
	printf("  NAME\n");
}

int i = 0;
void Put_index(TreeNode* root) // 중위 순환하면서 index 넣어주는 함수
{
	if (root)
	{

		Put_index(root->left);
		i++;
		root->index = i;
		Put_index(root->right);

	}

}

void Index_search(TreeNode* root, int num)
{
	if (root == NULL) return NULL;
	if (num == root->index)
	{
		if (root->index < 1000) printf(" ");
		printf("%d.  %d", root->index, root->snum);
		printf("      ");

		for (int j = 0; j < 11; j++)
		{
			if (j == 3 || j == 7) printf("-");
			printf("%d", root->pnum[j]);
		}

		printf("      ");
		printf("%s", root->name);
		printf("\n");
	}
	else if (num < root->index) Index_search(root->left, num);
	else Index_search(root->right, num);

}

void Inorder(TreeNode* root)
{
	if (root)
	{
		Inorder(root->left);
		if (root->index % 100 == 0)
		{
			if (root->index < 1000) printf(" ");
			printf("%d.  %d", root->index, root->snum);
			printf("      ");

			for (int j = 0; j < 11; j++)
			{
				if (j == 3 || j == 7) printf("-");
				printf("%d", root->pnum[j]);
			}

			printf("      ");
			printf("%s", root->name);
			printf("\n");
		}

		Inorder(root->right);
	}

}






int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;

	TreeNode* data = malloc(sizeof(TreeNode) * 10000);

	srand((unsigned)time(NULL));

	for (int i = 1; i < 10001; i++)
	{
		TreeNode* tmp = malloc(sizeof(TreeNode));
		tmp = Create_node();
		root = Insert_node(root, tmp);
	}

	Put_index(root);
	Print_title();
	Inorder(root);
	printf("\n");

	while (1)
	{
		printf("순번을 입력하세요\n");
		int num;
		scanf("%d", &num);
		Index_search(root, num);
		printf("\n");
	}



}