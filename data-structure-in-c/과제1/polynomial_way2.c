#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101 

 
typedef struct
{
	int coef; //���
	int degree;//���� 
}poly;//���׽��� ��Ÿ���� ���� ����ü


void setData(poly* a, int count) { //������ �Է¹ް� ����ü�� �ʱ�ȭ�ϴ� �Լ�
	int i;
	printf("������ �Է��ϼ���.");
	for (i = 0; i < count; i++) {
		scanf_s("%d", &a[i].coef);
		scanf_s("%d", &a[i].degree);
	}

}

int examineData(poly* a, int count) { //������ 5�� �������� �˻��ϴ� �Լ�
	int i;
	for (i = 0; i < count; i++) {
		if (a[i].degree > 5) {
			printf("������ 5 ���Ϸ� �Է����ּ���.");
			return -1;
		}
	}
}

void multi_poly(poly* c, int count1, poly* d, int count2, poly* result) //���� �Լ�
{//������ 0�� �Ͱ� ������� �ϴ� ������ ��� ���� �޴� ����
	int Rpos = 0;//result ��ġ
	for (int i = 0; i < count1; i++)
	{

		for (int j = 0; j < count2; j++)
		{
			result[Rpos].degree = c[i].degree + d[j].degree;//���׽��� ��-> �������� ���� ������� ����
			result[Rpos].coef = c[i].coef * d[j].coef;
			Rpos++;
		}

	}

	return;
}

void regulation(poly* result, int count) //������ ������ ���� �������� �����ֱ� 
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
	poly temp;//�ӽ� ����ü �ڸ� ����
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			//���� ���Ͽ� i���� j�� ũ�� swap �Լ� �����Ͽ� result ����ü ����
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

void add_poly(poly* c, int count1, poly* d, int count2, poly* result) //���� �Լ�
{
	int Cpos = 0;
	int Dpos = 0;
	int Rpos = 0; //�� ���׽��� ��ġ�� ��Ÿ���� ������ �˻���
	if (c[0].degree > d[0].degree) //�� �� �� �ְ������� ������� �ְ��������� ����
	{
		result[0].degree = c[0].degree;
	}
	else
	{
		result[0].degree = d[0].degree;
	}

	while (Cpos < count1 && Dpos < count2) {
		
		if ((c[Cpos].degree) > (d[Dpos].degree))
		{
			result[Rpos].coef = c[Cpos].coef;
			result[Rpos].degree = c[Cpos].degree;
			Rpos++;
			Cpos++;
		}
		else if ((c[Cpos].degree) == (d[Dpos].degree))
		{
			result[Rpos].degree = c[Cpos].degree;
			result[Rpos].coef = c[Cpos].coef + d[Dpos].coef;
			Rpos++;
			Cpos++;
			Dpos++;
		}
		else if((c[Cpos].degree < d[Dpos].degree))
		{
			result[Rpos].coef = d[Dpos].coef;
			result[Rpos].degree = d[Dpos].degree;
			Rpos++;
			Dpos++;
		}
	}
	return;
}

void getResult(poly* a, int num) //����� ������ 0�� ���� �����ϰ� ������ִ� ����� ��� �Լ�
{
	for (int i = 0; i <= num; i++)
	{
		if (a[i].degree == 0 && a[i].coef == 0) break;
		if (a[i].coef == 0) break;
		printf("%d %d ", a[i].coef, a[i].degree);
	}
	printf("\n");

}

void calculate_sig(poly* a, int input) //���׽Ŀ� �� �Է� �� ���
{
	int num = 0;
	int result = 0;
	int rest = a[0].degree;
	for (int i = 0; i <= a[0].degree; i++)
	{
		num = a[i].coef;
		for (int j = 0; j < a[i].degree; j++)
		{
			num = num * input;
		}
		result += num;
		if (a[i].degree == 0)break;
	}
	//result += a[rest].coef; //����0�� ��� ���ϱ� 
	printf("������� %d\n", result);
}

void main()
{
	/* a,b�� ���׽��� ���� ������ �Է��ϴ� ����
	*c*d*result�� �� ����ü�� �迭�� �������� �����ϱ� ���� �����ͷ� ����
	c�� ù��° ���׽� d�� �ι�° ���׽�
	result�� ��� ���׽�
	*/
	int a, b;
	poly* c;
	poly* d;
	poly* result1; //���� ���
	poly* result2; // ���� ���
	//�Է� �κ����� ����
	printf("���� 1�� �� ���� ������ �����Ǿ� �ֳ���?");
	scanf_s("%d", &a);
	c = (poly*)(malloc((sizeof(poly) * a)));
	setData(c, a);
	int exd1;
	exd1 = examineData(c, a);
	if (exd1 == -1) {
		printf("ERROR!\n");
		exit(-1);
	}

	printf("���� 2�� �� ���� ������ �����Ǿ� �ֳ���?");
	scanf_s("%d", &b);
	d = (poly*)(malloc((sizeof(poly) * b)));
	setData(d, b);
	int exd2;
	exd2 = examineData(c, a);
	if (exd2 == -1) {
		printf("ERROR!\n");
		exit(-1);
	}

	result1 = (poly*)(malloc(sizeof(poly) * MAX_DEGREE));
	result2 = (poly*)(malloc(sizeof(poly) * MAX_DEGREE));
	int MAX;
	if (c[0].degree > d[0].degree) MAX = c[0].degree;
	else MAX = d[0].degree;

	add_poly(c, a, d, b, result1);
	printf("���� 1 + 2��\n");
	getResult(result1, MAX);


	int max1 = c[0].degree + 1;
	int max2 = d[0].degree + 1;
	multi_poly(c, a, d, b, result2);
	regulation(result2, max1 * max2);
	swapMax_Struct(result2, max1 * max2);

	printf("���� 1 * 2��\n");
	getResult(result2, max1 * max2);


	int numsig, numnum;
	poly* uinput;
	uinput = (poly*)(malloc(sizeof(poly) * MAX_DEGREE));
	while (1)
	{
		printf("���Ŀ� ���� ��������");
		scanf_s("%d %d", &numsig, &numnum);
		if (numsig == 1) uinput = c;
		else if (numsig == 2)uinput = d;
		else if (numsig == 3) uinput = result1;
		else if (numsig == 4) uinput = result2;
		calculate_sig(uinput, numnum);

	}



	//�����޸� ����
	free(c);
	free(d);
	free(result2);
	free(result1);

	return;
}
