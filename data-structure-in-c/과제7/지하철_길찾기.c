#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_VETICLES 21
#define INF 1000000 // 무한대, 연결이 없는 경우

typedef struct Subway {
	char name[20]; // 정점 개수
	int distance[MAX_VETICLES];
} Subway;

Subway info[MAX_VETICLES] = {
	{"홍대입구", {0,110,INF,INF,INF,500,INF,INF,INF,INF,INF,INF,INF,80,INF,INF,INF,INF,INF,INF,INF}},
	{"합정", {110,0,50,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,210,INF,INF,INF,INF,INF,INF}},
	{"상수", {INF,50,0,50,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"광흥창",{INF,INF,50,0,80,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"대흥", {INF,INF,INF,80,0,90,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"공덕", {500,INF,INF,INF,90,0,560,INF,460,INF,INF,INF,INF,INF,INF,INF,320,INF,INF,INF,75}},
	{"용산", {INF,INF,INF,INF,INF,560,0,360,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,540,INF}},
	{"남영", {INF,INF,INF,INF,INF,INF,360,0,80,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"서울역", {INF,INF,INF,INF,INF,460,INF,80,0,90,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"시청", {INF,INF,INF,INF,INF,INF,INF,INF,90,0,370,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"충정로", {INF,INF,INF,INF,INF,INF,INF,INF,INF,370,0,75,INF,INF,INF,INF,INF,INF,INF,INF,90}},
	{"아현",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,75,0,80,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"이대",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,80,0,60,INF,INF,INF,INF,INF,INF,INF}},
	{"신촌",{80,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,60,0,INF,INF,INF,INF,INF,INF,INF}},
	{"당산",{INF,210,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,125,INF,INF,INF,INF,INF}},
	{"국회의사당",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,125,0,230,INF,INF,INF,INF}},
	{"여의도",{INF,INF,INF,INF,INF,320,INF,INF,INF,INF,INF,INF,INF,INF,INF,230,0,350,410,INF,INF}},
	{"신길",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,350,0,INF,170,INF}},
	{"샛강",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,410,INF,0,80,INF}},
	{"노량진",{INF,INF,INF,INF,INF,INF,540,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,170,80,0,INF}},
	{"애오개",{INF,INF,INF,INF,INF,75,INF,INF,INF,INF,90,INF,INF,INF,INF,INF,INF,INF,INF,INF,0}}
};


int record[MAX_VETICLES];
int distance[MAX_VETICLES]; // 시작 정점으로부터 최단 경로 거리
int found[MAX_VETICLES]; // 방문한 정점 표시
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
	found[start] = TRUE; //시작 정점 방문 표시//
	distance[start] = 0;
	for (int i = 0; i < MAX_VETICLES - 2; i++)
	{
		int min = FindMin(distance, MAX_VETICLES, found);
		found[min] = TRUE;
		for (int j = 0; j < MAX_VETICLES; j++)
		{
			if (found[j] == FALSE) // 가지 않은 길일 때
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
		printf("최단 경로 : %s ", a);
		printf("%s ", b);
	}
	else if (record[end] != start) printf("%s ", b);

}

void PrinttheDistance(int start, int end)
{
	if (distance[end] != INF)
	{
		printf("거리 : %.2fkm", (float)distance[end] / 100);
	}
}
int main(void)
{
	char start[20];
	char end[20];
	ShowStationsByDfs(0);
	printf("\n\n");
	printf("출발역을 입력하세요. ");
	scanf("%s", start);
	printf("도착역을 입력하세요. ");
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