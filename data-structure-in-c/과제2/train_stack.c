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

Train is_empty(Stack* s) { //���� ���� ���� �Լ�
	return (s->top == -1);
}

Train is_full(Stack * s) { //��ȭ ���� ���� �Լ�
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
	int input_train[9]; //�Է¹޴� ���� ��ȣ�� ��� �迭
	int output_train[9]; //������� �׾��� ���� ��ȣ�� ��� �迭
	for (int c = 0; c < 9; c++) { //out train�� �迭 ��� 0���� �ʱ�ȭ 
		output_train[c] = 0;
	}
	Stack s1; //���� ���� 1
	Stack s2; //���� ���� 2

	init(&s1); //�ʱ�ȭ
	init(&s2);

	int i, count = 1; //�� Ƚ�� ���� ���� ���� ���� 
	int push_1 = 0;//���� 1�� �ִ� ���緮
	int push_2 = 0;//���� 1�� �ִ� ���緮 
	int n; //input train ���� ���� 
	int outputnum = 0; //out train�� index ī��Ʈ 

	printf("���� ��ȣ�� �Է��ϼ���."); //���� ��ȣ �Է¹ޱ� 
	for (i = 0; i < 9; i++) {
		scanf_s("%1d", &input_train[i]); //���� �� ���� ���� �Է� ����
	}

	for (i = 0; i < 9; i++) { //���� ���
		n = input_train[i];
		printf("%d : IN(%d)\n", count, n);
		count++;
		if (n == 1) //n�� 1�ϰ�� �ٷ� ��ȯ
		{
			printf("%d : OUT(1)\n", count);
			count++;
			output_train[0] = n;
			
		}
		else if (n - 1 == output_train[outputnum]) {//���ÿ� ���� �ʰ� �ٷ� out�Ǵ� ��� 
			printf("%d : OUT(%d)\n", count, n);
			count++;
			outputnum++;
			output_train[outputnum] = n;
			
		}
		else if (n < 6) { //n�� 6 ������ ��� ���� 1�� push
			Push(&s1, n); //n push
			printf("%d : PUSH(1,%d)\n", count++, n);
			push_1++; //�� ���緮 ++
			
		}
		else if (n>=6)
		{
			Push(&s2, n);
			printf("%d : PUSH(2,%d)\n", count++, n);
			push_2++; //�� ���緮 ++
		
		}
		if (!is_empty(&s1)) { //����1�� ������� ���� ���� 
			if (Peek(&s1) == (output_train[outputnum] + 1)) { //peek s1������ ������ �� ���� ��ȣ�� ���ٸ� pop&out
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
			if (Peek(&s2) == (output_train[outputnum] + 1)) {//peek s2������ ������ �� ���� ��ȣ�� ���ٸ� pop&out
				output_train[outputnum + 1] = Peek(&s2);
				outputnum++;
				Pop(&s2);
				printf("%d : POP(2)\n", count);
				count++;
				printf("%d : OUT(%d)\n", count, output_train[outputnum]);
			}
		}


	}
	//���� �Է��� ��� ���� �� ���ÿ� ���� ���� pop ���ֱ� 


	int peeknum;

	while (outputnum < 8) { //output_train�� ��� ������ �ƿ��� �� ���� 
		while (!is_empty(&s1)) {// ���� s1�� ��� �����͸� Ȯ���Ͽ� out�ž� �� ������ �ִ��� Ȯ�� 
			if (outputnum == 8) 
				break;
			peeknum = Peek(&s1);
			if (peeknum == (output_train[outputnum] + 1)) //s1 peek���� ������ �� ���� ��ȣ�� ������ pop&out
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
			else //�ٸ� ��� ���� s2�� push 
			{
				Push(&s2, peeknum);
				Pop(&s1);
				printf("%d : POP(1)\n", count);
				count++;
				printf("%d : PUSH(2,%d)\n", count, peeknum);
				count++;

			}
		}
		while (!is_empty(&s2)) {//���� s2�� ��� ���� Ȯ���Ͽ� ������ �� ������ �ִ��� Ȯ�� 
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

	printf("����. �� %dȸ\n", (count-1));
	printf("�ִ� ���緮 : 1�� %d��, 2�� %d��", push_1, push_2);
	

}

	
