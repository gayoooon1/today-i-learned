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
	if (*phead == NULL) {   // 공백리스트인 경우
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { // p가 NULL이면 첫번째 노드로 삽입
		new_node->link = *phead;
		*phead = new_node;
	}
	else {          // p 다음에 삽입
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
	ListNode* newnode = malloc(sizeof(ListNode)); //새로운 노드 생성
	printf("이름 :");
	scanf("%s", newnode->name);	//name 입력
	printf("번호 :");	//phone 입력
	for (int i = 0; i < 11; i++)
	{
		scanf("%d", &tmp[i]);
		newnode->phone[i] = tmp[i];
	}
	newnode->link = NULL;
	return newnode;	//newnode 의 주소값을 반환
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
	printf("%d 명의 연락처가 있습니다.\n", total);
}

ListNode* Search_last(ListNode* head) // 링크가 NULL이면 주소를 반환
{
	ListNode* p = head;
	while (p != NULL)
	{
		p = p->link;
		if (p->link == NULL) return p;
	}

}

ListNode* Search_before(char str[], ListNode* head) //검색한 이름의 이전 node
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
			temp = p->link; // 앞으로 옮겨야할 노드를 temp에 저장
			p->link = p->link->link; // temp에 저장한 것을 빼고 연결
			temp->link = phead; // temp의 link는 가장 첫 자리를 가리킵니다.
			phead = p = temp; // 그리고 p와 phead 모두 temp로 초기화 함으로 써 모두 가장 첫자리로 가게 됩니다.
			continue; // 가장 첫 자리로 간 p가 밑의 p = p->link로 인해서 앞으로 가지 못하도록 막는 역할을 합니다.
		}
		p = p->link;
	}
	return phead;
}



int Menu()
{
	int num;
	printf("1. 찾기\n"
		"2. 추가\n"
		"3. 삭제\n"
		"4. 정렬\n"
		"5. 켜기\n"
		"6. 끄기\n"
		"7. 목록\n");
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
	char name_box[10][7] = { "김가윤" , "한지희" , "박혜나" , "박주희" , "전영완" , "노민주" , "이세은" , "허다연" , "김형섭" , "김세일" };

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

		if (trial == 10) //여기서 끝남
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
				printf("찾았습니다.\n");
				for (int i = 0; i < 11; i++)
				{
					if (i == 3 || i == 7) printf("-");
					printf("%d", searched->phone[i]);
				}
				printf("\n");
			}
			else printf("존재하지 않는 이름입니다.\n2번을 눌러 추가하세요.\n");
			printf("\n");
		}
		else if (m == 2)
		{
			if (Peek(&sort) == 5)
			{
				newnode3 = Create_node();
				tmp = Compare_name(newnode3, head);
				Insert_node(&head, tmp, newnode3);
				printf("입력 되었습니다.\n");
				printf("\n");
				Display(head);
				Total(head);
				printf("\n");

			}
			else
			{
				tmp = Search_last(head);
				Insert_node(&head, tmp, Create_node());
				printf("입력 되었습니다.\n");
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
				printf("삭제 되었습니다.\n");
				Total(head);
				printf("\n");
			}
			else
			{
				searched = Search_before(str, head);
				Delete_node(&head, searched, Search_name(str, head));
				printf("삭제 되었습니다.\n");
				Total(head);
				printf("\n");
			}



		}
		else if (m == 4)
		{
			if (Peek(&sort) == 5)
			{
				printf("정렬 켜기 상태입니다.\n정렬을 진행할 필요가 없습니다.\n");
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
			printf("정렬 켜기 상태입니다.\n");
			printf("\n");
		}

		else if (m == 6)
		{
			Pop(&sort);
			printf("정렬 끄기 상태입니다.\n");
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