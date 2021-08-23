#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:4996)



typedef struct DlistNode
{
	char name[10];
	int snum;
	int pnum[11];
	struct DlistNode* sllink;
	struct DlistNode* srlink;
	struct DlistNode* nllink;
	struct DlistNode* nrlink;

} DlistNode;

void Init(DlistNode* phead)
{
	phead->sllink = phead;
	phead->srlink = phead;
	phead->nllink = phead;
	phead->nrlink = phead;
}

void Dinsert_node_snum(DlistNode* before_snum, DlistNode* new_node)
{
	new_node->sllink = before_snum;
	new_node->srlink = before_snum->srlink;
	before_snum->srlink->sllink = new_node;
	before_snum->srlink = new_node;

}

void Dinsert_node_name(DlistNode* before_name, DlistNode* new_node)
{

	new_node->nllink = before_name;
	new_node->nrlink = before_name->nrlink;
	before_name->nrlink->nllink = new_node;
	before_name->nrlink = new_node;

}

void Print_title()
{
	printf(" NO.   ");
	printf("STUDENT ID    ");
	printf("PHONE NUMBER     ");
	printf("NAME\n");
}

void Display_snum(DlistNode* phead) { // ��ȣ ������ ����Ʈ
	DlistNode* p;
	Print_title();
	int i = 1;
	for (p = phead->srlink; p != phead; p = p->srlink) 
		
	{

			if (i % 100 == 0)
			{
				if (i < 1000) printf(" ");
				printf("%d.  %d", i, p->snum);
				printf("      ");

				for (int j = 0; j < 11; j++)
				{
					printf("%d", p->pnum[j]);
				}

				printf("      ");
				printf("%s", p->name);
				printf("\n");
			}
			i++;
			
		

	}
}

void Display_name(DlistNode* phead) {
	DlistNode* p;
	Print_title();
	int i = 1;
	for (p = phead->nrlink; p != phead; p = p->nrlink)

	{

		if (i % 100 == 0)
		{
			if (i < 1000) printf(" ");
			printf("%d.  %d", i, p->snum);
			printf("      ");

			for (int j = 0; j < 11; j++)
			{
				printf("%d", p->pnum[j]);
			}

			printf("      ");
			printf("%s", p->name);
			printf("\n");
		}
		i++;



	}
}

int Center_snum(DlistNode* phead)
{
	DlistNode* p;
	p = phead;
	int num = 0;
	while (p != phead)
	{
		p = p->srlink; //������ ��ũ���� �̵�
		num++;
	}
	return num; //�׸�

}

int Center_name(DlistNode* phead)
{
	DlistNode* p;
	p = phead;
	int num = 0;
	while (p != phead)
	{
		p = p->nrlink; //������ ��ũ���� �̵�
		num++;
	}
	return num; //�׸�

}

DlistNode* Compare_snum(DlistNode* phead, DlistNode* newnode) //���� �� ��ġ�� ��ȯ�ϴ� �Լ�
{
	DlistNode* p;
	p = phead->srlink;
	while (p != phead)
	{
		if ((newnode->snum < p->snum) && (p->sllink == phead) && (p->srlink == phead)) //���� �۾Ƽ� head �ٷ� �ڿ� �߰�
			return phead;
		else if ((newnode->snum < p->snum) && (newnode->snum < p->sllink->snum)) //p���ٵ� �۰� ���� �ͺ��ٵ� ���� ��
			return p->sllink->sllink;
		else if ((newnode->snum < p->snum) && (newnode->snum > p->sllink->snum)) //p���� ������ ���� �ͺ��� Ŭ ��
			return p->sllink;
		else if ((newnode->snum > p->snum) && (p->sllink == phead) && (p->srlink == phead)) // p���� ũ�� ��, �ڿ� head�� ���� ��(2��° ���)
			return p;
		else if ((newnode->snum > p->snum) && (p->srlink == phead)) // p���� ũ�� �ڿ� head�� ���� ��(2��° ���)
			return p;
		else if ((newnode->snum > p->snum) && (newnode->snum < p->srlink->snum)) //p���� ũ���� ���� �ͺ��� ���� ��
			return p;
		
		else p = p->srlink;
	}
}

DlistNode* Compare_name(DlistNode* phead, DlistNode* newnode)
{
	DlistNode* p;
	p = phead->nrlink;
	while (p != phead)
	{
		if (strcmp(newnode->name, p->name) < 0 && (p->nllink == phead) && (p->nrlink == phead))
			return phead;
		else if (strcmp(newnode->name, p->name) < 0 && strcmp(newnode->name, p->nllink->name) < 0)
			return p->nllink->nllink;
		else if (strcmp(newnode->name, p->name) < 0 && strcmp(newnode->name, p->nllink->name) > 0)
			return p->nllink;
		else if (strcmp(newnode->name, p->name) > 0 && (p->nllink == phead) && (p->nrlink == phead))
			return p;
		else if (strcmp(newnode->name, p->name) > 0 && (p->nrlink == phead))
			return p;
		else if (strcmp(newnode->name, p->name) > 0 && strcmp(newnode->name, p->nrlink->name) < 0)
			return p;
		else p = p->nrlink;
	
	}

}

DlistNode* Create_node()
{

	DlistNode* newnode = malloc(sizeof(DlistNode)); //���ο� ��� ����

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

	return newnode;	//newnode �� �ּҰ��� ��ȯ
}

int main(void)
{
	DlistNode* p[10000];
	DlistNode head_node;

	srand((unsigned)time(NULL)); //main���� �ѹ��� ����
	Init(&head_node);


	for (int i = 0; i < 10000; i++) {
		DlistNode* tmp_snum = malloc(sizeof(DlistNode));
		DlistNode* tmp_name = malloc(sizeof(DlistNode));
		p[i] = malloc(sizeof(DlistNode));
		p[i] = Create_node();
		//tmp_snum = Compare_snum(&head_node, p[i]); //��ġ�� ��ȯ�ϴ� �Լ�
		//Init(&head_node);
		tmp_name = Compare_name(&head_node, p[i]);
		//Dinsert_node_snum(tmp_snum, p[i]);
		Dinsert_node_name(tmp_name, p[i]);
		
	}
	//Display_snum(&head_node);
	Display_name(&head_node);


}