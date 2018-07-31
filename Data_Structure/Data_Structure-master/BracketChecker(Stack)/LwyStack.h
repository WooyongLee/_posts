#pragma once
#include <stdio.h>
#include <stdlib.h>
const int MAX_STACK_SIZE = 100; // ������ �ִ� Size�� 100���� 
class CLwyStack
{
	char m_data[MAX_STACK_SIZE]; // ����� �迭
	int m_top;
public:
	CLwyStack(void) : m_top(0) {  } // �⺻ ������
	~CLwyStack(void)  {  Reset(); }// ���ÿ� �ƹ��͵� ���ٴ� ��, �ʱ�ȭ
	bool IsEmpty() { return m_top == 0; } // ������ 0
	bool IsFull() { return m_top == MAX_STACK_SIZE; } // ������ full�� ��� 
	void Push( char ); // ���ÿ� ���� push��
	char Pop(); // ���ÿ� ���� pop��
	char Peek(); // ������ �� ���� �ִ� ���� ��ȯ��
	void Display(); // ���� ������ ��Ȳ�� ���
	void Reset(); // ������ �ʱ�ȭ
};

void CLwyStack::Push(char e)
{
	if (IsFull()) {// ������ full���� �ƴ����� �ϴ� �˻�
		printf("Error : ������ FULL \n"); // full�� ��� ���� �� �������� ����
		return;
	}
	m_top += 1; // ������ top�� ��ġ�� �ٲ�,+1 ���ݴϴ�.
	m_data[m_top] = e; // ������ ������ ���Ӱ� �Ҵ��� �迭��ҿ� �ϳ� �� �޽��ϴ�.
}

char CLwyStack::Pop()
{
	if ( IsEmpty() ) { // ������ ������� �ƴ��� �ϴ� �˻�
		printf("Error : ���ð���\n"); // ������ ��� ���� �� ���� �����
		return 0;
	}
	// ������ top�� ��ġ�� �ٲ�, -1 ���ݽô�.
	return m_data[m_top--]; // ���� ���ÿ� �ִ� �����͸� ��ȯ�մϴ�
}

char CLwyStack::Peek()
{
	if (IsEmpty() ) { //������ ����⸦ �Ǻ��Ϸ��� ������ ��������� �ȵ���
		printf("Error :���ð���\n"); 
		return 0;
	}
	return m_data[m_top - 1]; // ������ �� ���� �ڷḸ ��ȯ�ϰ� �ƹ� �������� �ʽ��ϴ�.
}

void CLwyStack::Display() 
{
	for ( int i = 0 ; i < m_top ; i++ ) // ������ �� ���ڵ��� �ؿ������� �ݺ��ϸ鼭 ���ʴ�� �� ����غ��ϴ�.
		printf("< %c > ", m_data[m_top]);
}
void CLwyStack::Reset()
{
	m_top = 0; // top�� 0���� �־� ������ ���ϴ�.
}