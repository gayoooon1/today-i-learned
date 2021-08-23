#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_VETICLES 21
#define INF 1000000 // ���Ѵ�, ������ ���� ���

typedef struct Subway {
	char name[20]; // ���� ����
	int distance[MAX_VETICLES];
} Subway;

Subway info[MAX_VETICLES] = {
	{"ȫ���Ա�", {0,110,INF,INF,INF,500,INF,INF,INF,INF,INF,INF,INF,80,INF,INF,INF,INF,INF,INF,INF}},
	{"����", {110,0,50,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,210,INF,INF,INF,INF,INF,INF}},
	{"���", {INF,50,0,50,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"����â",{INF,INF,50,0,80,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"����", {INF,INF,INF,80,0,90,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"����", {500,INF,INF,INF,90,0,560,INF,460,INF,INF,INF,INF,INF,INF,INF,320,INF,INF,INF,75}},
	{"���", {INF,INF,INF,INF,INF,560,0,360,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,540,INF}},
	{"����", {INF,INF,INF,INF,INF,INF,360,0,80,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"���￪", {INF,INF,INF,INF,INF,460,INF,80,0,90,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"��û", {INF,INF,INF,INF,INF,INF,INF,INF,90,0,370,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"������", {INF,INF,INF,INF,INF,INF,INF,INF,INF,370,0,75,INF,INF,INF,INF,INF,INF,INF,INF,90}},
	{"����",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,75,0,80,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"�̴�",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,80,0,60,INF,INF,INF,INF,INF,INF,INF}},
	{"����",{80,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,60,0,INF,INF,INF,INF,INF,INF,INF}},
	{"���",{INF,210,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,125,INF,INF,INF,INF,INF}},
	{"��ȸ�ǻ��",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,125,0,230,INF,INF,INF,INF}},
	{"���ǵ�",{INF,INF,INF,INF,INF,320,INF,INF,INF,INF,INF,INF,INF,INF,INF,230,0,350,410,INF,INF}},
	{"�ű�",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,350,0,INF,170,INF}},
	{"����",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,410,INF,0,80,INF}},
	{"�뷮��",{INF,INF,INF,INF,INF,INF,540,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,170,80,0,INF}},
	{"�ֿ���",{INF,INF,INF,INF,INF,75,INF,INF,INF,INF,90,INF,INF,INF,INF,INF,INF,INF,INF,INF,0}}
};


int record[MAX_VETICLES];
int distance[MAX_VETICLES]; // ���� �������κ��� �ִ� ��� �Ÿ�
int found[MAX_VETICLES]; // �湮�� ���� ǥ��
int visited[MAX_VETICLES];

int FindStationNum(char* station)
{
	int i = 0;
	for (int j = 0; j < MAX_VETICLES; j++)
	{
		if (strcmp(station, info[j].name) != 0) i++;
		else if (strcmp(station, info[j].name) == 0) break;
	}
	return i;
}
void ShowStationsByDfs(int v)
{
	visited[v] = TRUE;
	printf("%s", info[v].name);
	if (v != 20) printf(" - ");
	for (int i = 0; i < 21; i++)
	{
		if (info[v].distance[i] && !visited[i])
			ShowStationsByDfs(i);
	}

}

int FindMin(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
	{
		if (distance[i] < min && !found[i])
		{
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void CalculateShortestPath(int start)
{
	for (int i = 0; i < MAX_VETICLES; i++)
	{

		record[i] = start;
		distance[i] = info[start].distance[i];
		found[i] = FALSE;
	}
	found[start] = TRUE; //���� ���� �湮 ǥ��//
	distance[start] = 0;
	for (int i = 0; i < MAX_VETICLES - 2; i++)
	{
		int min = FindMin(distance, MAX_VETICLES, found);
		found[min] = TRUE;
		for (int j = 0; j < MAX_VETICLES; j++)
		{
			if (found[j] == FALSE) // ���� ���� ���� ��
			{
				if (distance[min] + info[min].distance[j] < distance[j])
				{
					distance[j] = distance[min] + info[min].distance[j];
					record[j] = min;

				}

			}

		}
	}
}

void PrintHowtoGo(int start, int end)
{
	char a[128];
	char b[128];
	if (record[end] != start) PrintHowtoGo(start, record[end]);

	for (int j = 0; j < MAX_VETICLES; j++)
	{
		if (record[end] == j)
		{
			strcpy(a, info[j].name);
		}
		if (end == j)
		{
			strcpy(b, info[j].name);
		}

	}
	if (record[end] == start) {
		printf("�ִ� ��� : %s ", a);
		printf("%s ", b);
	}
	else if (record[end] != start) printf("%s ", b);

}

void PrinttheDistance(int start, int end)
{
	if (distance[end] != INF)
	{
		printf("�Ÿ� : %.2fkm", (float)distance[end] / 100);
	}
}
int main(void)
{
	char start[20];
	char end[20];
	ShowStationsByDfs(0);
	printf("\n\n");
	printf("��߿��� �Է��ϼ���. ");
	scanf("%s", start);
	printf("�������� �Է��ϼ���. ");
	scanf("%s", end);
	printf("\n");
	int start_num = FindStationNum(start);
	int end_num = FindStationNum(end);
	CalculateShortestPath(start_num);
	PrintHowtoGo(start_num, end_num);
	printf("\n");
	PrinttheDistance(start_num, end_num);
	printf("\n");

}