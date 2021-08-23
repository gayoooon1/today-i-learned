#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101 

//다항식을 나타내기 위한 구조체 
typedef struct
{
	int coef; //계수
	int degree;//차수 
}poly;

void sayData(poly* a, int count) { //수식을 입력받는 함수
	int i;
	printf("수식을 입력하세요.");
	for (i = 0; i < count; i++) {
		scanf_s("%d", &a[i].coef);
		scanf_s("%d", &a[i].degree);
	}

}

int examineData(poly* a, int count) { //수식이 5차 이하인지 검사하는 함수
	int i;
	for (i = 0; i < count; i++) {
		if (a[i].degree > 5) {
			printf("차수는 5 이하로 입력해주세요.");
			return -1;
		}
	}
}

void setData(poly* a, poly* a1) { //입력받은 수식을 방법 1로 바꿔주는 함수
	int i = 0;
	int x;
	int j = a[0].degree;
	int index = (a[0].degree) + 1;
	int Pos = 0;
	while (j != -1)
	{
		a1[i].degree = j;
		j--;
		i++;
	}

	for (x = 0; x < index; x++)
	{
		if (a1[x].degree == a[Pos].degree) {
			a1[x].coef = a[Pos].coef;
			Pos++;
		}
		else {
			a1[x].coef = 0;
		}
	}

	return;

}

void multi_poly(poly* c, poly* d, poly* result) //곱셈 함수
{//차수가 0인 것과 상관없이 일단 차수와 계수 값을 받는 것임
	int Rpos = 0;//result 위치
	for (int i = 0; i < c[0].degree + 1; i++)
	{

		for (int j = 0; j < d[0].degree + 1; j++)
		{
			result[Rpos].degree = c[i].degree + d[j].degree;//다항식의 곱-> 지수끼리 덧셈 계수끼리 곱셈
			result[Rpos].coef = c[i].coef * d[j].coef;
			Rpos++;
		}

	}

	return;
}

void regulation(poly* result, int count) //곱셈시 차수가 같은 지수끼리 묶어주기 
{
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (result[i].degree == result[j].degree)
			{
				result[i].coef += result[j].coef;
				result[j].coef = 0;
				result[j].degree = 0;
			}
		}
	}
	return;
}

void swapMax_Struct(poly* a, int count)
{
	poly temp;//임시 구조체 자리 변수
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			//차수 비교하여 i보다 j가 크면 swap 함수 응용하여 result 구조체 변경
			if (a[i].degree < a[j].degree)
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}

		}
	}
	return;
}

void add_poly(poly* c, poly* d, poly* result) //덧셈 함수
{
	int Cpos = 0, Dpos = 0, Rpos = 0; //각 다항식의 위치변수
	int c_degree = c[0].degree, d_degree = d[0].degree; //각 식의 최고차항 

	int big;
	if (c_degree > d_degree) big = c_degree;
	else big = d_degree;
	result[0].degree = big; //두 식의 최고차항 중 더 큰 차수가 결과값의 최고 차수
	int num = big;

	for (int x = 0; x <= big; x++)
	{
		result[x].degree = num;
		num--;
	}

	while (Cpos <= c[0].degree && Dpos <= d[0].degree)
	{
		if (c_degree > d_degree) //식 1의 차수가 더 클 때
		{
			result[Rpos++].coef = c[Cpos++].coef;
			c_degree--;


		}
		else if (c_degree == d_degree) //차수가 같을 때
		{
			result[Rpos++].coef = c[Cpos++].coef + d[Dpos++].coef;
			d_degree--;
			c_degree--;

		}
		else
		{
			result[Rpos++].coef = d[Dpos++].coef;
			printf("%d", d_degree);
			printf("%d", result[Rpos].coef);

			d_degree--;

		}
	}
	return;
}

void getResult(poly* a, int num) //계수나 차수가 0인 항을 제외하고 출력해주는 결과값 출력 함수
{
	for (int i = 0; i <= num; i++)
	{
		if (a[i].degree == 0 && a[i].coef == 0) break;
		if (a[i].coef == 0) break;
		printf("%d %d ", a[i].coef, a[i].degree);
	}
	printf("\n");

}

void calculate_sig(poly* a, int input) //다항식에 값 입력 후 계산
{
	int num = 0;
	int result = 0;
	int rest = a[0].degree;
	for (int i = 0; i < a[0].degree; i++)
	{
		num = a[i].coef;
		for (int j = 0; j < a[i].degree; j++)
		{
			num = num * input;
		}
		result += num;
	}
	result += a[rest].coef; //차수0의 계수 더하기 
	printf("결과값은 %d\n", result);
}

void main()
{
	/* a,b는 다항식의 항의 개수를 입력하는 변수
	*c*d*result는 각 구조체의 배열을 동적으로 전달하기 위해 포인터로 설정
	c는 첫번째 다항식 d는 두번째 다항식
	result는 결과 다항식
	*/
	int a, b;
	poly* c;
	poly* c1;
	poly* d;
	poly* d1;
	poly* result1; //덧셈 결과
	poly* result2; // 곱셈 결과
	//입력 부분항의 개수
	printf("수식 1은 몇 개의 항으로 구성되어 있나요?");
	scanf_s("%d", &a);
	c = (poly*)(malloc((sizeof(poly) * a)));
	c1 = (poly*)(malloc)(sizeof(poly) * (a * 2));
	sayData(c, a);
	int exd1;
	exd1 = examineData(c, a);
	if (exd1 == -1) {
		printf("ERROR!\n");
		exit(-1);
	}
	setData(c, c1);

	printf("수식 2는 몇 개의 항으로 구성되어 있나요?");
	scanf_s("%d", &b);
	d = (poly*)(malloc((sizeof(poly) * b)));
	d1 = (poly*)(malloc)(sizeof(poly) * (a * 2));
	sayData(d, b);
	int exd2;
	exd2 = examineData(d, b);
	if (exd2 == -1) {
		printf("ERROR!\n");
		exit(-1);
	}
	setData(d, d1);


	result1 = (poly*)(malloc(sizeof(poly) * MAX_DEGREE));
	result2 = (poly*)(malloc(sizeof(poly) * MAX_DEGREE));
	int MAX;
	if (c[0].degree > d[0].degree) MAX = c[0].degree;
	else MAX = d[0].degree;

	add_poly(c1, d1, result1);
	printf("수식 1 + 2는\n");
	getResult(result1, MAX);


	int max1 = c1[0].degree + 1;
	int max2 = d1[0].degree + 1;
	multi_poly(c1, d1, result2);
	regulation(result2, max1 * max2);
	swapMax_Struct(result2, max1 * max2);

	printf("수식 1 * 2는\n");
	getResult(result2, max1 * max2);


	int numsig, numnum;
	poly* uinput;
	uinput = (poly*)(malloc(sizeof(poly) * MAX_DEGREE));
	while (1)
	{
		printf("수식에 값을 넣으세요");
		scanf_s("%d %d", &numsig, &numnum);
		if (numsig == 1) uinput = c1;
		else if (numsig == 2)uinput = d1;
		else if (numsig == 3) uinput = result1;
		else if (numsig == 4) uinput = result2;
		calculate_sig(uinput, numnum);

	}



	//동적메모리 해제
	free(c);
	free(d);
	free(result2);
	free(result1);

	return;
}

