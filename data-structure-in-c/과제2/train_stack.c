#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int Train;
typedef struct {
	Train stack[10];
	int top;
} Stack;

void init(Stack* s) {
	s->top = -1;
}

Train is_empty(Stack* s) { //공백 상태 검출 함수
	return (s->top == -1);
}

Train is_full(Stack * s) { //포화 상태 검출 함수
	return (s->top == 9);
}

void Push(Stack * s, Train num) {
	if (is_full(s)) {
		printf("STACK ERROR!(full)\n");
		return;
	}
	else {
		s->top += 1;
		s->stack[s->top] = num;
	}
}

Train Pop(Stack * s) {
	if (is_empty(s)) {
		printf("STACK ERROR!(empty pop)\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}

Train Peek(Stack * s) {
	//if (is_empty(s)) {
		//printf("STACK ERROR!(empty peek)\n");
		//exit(0);
	//}
	//else 
	return s->stack[s->top];
}









int main(void) {
	int input_train[9]; //입력받는 열차 번호를 담는 배열
	int output_train[9]; //순서대로 쌓아진 열차 번호를 담는 배열
	for (int c = 0; c < 9; c++) { //out train의 배열 모두 0으로 초기화 
		output_train[c] = 0;
	}
	Stack s1; //열차 스택 1
	Stack s2; //열차 스택 2

	init(&s1); //초기화
	init(&s2);

	int i, count = 1; //총 횟수 세기 위한 정수 변수 
	int push_1 = 0;//스택 1의 최대 적재량
	int push_2 = 0;//스택 1의 최대 적재량 
	int n; //input train 받을 변수 
	int outputnum = 0; //out train의 index 카운트 

	printf("열차 번호를 입력하세요."); //열차 번호 입력받기 
	for (i = 0; i < 9; i++) {
		scanf_s("%1d", &input_train[i]); //숫자 간 띄어쓰기 없이 입력 가능
	}

	for (i = 0; i < 9; i++) { //열차 출발
		n = input_train[i];
		printf("%d : IN(%d)\n", count, n);
		count++;
		if (n == 1) //n이 1일경우 바로 반환
		{
			printf("%d : OUT(1)\n", count);
			count++;
			output_train[0] = n;
			
		}
		else if (n - 1 == output_train[outputnum]) {//스택에 들어가지 않고 바로 out되는 경우 
			printf("%d : OUT(%d)\n", count, n);
			count++;
			outputnum++;
			output_train[outputnum] = n;
			
		}
		else if (n < 6) { //n이 6 이하일 경우 스택 1에 push
			Push(&s1, n); //n push
			printf("%d : PUSH(1,%d)\n", count++, n);
			push_1++; //총 적재량 ++
			
		}
		else if (n>=6)
		{
			Push(&s2, n);
			printf("%d : PUSH(2,%d)\n", count++, n);
			push_2++; //총 적재량 ++
		
		}
		if (!is_empty(&s1)) { //스택1일 비어있지 않을 동안 
			if (Peek(&s1) == (output_train[outputnum] + 1)) { //peek s1스택이 다음에 올 열차 번호와 같다면 pop&out
				output_train[outputnum + 1] = Peek(&s1);
				outputnum++;
				Pop(&s1);
				printf("%d : POP(1)\n", count);
				count++;
				printf("%d : OUT(%d)\n", count, output_train[outputnum]);
			}
		}
		if (!is_empty(&s2))
		{
			if (Peek(&s2) == (output_train[outputnum] + 1)) {//peek s2스택이 다음에 올 열차 번호와 같다면 pop&out
				output_train[outputnum + 1] = Peek(&s2);
				outputnum++;
				Pop(&s2);
				printf("%d : POP(2)\n", count);
				count++;
				printf("%d : OUT(%d)\n", count, output_train[outputnum]);
			}
		}


	}
	//열차 입력이 모두 끝난 후 스택에 남은 열차 pop 해주기 


	int peeknum;

	while (outputnum < 8) { //output_train에 모든 열차가 아웃될 때 까지 
		while (!is_empty(&s1)) {// 스택 s1의 모든 데이터를 확인하여 out돼야 할 열차가 있는지 확인 
			if (outputnum == 8) 
				break;
			peeknum = Peek(&s1);
			if (peeknum == (output_train[outputnum] + 1)) //s1 peek값이 다음에 올 열차 번호와 같으면 pop&out
			{
				output_train[outputnum + 1] = peeknum;
				outputnum++;
				Pop(&s1);
				printf("%d : POP(1)\n", count);
				count++;
				printf("%d : OUT(%d)\n", count, output_train[outputnum]);
				count++;
				if (outputnum == 8) 
					break;

			}
			else //다를 경우 스택 s2로 push 
			{
				Push(&s2, peeknum);
				Pop(&s1);
				printf("%d : POP(1)\n", count);
				count++;
				printf("%d : PUSH(2,%d)\n", count, peeknum);
				count++;

			}
		}
		while (!is_empty(&s2)) {//스택 s2의 모든 값을 확인하여 다음에 올 열차가 있는지 확인 
			if (outputnum == 8)
				break;
			peeknum = Peek(&s2);
			if (peeknum == (output_train[outputnum] + 1))
			{
				output_train[outputnum + 1] = peeknum;
				outputnum++;
				Pop(&s2);
				printf("%d : POP(2)\n", count);
				count++;
				printf("%d : OUT(%d)\n", count, output_train[outputnum]);
				count++;
				if (outputnum == 8) 
					break;
			}
			else
			{
				Push(&s1, peeknum);
				Pop(&s2);
				printf("%d : POP(2)\n", count);
				count++;
				printf("%d : PUSH(1,%d)\n", count, peeknum);
				count++;

			}
		}
	}

	printf("종료. 총 %d회\n", (count-1));
	printf("최대 적재량 : 1번 %d대, 2번 %d대", push_1, push_2);
	

}

	
