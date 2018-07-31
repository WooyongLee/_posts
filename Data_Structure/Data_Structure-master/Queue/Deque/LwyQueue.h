#pragma once
#include <stdio.h>
#define MAXSIZEQUEUE 10 // �ִ� ť�� ũ�� ����
class CLwyQueue
{
protected :
	int m_front; // ���� �ֱٿ� ������ ��ġ
	int m_rear; //���� �ֱٿ� ���Ե� ��ġ
	int m_data[MAXSIZEQUEUE];
public :
	CLwyQueue(void) { m_front = m_rear = 0; } // ���� ť �����
	~CLwyQueue(void) { 	}

	bool IsEmpty() { return m_front == m_rear; } // ť�� ó���� ���� ���� ���� ����
	bool IsFull() { return m_front == (m_rear + 1) % MAXSIZEQUEUE; }
	
	void EnQueue(int ); // ť �����Լ�
	int DeQueue(); // ť �����Լ�
	int Peek(); // ������ ���⸸ �ϴ� �Լ�
	void Display(); // ����Լ�
};
void CLwyQueue::EnQueue(int i)
{
	if(IsFull()) { // ����ó��, ť�� �� ������ ��� ���� �Ұ�
		printf("ť�� ���� �� �ֽ��ϴ�.\n"); 
		return;
	}
	m_rear++; //ť�� rear�� �ϳ� �������� �ݴϴ�.
	m_rear = m_rear % MAXSIZEQUEUE; // ť�� ������� ������ �Ѿ�� �ʵ��� ������
	// ���� m_rear�� ť�� �ִ�ġ�� �Ѿ ��� �ٽ� ť�� ù �������� �Ҵ��մϴ�.
	m_data[m_rear] = i; // ť�� ���ڸ� �ֽ��ϴ�.
}
int CLwyQueue::DeQueue()
{
	if(IsEmpty()){ // ����ó��, ť�� ��� ���� ��� ���� �Ұ�
		printf("ť�� ��� �ֽ��ϴ�.\n");
		return -1;
	}
	m_front++; // ť�� front�� �ϳ� �������� �ݴϴ�.
	m_front = m_front % MAXSIZEQUEUE;
	return m_data[m_front]; // ť�� ���ΰ��� ��ȯ�� �ݴϴ�.
}

int CLwyQueue::Peek()
{
	if(IsEmpty()){
		printf("ť�� ��� �ֽ��ϴ�.\n");
		return -1;
	}
	return m_data[(m_front+1) % MAXSIZEQUEUE];
}
void CLwyQueue::Display()
{
	if(!IsEmpty()){
		int from = m_front + 1;
		int to = m_rear;

		if ( from > to) to += MAXSIZEQUEUE;

		for( ; from <= to ; from++){
			printf("%3d ", m_data[from % MAXSIZEQUEUE] );
		}
	}
	printf("\n");
}
