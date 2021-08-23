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

void Heapsort_Print_Data(Student* Data)
{
	int i = 1;
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


void Selection_sort_by_snum(Student* Data)
{
	Student temp;
	int max;
	for (int i = 0; i < 10000 - 1; i++)
	{
		max = i;
		for (int j = i + 1; j < 10000; j++)
		{
			if (Data[j].snum > Data[max].snum)
			{
				max = j;

			}

		}
		temp = Data[max];
		Data[max] = Data[i];
		Data[i] = temp;

	}
	printf("학번 기준 \n");
	Print_Data(Data);
}

void Selection_sort_by_name(Student* Data)
{
	int max;
	Student temp;
	for (int i = 0; i < 10000 - 1; i++)
	{
		max = i;
		for (int j = i + 1; j < 10000; j++)
		{
			if (strcmp(Data[max].name , Data[j].name) < 0)
			{
				max = j;

			}

		}

		temp = Data[max];
		Data[max] = Data[i];
		Data[i] = temp;		
		

	}
	printf("이름 기준 \n");
	Print_Data(Data);
}

int Partition_snum(Student* Data, int left, int right)
{
	int pivot;
	int low, high;
	Student temp;

	low = left;
	high = right + 1;
	pivot = Data[left].snum;
	do
	{
		do 
			low++;
		while (low <= right && Data[low].snum >= pivot);
		do 
			high--;
		while (high >= left && Data[high].snum < pivot);
		if (low < high)
		{
			temp = Data[low];
			Data[low] = Data[high];
			Data[high] = temp;
		}
	} while (low < high);

	temp = Data[left];
	Data[left] = Data[high];
	Data[high] = temp;
	return high;
}

void Quick_sort_snum(Student* Data, int left, int right)
{
	if (left < right)
	{
		int q = Partition_snum(Data, left, right);
		Quick_sort_snum(Data, left, q - 1);
		Quick_sort_snum(Data, q + 1, right);
	}
		
	return;
}

int Partition_name(Student* Data, int left, int right)
{
	char pivot[10];
	int low, high;
	Student temp;

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
		while (low <= right && strcmp(Data[low].name ,pivot) > -1);
		do
			high--;
		while (high >= left && strcmp(Data[high].name , pivot) < 0);
		if (low < high)
		{
			temp = Data[low];
			Data[low] = Data[high];
			Data[high] = temp;
		}
	} while (low < high);

	temp = Data[left];
	Data[left] = Data[high];
	Data[high] = temp;
	return high;
}

void Quick_sort_name(Student* Data, int left, int right)
{
	if (left < right)
	{
		int q = Partition_name(Data, left, right);
		Quick_sort_name(Data, left, q - 1);
		Quick_sort_name(Data, q + 1, right);
	}

	return;
}

void Adjust_snum(Student* Data, int root, int n)
{
	int child, rootkey;
	int temp;
	temp = Data[root].snum;
	rootkey = Data[root].snum;
	child = 2 * root;

	while (child <= n)
	{
		if ((child < n) && (Data[child].snum >= Data[child + 1].snum))
		{
			child++;
		}
		if (rootkey <= Data[child].snum) break;
		else
		{
			Data[child / 2].snum = Data[child].snum;
			child *= 2;
		}
	}
	Data[child / 2].snum = temp;
}



void Heapsort_snum(Student* Data, int n)
{
	int i;
	Student temp;
	for (i = n / 2; i > 0; i--) 
		Adjust_snum(Data, i, n);
	for (i = n - 1; i > 0; i--)
	{
		temp = Data[1];
		Data[1] = Data[i + 1];
		Data[i + 1] = temp;
		Adjust_snum(Data, 1, i);
	}
	
}

void Adjust_name(Student* Data, int root, int n)
{
	int child;
	char rootkey[10];
	char temp[10];
	for (int i = 0; i < 10; i++)
	{
		temp[i] = Data[root].name[i];
		rootkey[i] = Data[root].name[i];
	}

	child = 2 * root;

	while (child <= n)
	{
		if ((child < n) && strcmp(Data[child].name , Data[child + 1].name) > -1) //0이나 1
		{
			child++;
		}
		if (strcmp(rootkey , Data[child].name) < 1) break; //<=
		else
		{
			for (int j = 0; j < 10; j++)
			{
				Data[child / 2].name[j] = Data[child].name[j];
			}
			child *= 2;
		}
	}
	for (int k = 0; k < 10; k++)
	{
		Data[child / 2].name[k] = temp[k];
	}
}

void Heapsort_name(Student* Data, int n)
{
	int i;
	Student temp;
	for (i = n / 2; i > 0; i--)
		Adjust_name(Data, i, n);
	for (i = n - 1; i > 0; i--)
	{
		temp = Data[1];
		Data[1] = Data[i + 1];
		Data[i + 1] = temp;
		Adjust_name(Data, 1, i);
	}

}

int main(void)
{
	Student* Data = malloc(sizeof(Student) * 10000); //전역변수에서는 malloc을 호출할 수 없음
	
	Put_snum(Data);
	Put_pnum(Data);
	Put_name(Data);
	clock_t start_s, start_q, start_h, end_s, end_q, end_h;
	float res_s, res_q, res_h;

	printf("SELECTION SORT START!\n");
	start_s = clock();
	Selection_sort_by_snum(Data);
	end_s = clock();
	res_s = (float)(end_s - start_s) / CLOCKS_PER_SEC;
	printf("학번 기준 Selection Sort time %.3f\n", res_s);
	printf("\n");

	start_s = clock();
	Selection_sort_by_name(Data);
	end_s = clock();
	res_s = (float)(end_s - start_s) / CLOCKS_PER_SEC;
	printf("이름 기준 Selection Sort time %.3f\n", res_s);
	printf("\n");
	printf("\n");


	printf("QUICK SORT START!\n");
	start_q = clock();
	Quick_sort_snum(Data, 0, 9999);
	end_q = clock();
	printf("학번 기준 \n");
	Print_Data(Data);
	res_q = (float)(end_q - start_q) / CLOCKS_PER_SEC;
	printf("학번 기준 Quick Sort time %.3f\n", res_q);
	printf("\n");

	start_q = clock();
	Quick_sort_name(Data, 0, 9999);
	end_q = clock();
	printf("이름 기준 \n");
	Print_Data(Data);
	res_q = (float)(end_q - start_q) / CLOCKS_PER_SEC;
	printf("이름 기준 Quick Sort time %.3f\n", res_q);
	printf("\n");
	printf("\n");


	printf("HEAP SORT Start!\n");
	printf("학번 기준 \n");
	start_h = clock();
	Heapsort_snum(Data, 9999);
	end_h = clock();
	Heapsort_Print_Data(Data);
	res_h = (float)(end_h - start_h) / CLOCKS_PER_SEC;
	printf("학번 기준 Heap Sort time %.3f\n", res_h);
	printf("\n");

	printf("이름 기준 \n");
	start_h = clock();
	Heapsort_name(Data, 9999);
	end_h = clock();
	Heapsort_Print_Data(Data);
	res_h = (float)(end_h - start_h) / CLOCKS_PER_SEC;
	printf("이름 기준 Heap Sort time %.3f\n", res_h);

	
	free(Data);

}