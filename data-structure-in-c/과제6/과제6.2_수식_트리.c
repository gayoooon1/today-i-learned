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
		free(main->left);//기존에 연결된 노드 삭제
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

		if (exp[i] >= 97 && exp[i] <= 122) //피연산자
		{
			PutData(pnode, exp[i]); //피연산자 데이터 넣기
		}
		else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') { //연산자
			MakeRightSubTree(pnode, BinaryTreeStackPop(&stack));
			MakeLeftSubTree(pnode, BinaryTreeStackPop(&stack)); //pop해서 stack에서 연산자 꺼내기
			PutData(pnode, exp[i]); //해당 연산자로 트리 만든 다음에 stack에 넣기
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
	printf("전위 순회 :");
	PreorderExp(etree);
	printf("\n");
	printf("중위 순회 :");
	InorderExp(etree);
	printf("\n");
	printf("후위 순회 :");
	PostorderExp(etree);
	printf("\n");




}