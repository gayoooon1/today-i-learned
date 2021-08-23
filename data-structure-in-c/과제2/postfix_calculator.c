#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#define FALSE 0
#define STACK_LEN 100
typedef int Data;
typedef struct _arrayStack
{
	Data stackArr[STACK_LEN];
	int topIndex;
}ArrayStack;

typedef ArrayStack Stack;

void StackInit(Stack* pstack)
{
	pstack->topIndex = -1; //������ �ʱ�ȭ 
}

int isEmpty(Stack* pstack)
{
	if (pstack->topIndex == -1)
		return TRUE;
	else
		return FALSE;
}

void Push(Stack* pstack, Data data)
{
	pstack->topIndex += 1; //�������߰��� ���� �ε����� ����
	pstack->stackArr[pstack->topIndex] = data; //������ ����
}

Data Pop(Stack* pstack)
{
	int rIdx;

	if (isEmpty(pstack)) {
		printf("Stack Memory Error!");
		exit(-1);
	}
	rIdx = pstack->topIndex; //������ �����Ͱ� ����� �ε����� ����
	pstack->topIndex -= 1; //�˿����� ����� ž�ε��� �� �ϳ� ����

	return pstack->stackArr[rIdx];
}

Data Peek(Stack* pstack)
{
	if (isEmpty(pstack))
	{
		printf("Stack Memory Error");
		exit(-1);
	}
	return pstack->stackArr[pstack->topIndex]; //�� ���� ����� ������ ��ȯ
}

int getPriority(char operator) //�������� �켱������ ��ȯ
{
	switch (operator)
	{
	case '^':
		return 4;
	case '*':
		return 3;
	case '+':
	case '-':
		return 2;
	case '(':
		return 1; //(�������� ��� ')'�� �� �� ���� ����ؾ� �ϹǷ� �켱������ ���� ������,���� ���� ���� �Է� 

	}
}


char* change2Post(char uinput[]) //����->���� ��ȯ �Լ� 
{
	Stack stack;


	int length = strlen(uinput);
	int my_len = length;
	char* resultValue = (char*)malloc(length + 1);
	memset(resultValue, '\0', sizeof(char) * length + 1);

	char s; //���� ����� �迭�� �ȴ� char�� ����
	char popOper;//stack���� pop �� ������ �޴� ���� 
	int  i, count = 0;

	StackInit(&stack);
	for (i = 0; i < length; i++)
	{
		s = uinput[i];
		if (isdigit(s)) {
				resultValue[count++] = s;
		}
		else
		{
			switch (s) //�������� ���
			{
			case'(': //���� ��ȣ�� ��� �ٷ� �������� push�Ѵ� 
				Push(&stack, s);
				break;
			case ')': //�ݴ� ��ȣ�� ���, ���� ��ȣ�� ���� �� ���� ���ÿ� �ִ� ���� pop�Ѵ�. 
				while (1)
				{
					popOper = Pop(&stack);
					if (popOper == '(')
						break;
					resultValue[count++] = popOper;
				}
				break;
			case'+':
			case'-':
			case'*':
			case '^': //���ÿ� �ִ� �������� �켱������ ���� ���� �������� �켱���� ���� ���ų� Ŭ ��
				while (!isEmpty(&stack) && getPriority(Peek(&stack)) >= getPriority(s))
				{//���ÿ� ����� �����ڰ� pop�ȴ�. 
					resultValue[count++] = Pop(&stack);
				}
				Push(&stack, s); //���� ���� �����ڸ� ���ÿ� push�Ѵ�. 
				if (!isEmpty(&stack) && getPriority(Peek(&stack)) < getPriority(s))
				{
					Push(&stack, s); //���� ���� �������� �켱������ �� ũ�� ���ÿ� push�Ѵ�. 
				}
				break;
			}
		}


	}
	while (!isEmpty(&stack))
	{
		resultValue[count++] = Pop(&stack);
		if (count == my_len) break;
	}
	return resultValue;

}

int testNum(char* uinput) //���� ã�� ��Ÿ���� 
{
	int i;
	for (i = 0; i < strlen(uinput); i++)
	{
		//���� ó���� �����ڰ� ������ ���, �����ڰ� ���޾Ƽ� ������ ���
		if ((uinput[0] == '+' || uinput[0] == '-' || uinput[0] == '*' || uinput[0] == '^') || ((uinput[i] == '+' || uinput[i] == '-' || uinput[i] == '*' || uinput[i] == '^') && (uinput[i + 1] == '+' || uinput[i + 1] == '-' || uinput[i + 1] == '*' || uinput[i + 1] == '^')))
		{	
			printf("%c", uinput[i]);
			printf("(!) �� �κп� ������ �ֽ��ϴ�. ���ڰ� �;��մϴ�.");
			exit(1);
		}
	}


}
int testPair(char* uinput) {//��ȣ �˻�
	int b;
	Stack stack;
	StackInit(&stack);
	for (int i = 0; i < strlen(uinput); i++) {
		switch (uinput[i]) {
		case '(':
			Push(&stack, uinput[i]);
			break;
		case ')':

			b = isEmpty(&stack);
			if (b == 1) printf("ERROR!\n");
			else Pop(&stack);
			break;
		}
	}

	int a = isEmpty(&stack);
	if (a == 0) {
		printf("(!) �� �κп� ������ �ֽ��ϴ�. ')'�� �;��մϴ�.");
		exit(1);
	}
}

int calculate(char result[])
{
	Stack stack; //���� ����
	int length = strlen(result);
	int i, a, b, j;
	char s, o1, o2;

	StackInit(&stack); //���� �ʱ�ȭ

	for (i = 0; i < length; i++)
	{
		if (isEmpty == 1) break;
		s = result[i];
		if (isdigit(s)) //�������� Ȯ��
		{
			Push(&stack, s - '0');//���ÿ� �־��ֱ� 
		}
		else
		{
			o2 = Pop(&stack);
			o1 = Pop(&stack);
			switch (s)
			{
			case'+':
				Push(&stack, o1 + o2); //����� ���ÿ� �ٽó־��ֱ� 
				break;
			case'-':
				Push(&stack, o1 - o2);
				break;
			case'*':
				Push(&stack, o1 * o2);
				break;
			case'^':
				a = o1;
				b = o2;
				for (j = 1; j < b; j++)
				{
					a = a * o1;
				}
				Push(&stack, a);
				break;
			}

		}

	}
	return Pop(&stack); //���� �������� ���� ���ڰ� ���.


}

int main(void) {
	printf("������ �Է��ϼ���."); //�ӽÿ�
	char* exp;
	char* str;
	char** str1 = NULL;
	char express[100];
	char rexpress[100];
	gets_s(express, 100);
	int a = testNum(express);
	int b = testPair(express);
	exp = change2Post(express);
	int last_result = calculate(exp);
	printf("= %d", last_result);



}
