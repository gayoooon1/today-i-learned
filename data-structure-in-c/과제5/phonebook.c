#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#pragma warning(disable:4996)


typedef struct ListNode {
	char name[10];
	int phone[11];
	struct ListNode* link;
} ListNode;

typedef struct {
	int stack[100];
	int top;
} Stack;

void Init(Stack* s)
{
	s->top = -1;
}

int is_Full(Stack* s)
{
	return (s->top == 99);
}

void Push(Stack* s, int num)
{
	if (is_Full(s))
	{
		printf("STACK ERROR!\n");
		return;
	}
	else s->stack[++(s->top)] = num;
}

int Pop(Stack* s)
{
	return s->stack[(s->top)--];
}

int Peek(Stack* s)
{
	return s->stack[s->top];
}

void Insert_node(ListNode** phead, ListNode* p, ListNode* new_node)
{
	if (*phead == NULL) {   // ���鸮��Ʈ�� ���
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { // p�� NULL�̸� ù��° ���� ����
		new_node->link = *phead;
		*phead = new_node;
	}
	else {          // p ������ ����
		new_node->link = p->link;
		p->link = new_node;
	}
}


void Delete_node(ListNode** phead, ListNode* p, ListNode* removed)
{
	if (p == NULL)
		*phead = (*phead)->link;

	else if (p == (*phead))
	{
		*phead = (*phead)->link;
		free(p);
		return;
	}

	else
		p->link = removed->link;
	free(removed);

}

ListNode* Create_node()
{
	int tmp[11];
	ListNode* newnode = malloc(sizeof(ListNode)); //���ο� ��� ����
	printf("�̸� :");
	scanf("%s", newnode->name);	//name �Է�
	printf("��ȣ :");	//phone �Է�
	for (int i = 0; i < 11; i++)
	{
		scanf("%d", &tmp[i]);
		newnode->phone[i] = tmp[i];
	}
	newnode->link = NULL;
	return newnode;	//newnode �� �ּҰ��� ��ȯ
}



void Display(ListNode* head)
{
	int n = 1;
	ListNode* p = head;
	while (p != NULL) {
		printf("%d. %s ", n, p->name);
		for (int i = 0; i < 11; i++)
		{
			if (i == 3 || i == 7) printf("-");
			printf("%d", p->phone[i]);
		}
		printf("\n");
		p = p->link;
		n++;
	}
	printf("\n");
}

void Total(ListNode* head)
{
	ListNode* p = head;
	int total = 1;
	while (p != NULL)
	{
		p = p->link;
		total++;
	}
	printf("%d ���� ����ó�� �ֽ��ϴ�.\n", total);
}

ListNode* Search_last(ListNode* head) // ��ũ�� NULL�̸� �ּҸ� ��ȯ
{
	ListNode* p = head;
	while (p != NULL)
	{
		p = p->link;
		if (p->link == NULL) return p;
	}

}

ListNode* Search_before(char str[], ListNode* head) //�˻��� �̸��� ���� node
{
	ListNode* p;
	p = head;

	while (p != NULL)
	{
		if (strcmp(p->link->name, str) == 0)
		{
			return p;
		}

		p = p->link;

	}
	return NULL;

}

ListNode* Search_name(char str[], ListNode* head)
{
	ListNode* p;
	p = head;
	while (p != NULL)
	{
		if (strcmp(p->name, str) == 0)
		{
			return p;
		}
		p = p->link;

	}

	return NULL;

}

ListNode* Compare_name(ListNode* newnode, ListNode* head)
{
	ListNode* p;
	p = head;
	while (p != NULL)
	{
		if (strcmp(newnode->name, p->name) >= 0 && strcmp(newnode->name, p->link->name) == -1)
			return p;
		p = p->link;
	}

	return NULL;
}

ListNode* Insertion_sort(ListNode* phead)
{
	ListNode* p, * temp;
	p = phead;

	while (p->link != NULL) {
		if (strcmp(p->name, p->link->name) == 1)
		{
			temp = p->link; // ������ �Űܾ��� ��带 temp�� ����
			p->link = p->link->link; // temp�� ������ ���� ���� ����
			temp->link = phead; // temp�� link�� ���� ù �ڸ��� ����ŵ�ϴ�.
			phead = p = temp; // �׸��� p�� phead ��� temp�� �ʱ�ȭ ������ �� ��� ���� ù�ڸ��� ���� �˴ϴ�.
			continue; // ���� ù �ڸ��� �� p�� ���� p = p->link�� ���ؼ� ������ ���� ���ϵ��� ���� ������ �մϴ�.
		}
		p = p->link;
	}
	return phead;
}



int Menu()
{
	int num;
	printf("1. ã��\n"
		"2. �߰�\n"
		"3. ����\n"
		"4. ����\n"
		"5. �ѱ�\n"
		"6. ����\n"
		"7. ���\n");
	scanf("%d", &num);
	return num;

}

int main()
{
	ListNode* head = NULL;
	ListNode* newnode, * newnode2, * newnode3;
	ListNode* searched;
	ListNode* tmp;
	newnode2 = malloc(sizeof(ListNode));

	int num;
	char name_box[10][7] = { "�谡��" , "������" , "������" , "������" , "������" , "�����" , "�̼���" , "��ٿ�" , "������" , "�輼��" };

	srand((unsigned)time(NULL));

	newnode2->phone[0] = 0;
	newnode2->phone[1] = 1;
	newnode2->phone[2] = 0;

	for (int i = 3; i < 11; i++)
	{
		num = rand() % 10;
		newnode2->phone[i] = num;
	}

	strcpy_s(newnode2->name, sizeof(newnode2->name) + 1, name_box[0]);
	Insert_node(&head, NULL, newnode2);


	int trial = 1;
	while (trial != 10)
	{
		newnode = malloc(sizeof(ListNode));
		newnode->phone[0] = 0;
		newnode->phone[1] = 1;
		newnode->phone[2] = 0;
		for (int k = 3; k < 11; k++)
		{
			num = rand() % 10;
			newnode->phone[k] = num;
		}

		strcpy_s(newnode->name, sizeof(newnode->name) + 1, name_box[trial]);
		Insert_node(&head, newnode2, newnode);

		trial += 1;

		if (trial == 10) //���⼭ ����
		{
			newnode->link = NULL;
			break;
		}

		newnode2 = malloc(sizeof(ListNode));
		newnode2->phone[0] = 0;
		newnode2->phone[1] = 1;
		newnode2->phone[2] = 0;
		for (int i = 3; i < 11; i++)
		{
			num = rand() % 10;
			newnode2->phone[i] = num;
		}

		strcpy_s(newnode2->name, sizeof(newnode2->name) + 1, name_box[trial]);
		Insert_node(&head, newnode, newnode2);
		trial += 1;

	}

	/******************************************************************/

	Stack sort;
	Init(&sort);

	while (1)
	{
		int m = Menu();


		if (m == 1)
		{
			char str[10];
			scanf("%s", str);
			searched = Search_name(str, head);
			if (searched != NULL)
			{
				printf("ã�ҽ��ϴ�.\n");
				for (int i = 0; i < 11; i++)
				{
					if (i == 3 || i == 7) printf("-");
					printf("%d", searched->phone[i]);
				}
				printf("\n");
			}
			else printf("�������� �ʴ� �̸��Դϴ�.\n2���� ���� �߰��ϼ���.\n");
			printf("\n");
		}
		else if (m == 2)
		{
			if (Peek(&sort) == 5)
			{
				newnode3 = Create_node();
				tmp = Compare_name(newnode3, head);
				Insert_node(&head, tmp, newnode3);
				printf("�Է� �Ǿ����ϴ�.\n");
				printf("\n");
				Display(head);
				Total(head);
				printf("\n");

			}
			else
			{
				tmp = Search_last(head);
				Insert_node(&head, tmp, Create_node());
				printf("�Է� �Ǿ����ϴ�.\n");
				Total(head);
				printf("\n");
			}

		}
		else if (m == 3)
		{
			char str[10];
			scanf("%s", str);
			if (strcmp(str, head->name) == 0)
			{
				Delete_node(&head, head, head);
				printf("���� �Ǿ����ϴ�.\n");
				Total(head);
				printf("\n");
			}
			else
			{
				searched = Search_before(str, head);
				Delete_node(&head, searched, Search_name(str, head));
				printf("���� �Ǿ����ϴ�.\n");
				Total(head);
				printf("\n");
			}



		}
		else if (m == 4)
		{
			if (Peek(&sort) == 5)
			{
				printf("���� �ѱ� �����Դϴ�.\n������ ������ �ʿ䰡 �����ϴ�.\n");
				continue;
			}
			else
			{
				Insertion_sort(head);
				Display(head);
				Total(head);
				printf("\n");
			}
		}
		else if (m == 5)
		{
			Push(&sort, 5);
			Insertion_sort(head);
			printf("���� �ѱ� �����Դϴ�.\n");
			printf("\n");
		}

		else if (m == 6)
		{
			Pop(&sort);
			printf("���� ���� �����Դϴ�.\n");
			printf("\n");
		}
		else if (m == 7)
		{
			if (Peek(&sort) == 5)
			{
				Insertion_sort(head);
				Display(head);
				Total(head);
				printf("\n");
			}
			else
			{
				Display(head);
				Total(head);
				printf("\n");
			}

		}


	}




}