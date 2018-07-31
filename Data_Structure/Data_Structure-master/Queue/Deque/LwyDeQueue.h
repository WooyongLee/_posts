#pragma once
#include "LwyQueue.h"
class CLwyDeQueue : public CLwyQueue 
{ // 상속했으므로 멤버변수를 넣지 않아야 함
public:
	CLwyDeQueue(void) {  }
	~CLwyDeQueue(void) {  }
	
	void AddRear( int i ) { EnQueue(i); } // 덱의 뒤에 추가하는 함수는 큐의 삽입연산과 같음
	void AddFront (int );
	int DelFront() { return DeQueue(); } // 덱의 앞에 삭제하는 함수는 큐의 삭제연산과 같음
	int DelRear();
	int GetFront() { return Peek(); } // 덱의 앞을 보여주는 함수는 큐의 peek연산과 같음
	int GetRear();
};
void CLwyDeQueue::AddFront(int i) 
{
	if (IsFull()) {
		printf("덱이 가득차있어요\n");
		return;
	}
	m_data[m_front] = i; // 받아온 데이터를 저장
	m_front--;
	if ( m_front < 0 ) m_front = MAXSIZEQUEUE - 1;//m_front = (m_front-1+MAXSIZEQUEUE) %MAXSIZEQUEUE;
}
int CLwyDeQueue::DelRear() 
{
	if ( IsEmpty()) {
		printf("덱이 비었어요\n");
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
