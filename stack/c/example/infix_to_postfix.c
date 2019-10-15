#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element; 
#define MAX_STACK_SIZE 100

// Statr of stack methods
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// Stack initializing
void init_stack(StackType *s)
{
	s->top = -1;
}

// Stack empty status
int is_empty(StackType *s)
{
	return (s->top == -1);
}
// Stack full status
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// Stack pushing
void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// Stack deleting
element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// Stack top element
element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
//End of stack methods//
 

// Preoritty of operator
int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}
// infix to postfix
void infix_to_postfix(char exp[])
{
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;

	init_stack(&s);					// ���� �ʱ�ȭ 
	for (i = 0; i<len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': // ������
											// ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				printf("%c", pop(&s));
			push(&s, ch);
			break;
		case '(':	// ���� ��ȣ
			push(&s, ch);
			break;
		case ')':	// ������ ��ȣ
			top_op = pop(&s);
			// ���� ��ȣ�� ���������� ���
			while (top_op != '(') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		default:		// �ǿ�����
			printf("%c", ch);
			break;
		}
	}
	while (!is_empty(&s))	// ���ÿ� ����� �����ڵ� ���
		printf("%c", pop(&s));
}

int main(void)
{
	char *s = "(2+3)*4+9";
	printf("Infix %s \n", s);
	printf("Postfix ");
	infix_to_postfix(s);
	printf("\n");
	return 0;
}
