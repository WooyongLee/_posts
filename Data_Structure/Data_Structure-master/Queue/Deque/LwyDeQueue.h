#pragma once
#include "LwyQueue.h"
class CLwyDeQueue : public CLwyQueue 
{ // ��������Ƿ� ��������� ���� �ʾƾ� ��
public:
	CLwyDeQueue(void) {  }
	~CLwyDeQueue(void) {  }
	
	void AddRear( int i ) { EnQueue(i); } // ���� �ڿ� �߰��ϴ� �Լ��� ť�� ���Կ���� ����
	void AddFront (int );
	int DelFront() { return DeQueue(); } // ���� �տ� �����ϴ� �Լ��� ť�� ��������� ����
	int DelRear();
	int GetFront() { return Peek(); } // ���� ���� �����ִ� �Լ��� ť�� peek����� ����
	int GetRear();
};
void CLwyDeQueue::AddFront(int i) 
{
	if (IsFull()) {
		printf("���� �������־��\n");
		return;
	}
	m_data[m_front] = i; // �޾ƿ� �����͸� ����
	m_front--;
	if ( m_front < 0 ) m_front = MAXSIZEQUEUE - 1;//m_front = (m_front-1+MAXSIZEQUEUE) %MAXSIZEQUEUE;
}
int CLwyDeQueue::DelRear() 
{
	if ( IsEmpty()) {
		printf("���� ������\n");
		return -1;
	}
	int temp = m_data[m_rear];

	m_rear = (m_rear - 1 + MAXSIZEQUEUE) % MAXSIZEQUEUE;
	return temp;
}
int CLwyDeQueue::GetRear()
{
	int temp = m_data[m_rear];
	return temp;
}
