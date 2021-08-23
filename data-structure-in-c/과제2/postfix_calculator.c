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
	pstack->topIndex = -1; //스택의 초기화 
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
	pstack->topIndex += 1; //데이터추가를 위한 인덱스값 증가
	pstack->stackArr[pstack->topIndex] = data; //데이터 저장
}

Data Pop(Stack* pstack)
{
	int rIdx;

	if (isEmpty(pstack)) {
		printf("Stack Memory Error!");
		exit(-1);
	}
	rIdx = pstack->topIndex; //삭제할 데이터가 저장된 인덱스값 저장
	pstack->topIndex -= 1; //팝연산의 결과로 탑인덱스 값 하나 감소

	return pstack->stackArr[rIdx];
}

Data Peek(Stack* pstack)
{
	if (isEmpty(pstack))
	{
		printf("Stack Memory Error");
		exit(-1);
	}
	return pstack->stackArr[pstack->topIndex]; //맨 위에 저장된 데이터 반환
}

int getPriority(char operator) //연산자의 우선순위를 반환
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
		return 1; //(연산자의 경우 ')'가 올 때 까지 대기해야 하므로 우선순위는 가장 높지만,가장 낮은 순위 입력 

	}
}


char* change2Post(char uinput[]) //중위->후위 변환 함수 
{
	Stack stack;


	int length = strlen(uinput);
	int my_len = length;
	char* resultValue = (char*)malloc(length + 1);
	memset(resultValue, '\0', sizeof(char) * length + 1);

	char s; //중위 연산식 배열을 훑는 char형 변수
	char popOper;//stack에서 pop 된 연산자 받는 변수 
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
			switch (s) //연산자일 경우
			{
			case'(': //여는 괄호일 경우 바로 스택으로 push한다 
				Push(&stack, s);
				break;
			case ')': //닫는 괄호일 경우, 여는 괄호가 나올 때 까지 스택에 있는 값을 pop한다. 
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
			case '^': //스택에 있는 연산자의 우선순위가 새로 들어온 연산자의 우선순위 보다 같거나 클 때
				while (!isEmpty(&stack) && getPriority(Peek(&stack)) >= getPriority(s))
				{//스택에 저장된 연산자가 pop된다. 
					resultValue[count++] = Pop(&stack);
				}
				Push(&stack, s); //새로 들어온 연산자를 스택에 push한다. 
				if (!isEmpty(&stack) && getPriority(Peek(&stack)) < getPriority(s))
				{
					Push(&stack, s); //새로 들어온 연산자의 우선순위가 더 크면 스택에 push한다. 
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

int testNum(char* uinput) //오류 찾고 나타내기 
{
	int i;
	for (i = 0; i < strlen(uinput); i++)
	{
		//식의 처음에 연산자가 나오는 경우, 연산자가 연달아서 나오는 경우
		if ((uinput[0] == '+' || uinput[0] == '-' || uinput[0] == '*' || uinput[0] == '^') || ((uinput[i] == '+' || uinput[i] == '-' || uinput[i] == '*' || uinput[i] == '^') && (uinput[i + 1] == '+' || uinput[i + 1] == '-' || uinput[i + 1] == '*' || uinput[i + 1] == '^')))
		{	
			printf("%c", uinput[i]);
			printf("(!) 이 부분에 문제가 있습니다. 숫자가 와야합니다.");
			exit(1);
		}
	}


}
int testPair(char* uinput) {//괄호 검사
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
		printf("(!) 이 부분에 문제가 있습니다. ')'가 와야합니다.");
		exit(1);
	}
}

int calculate(char result[])
{
	Stack stack; //스택 선언
	int length = strlen(result);
	int i, a, b, j;
	char s, o1, o2;

	StackInit(&stack); //스택 초기화

	for (i = 0; i < length; i++)
	{
		if (isEmpty == 1) break;
		s = result[i];
		if (isdigit(s)) //정수인지 확인
		{
			Push(&stack, s - '0');//스택에 넣어주기 
		}
		else
		{
			o2 = Pop(&stack);
			o1 = Pop(&stack);
			switch (s)
			{
			case'+':
				Push(&stack, o1 + o2); //계산결과 스택에 다시넣어주기 
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
	return Pop(&stack); //가장 마지막에 남은 숫자가 결과.


}

int main(void) {
	printf("계산식을 입력하세요."); //임시용
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
