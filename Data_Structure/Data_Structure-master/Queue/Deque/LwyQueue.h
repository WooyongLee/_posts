#pragma once
#include <stdio.h>
#define MAXSIZEQUEUE 10 // 최대 큐의 크기 설정
class CLwyQueue
{
protected :
	int m_front; // 가장 최근에 삭제된 위치
	int m_rear; //가장 최근에 삽입된 위치
	int m_data[MAXSIZEQUEUE];
public :
	CLwyQueue(void) { m_front = m_rear = 0; } // 공백 큐 만들기
	~CLwyQueue(void) { 	}

	bool IsEmpty() { return m_front == m_rear; } // 큐이 처음과 끝이 같을 경우는 공백
	bool IsFull() { return m_front == (m_rear + 1) % MAXSIZEQUEUE; }
	
	void EnQueue(int ); // 큐 삽입함수
	int DeQueue(); // 큐 삭제함수
	int Peek(); // 꺼내서 보기만 하는 함수
	void Display(); // 출력함수
};
void CLwyQueue::EnQueue(int i)
{
	if(IsFull()) { // 예외처리, 큐가 꽉 차있을 경우 연산 불가
		printf("큐가 가득 차 있습니다.\n"); 
		return;
	}
	m_rear++; //큐의 rear을 하나 증가시켜 줍니다.
	m_rear = m_rear % MAXSIZEQUEUE; // 큐의 저장공간 범위를 넘어가지 않도록 설정함
	// 만일 m_rear가 큐의 최대치를 넘어설 경우 다시 큐의 첫 공간부터 할당합니다.
	m_data[m_rear] = i; // 큐에 인자를 넣습니다.
}
int CLwyQueue::DeQueue()
{
	if(IsEmpty()){ // 예외처리, 큐가 비어 있을 경우 연산 불가
		printf("큐가 비어 있습니다.\n");
		return -1;
	}
	m_front++; // 큐의 front를 하나 증가시켜 줍니다.
	m_front = m_front % MAXSIZEQUEUE;
	return m_data[m_front]; // 큐의 선두값을 반환해 줍니다.
}

int CLwyQueue::Peek()
{
	if(IsEmpty()){
		printf("큐가 비어 있습니다.\n");
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
