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

int Compare_snum(const void* a, const void* b)    // 내림차순 비교 함수 구현
{
	Student* p1 = (Student*)a;
	Student* p2 = (Student*)b;

	if (p1->snum > p2->snum)    // a가 b보다 클 때는
		return -1;      // -1 반환

	if (p1->snum < p2->snum)    // a가 b보다 작을 때는
		return 1;       // 1 반환

	return 0;           // a와 b가 같을 때는 0 반환

}

int Compare_name(const void* a, const void* b)    // 내림차순 비교 함수 구현
{
	Student* p1 = (Student*)a;
	Student* p2 = (Student*)b;

	return strcmp(p2->name, p1->name);
}



int main(void)
{
	Student* Data = malloc(sizeof(Student) * 10000); //전역변수에서는 malloc을 호출할 수 없음

	Put_snum(Data);
	Put_pnum(Data);
	Put_name(Data);

	clock_t start_q, end_q;
	float res_q;
	printf("QUICK SORT START!\n");
	start_q = clock();
	qsort(Data, 10000, sizeof(Student), Compare_snum);
	end_q = clock();
	printf("학번 기준 \n");
	Print_Data(Data);
	res_q = (float)(end_q - start_q) / CLOCKS_PER_SEC;
	printf("학번 기준 Quick Sort time %f\n", res_q);
	printf("\n");

	start_q = clock();
	qsort(Data, 10000, sizeof(Student), Compare_name);
	end_q = clock();
	printf("이름 기준 \n");
	Print_Data(Data);
	res_q = (float)(end_q - start_q) / CLOCKS_PER_SEC;
	printf("이름 기준 Quick Sort time %f\n", res_q);




}