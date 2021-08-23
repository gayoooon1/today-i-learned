#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:4996)



typedef struct Student_
{
	char name[10];
	int snum;
	int pnum[11];
} Student;

void Print_title()
{
	printf("STUDENT ID     ");
	printf("PHONE NUM      ");
	printf(" NAME\n");
}

void Print_Data(Student* Data)
{
	int i = 0;
	Print_title();
	while (i < 10000)
	{
		printf("%d", Data[i].snum);
		printf("      ");

		for (int j = 0; j < 11; j++)
		{
			printf("%d", Data[i].pnum[j]);
		}


		printf("      ");
		printf("%s", Data[i].name);
		printf("\n");
		i = i + 100;
	}


}


void Put_pnum(Student* Data)
{
	int tmp[11];
	int num;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 10000; i++)
	{

		tmp[0] = 0;
		tmp[1] = 1;
		tmp[2] = 0;
		for (int k = 3; k < 11; k++)
		{
			num = rand() % 10;
			tmp[k] = num;
		}

		for (int j = 0; j < 11; j++)
		{
			Data[i].pnum[j] = tmp[j];

		}
	}


}

void Put_name(Student* Data)
{
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
	srand((unsigned)time(NULL));
	int i = 0;
	while (i < 10000)
	{
		num = rand() % (49 + 1);
		strcpy_s(Data[i].name, sizeof(Data[i].name) + 1, name[num]);
		i++;

	}

}

void Put_snum(Student* Data)
{
	int std_num;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 10000; i++)
	{
		int inttmp = 20101234;
		std_num = rand() % (90000 + 1 - 30000) + 30000;
		inttmp = inttmp + std_num;
		Data[i].snum = inttmp;

	}
}

int top = 0;
int Stack[10000];

void Init()
{
	top = 0;
}

void Push(int i)
{
	if (top < 10000)
		Stack[top++] = i;
	else
	{
		printf("STACK IS FULL!\n");
		exit(0);
		return;
	}
}

int Pop()
{
	if (top != 0)
		return Stack[--top];
	else
		printf("STACK IS EMPTY!\n");
	return 1;
	exit(1);
}

int is_Empty()
{
	if (top == 0)
		return 0;
	else
	{
		return 1;
		exit(1);
	}
}

void Quick_sort_snum(Student* Data, int num)
{
	int pivot;
	int left, right;
	int low, high;
	Student temp;

	left = 0;
	right = num - 1;

	Push(right);
	Push(left);

	while (is_Empty() != 0)
	{
		left = Pop();
		right = Pop();

		if (left < right)
		{
			pivot = Data[right].snum;
			low = left - 1;
			high = right;

			while (1)
			{
				while (Data[++low].snum > pivot);
				while (Data[--high].snum < pivot);

				if (low >= high) break;

				temp = Data[low];
				Data[low] = Data[high];
				Data[high] = temp;	
			}
			temp = Data[low];
			Data[low] = Data[right];
			Data[right] = temp;

			Push(right);
			Push(low + 1);
			Push(low - 1);
			Push(left);

		}
	}
}


void Quick_sort_name(Student* Data, int num)
{
	char pivot[10];
	int left, right;
	int low, high;
	Student temp;

	left = 0;
	right = num - 1;
	

	Push(right);
	Push(left);

	while (is_Empty() != 0)
	{
		left = Pop();
		right = Pop();

		if (left < right)
		{
			low = left;
			high = right + 1;
			for (int i = 0; i < 10; i++)
			{
				pivot[i] = Data[left].name[i];
			}

			do
			{
				do
					low++;
				while (low <= right && strcmp(Data[low].name, pivot) > -1);
				do
					high--;
				while (high >= left && strcmp(Data[high].name, pivot) < 0);

				if (low < high)
				{
					temp = Data[low];
					Data[low] = Data[high];
					Data[high] = temp;
				}

				
			} while (low <= high);

			temp = Data[low];
			Data[low] = Data[right];
			Data[right] = temp;

			if (left < high - 1)
			{
				Push(left);
				Push(high - 1);
			}
			if (high + 1 < right)
			{
				Push(right);
				Push(low + 1);
			}
			
			
			

		}
	}
}



int main(void)
{
	Student* Data = malloc(sizeof(Student) * 10000); //전역변수에서는 malloc을 호출할 수 없음

	Put_snum(Data);
	Put_pnum(Data);
	Put_name(Data);
	clock_t start_q, end_q;
	float res_q;

	start_q = clock();
	Quick_sort_snum(Data, 10000);
	end_q = clock();
	printf("학번 기준 \n");
	Print_Data(Data);
	res_q = (float)(end_q - start_q) / CLOCKS_PER_SEC;
	printf("time %.3f\n", res_q);

	start_q = clock();
	Quick_sort_name(Data, 10000);
	end_q = clock();
	printf("이름 기준 \n");
	Print_Data(Data);
	res_q = (float)(end_q - start_q) / CLOCKS_PER_SEC;
	printf("time %.3f\n", res_q);
}

