#pragma once
#include <stdio.h>
#define MAXSIZEDEQUE 10 // �ִ� ť�� ũ�� ����
class CLwyDeque
{
private :
	int m_front; // ���� �ֱٿ� ������ ��ġ
	int m_rear; //���� �ֱٿ� ���Ե� ��ġ
	int m_data[MAXSIZEDEQUE];
public :
	CLwyDeque(void) { m_front = m_rear = 0; } // ���� ť �����
	~CLwyDeque(void) { 	}

	bool IsEmpty() { return m_front == m_rear; } // ť�� ó���� ���� ���� ���� ����
	bool IsFull() { return m_front == (m_rear + 1) % MAXSIZEDEQUE; }

	void AddRear(int ); // �� ���� �����Լ�
	void AddFront(int ); // �� ���� �����Լ�
	int DelFront(); // �� ���� �����Լ�
	int DelRear(); // �� ���� �����Լ�
	int GetFront();	 // �� ���� �����ִ� �Լ�
	int GetRear(); // �� ���� �����ִ� �Լ�
	void Display(); // ����Լ�
};
void CLwyDeque::AddRear(int i)
{
	if(IsFull()) { // ���� Ǯ�ϋ� ���� �Ұ�
		printf("���� ���� �� �ֽ��ϴ�.\n"); 
		return;
	}
	m_rear++; //���� rear�� �ϳ� �������� �ݴϴ�.
	m_rear = m_rear % MAXSIZEDEQUE; // ���� ������� ������ �Ѿ�� �ʵ��� ������
	// ���� m_rear�� ���� �ִ�ġ�� �Ѿ ��� �ٽ� ���� ù �������� �Ҵ��մϴ�. - ���󿬻�
	m_data[m_rear] = i; // ���� ���ڸ� �ֽ��ϴ�.
}
void CLwyDeque::AddFront(int i)
{
	if (IsFull()) { // ���� Ǯ�ϋ� ���� �Ұ�
		printf("���� ���� �� �ֽ��ϴ�.\n"); 
		return;
	}
	m_data[m_front] = i;	
	m_front--;
	if ( m_front < 0 ) m_front = MAXSIZEDEQUE - 1; // m_front = (m_front-1+MAXQUEUESIZE) %MAXQUEUESIZE;
} // m_front�� 0���� �۾����� �ִ�ũ�⿡ 1�� ���� �迭�� ���� ������ ä��
int CLwyDeque::DelFront()
{
	if(IsEmpty()){ // ���� ��� ���� ��� ���� �Ұ�
		printf("���� ��� �ֽ��ϴ�.\n");
		return -1;
	}
	m_front++; // ���� front�� �ϳ� �������� �ݴϴ�.
	m_front = m_front % MAXSIZEDEQUE;
	return m_data[m_front]; // ���� ���ΰ��� ��ȯ�� �ݴϴ�.
}
int CLwyDeque::DelRear()
{
	if(IsEmpty()){ // ���� ��� ���� ��� ���� �Ұ�
		printf("���� ��� �ֽ��ϴ�.\n");
		return -1;
	}
	int temp = m_data[m_rear];
	m_rear = (m_rear - 1 + MAXSIZEDEQUE) % MAXSIZEDEQUE;
	return temp;
}
int CLwyDeque::GetFront()
{
	if(IsEmpty()){ // ����˻�
		printf("���� ��� �ֽ��ϴ�.\n");
		return -1;
	}
	return m_data[(m_rear) % MAXSIZEDEQUE];
}
int CLwyDeque::GetRear()
{	
	if(IsEmpty()){ // ����˻�
		printf("���� ��� �ֽ��ϴ�.\n");
		return -1;
	}
	return m_data[(m_front + 1) % MAXSIZEDEQUE];
}
void CLwyDeque::Display()
{
	if(!IsEmpty()){
		int from = m_front + 1;
		int to = m_rear;

		if ( from > to) to += MAXSIZEDEQUE;

		for( ; from <= to ; from++){
			printf("%3d ", m_data[from % MAXSIZEDEQUE] );
		}
	}
	printf("\n");
}
