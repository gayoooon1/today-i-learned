#include <stdio.h>
#include <string.h>

typedef char word;
typedef struct {
	word queue[20];
	int front, rear, num;
} QueueType;

void init(QueueType* q) //�ʱ�ȭ �Լ�
{
	q->front = q->rear = 0;
	q->num = 0;
}

int is_empty(QueueType* q) //���� ���� �˻� �Լ�
{
	if ((q->front == q->rear) && (q->front == 0 && q->rear == 0)) return 0;
	else return -1;
}

int is_full(QueueType* q) //��ȭ ���� �˻� �Լ�
{
	if ((q->rear + 1) % 20 == q->front) return 0;
	else return -1;
}

void add_queue(QueueType* q, word item) //ť�� ���ڸ� �ִ� �Լ�
{
	if(is_full(q) == 0)
	{
		printf("ADDQUEUE(%c) FAILED : QUEUE IS FULL",item);
		exit(1);
	}
	else
	{
		q->rear = (q->rear + 1) % 20;
		q->queue[q->rear] = item;
		q->num++;
		printf("ADDQUEUE(%c)\n", item);
		printf("F=%d R=%d\n", q->front, q->rear);
	}
}

void print_queue(QueueType* q) //ť�� ���¸� print�ϴ� �Լ�
{
	int i = q->front+1;
	int j;
	printf("QUEUE = ");
	for (j = 0; j< q->num; j++)
	{
		printf("%c", q->queue[i%20]);
		i++;
	}
	printf(" (%d)\n",q->num);
}


void del_queue(QueueType* q) //ť ���� ���ڸ� �����ϴ� �Լ�
{
	if (is_empty(q) == 0)
	{
		printf("DELETEQUEUE() FAILED : QUEUE IS EMPTY\n");
	}
	else
	{
		q->front = (q->front + 1) % 20;
		q->num--;
		printf("DELETEQUEUE() : %c\n",q->queue[q->front]);
		printf("F=%d R=%d\n", q->front, q->rear);
	}

}

int main(void)
{	int a;
	int b;
	char wordnote[20];
	QueueType q;
	init(&q);

	while (1)
	{
		
		printf("ť ������ ���� ���� �Է��� 1��, ť ������ ���� ���� �Է��� 2���� �����ּ���.");
		scanf_s("%d", &a);
		if (a == 1)
		{
			scanf_s("%s", wordnote, 20);
			for (int i = 0; i < strlen(wordnote); i++)
			{
				add_queue(&q, wordnote[i]);
			}
			print_queue(&q);
			char wordnote = { 0, };
			
		}
		if (a == 2)
		{
			scanf_s("%d", &b);
			for (int i = 0; i < b; i++)
			{
				del_queue(&q);
			}
			print_queue(&q);
			
			
		}
	}
}