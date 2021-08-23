#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>
#define MAX_STACK_SIZE 100


typedef struct Stack {
	char data[MAX_STACK_SIZE];
	int top;
} Stack;

typedef struct BTstack {
	struct TreeNode* BTdata[MAX_STACK_SIZE];
	int top;
} BTstack;

typedef struct TreeNode {
	char data;
	struct TreeNode* left, * right;
} TreeNode;

// ================ FOR STACK ==================

void InitStack(Stack* s)
{
	s->top = -1;
}

int IsEmpty(Stack* s)
{
	return (s->top == -1);
}

int IsFull(Stack* s)
{
	return (s->top == MAX_STACK_SIZE - 1);
}

void Push(Stack* s, char item)
{
	if (IsFull(s))
	{
		printf("FULL!\n");
		return;
	}

	else s->data[++(s->top)] = item;
}

char Pop(Stack* s)
{
	if (IsEmpty(s))
	{
		printf("EMPTY!\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

char Peek(Stack* s)
{
	if (IsEmpty(s)) {
		printf("EMPTY!\n");
		exit(1);
	}
	else return s->data[s->top];
}

// ========================================================
void BinaryTreeStackInit(BTstack* s)
{
	s->top = -1;
}

int BinaryTreeStackIsEmpty(BTstack* s)
{
	return (s->top == -1);
}

int BinaryTreeStackIsFull(BTstack* s)
{
	return (s->top == MAX_STACK_SIZE - 1);
}

void BinaryTreeStackPush(BTstack* s, TreeNode* node)
{
	if (IsFull(s))
	{
		printf("FULL!\n");
		return;
	}

	else s->BTdata[++(s->top)] = node;
}

TreeNode* BinaryTreeStackPop(BTstack* s)
{
	if (IsEmpty(s))
	{
		printf("EMPTY!\n");
		exit(1);
	}
	else return s->BTdata[(s->top)--];
}

// ========================================================
int IsPrec(char o)
{
	if (o == '+' || o == '-') return 1;
	if (o == '*' || o == '/') return 2;
}

char* ChangetoPostfix(char exp[])
{
	char ch;
	int idx = 0;
	int len = strlen(exp);
	char* tmp = (char*)malloc(len + 1);
	memset(tmp, 0, sizeof(char) * len + 1);
	Stack s;
	InitStack(&s);

	for (int i = 0; i < len; i++)
	{
		ch = exp[i];
		switch (ch)
		{
		case '+': case '-': case '*': case '/':
			while (!IsEmpty(&s) && (IsPrec(ch) <= IsPrec(Peek(&s))))
				tmp[idx++] = Pop(&s);
			Push(&s, ch);
			break;
		default:
			tmp[idx++] = ch;
			break;
		}

	}
	while (!IsEmpty(&s)) tmp[idx++] = Pop(&s);

	strcpy(exp, tmp);
	free(tmp);
}

// ==========================================================
void InorderExp(TreeNode* root)
{
	if (root != NULL)
	{
		InorderExp(root->left);
		printf("%c ", root->data);
		InorderExp(root->right);
	}

}

void PreorderExp(TreeNode* root)
{
	if (root != NULL)
	{
		printf("%c ", root->data);
		PreorderExp(root->left);
		PreorderExp(root->right);
	}
}

void PostorderExp(TreeNode* root)
{
	if (root != NULL)
	{
		PostorderExp(root->left);
		PostorderExp(root->right);
		printf("%c ", root->data);
	}
}

// =============================================================

TreeNode* MakeNewNode()
{
	TreeNode* tmp = malloc(sizeof(TreeNode));
	tmp->left = tmp->right = NULL;
	return tmp;
}

void PutData(TreeNode* node, char data)
{
	node->data = data;
}


void MakeLeftSubTree(TreeNode* main, TreeNode* sub)
{
	if (main->left != NULL)
		free(main->left);//������ ����� ��� ����
	main->left = sub;
}

void MakeRightSubTree(TreeNode* main, TreeNode* sub)
{
	if (main->right != NULL)
		free(main->right);
	main->right = sub;
}

TreeNode* MakeExpTree(char exp[])
{
	BTstack stack;
	BinaryTreeStackInit(&stack);
	TreeNode* pnode = NULL;

	int len = strlen(exp);

	for (int i = 0; i < len; i++)
	{
		pnode = MakeNewNode();

		if (exp[i] >= 97 && exp[i] <= 122) //�ǿ�����
		{
			PutData(pnode, exp[i]); //�ǿ����� ������ �ֱ�
		}
		else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') { //������
			MakeRightSubTree(pnode, BinaryTreeStackPop(&stack));
			MakeLeftSubTree(pnode, BinaryTreeStackPop(&stack)); //pop�ؼ� stack���� ������ ������
			PutData(pnode, exp[i]); //�ش� �����ڷ� Ʈ�� ���� ������ stack�� �ֱ�
		}
		BinaryTreeStackPush(&stack, pnode);
		//printf("PUSH %c\n", pnode->data);

	}
	return BinaryTreeStackPop(&stack);

}

int main(void)
{
	char exp[20];
	scanf("%s", exp);
	ChangetoPostfix(exp);

	TreeNode* etree = MakeExpTree(exp);
	printf("���� ��ȸ :");
	PreorderExp(etree);
	printf("\n");
	printf("���� ��ȸ :");
	InorderExp(etree);
	printf("\n");
	printf("���� ��ȸ :");
	PostorderExp(etree);
	printf("\n");




}