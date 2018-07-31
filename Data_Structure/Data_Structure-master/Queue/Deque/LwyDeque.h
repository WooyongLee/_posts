#pragma once
#include <stdio.h>
#define MAXSIZEDEQUE 10 // 최대 큐의 크기 설정
class CLwyDeque
{
private :
	int m_front; // 가장 최근에 삭제된 위치
	int m_rear; //가장 최근에 삽입된 위치
	int m_data[MAXSIZEDEQUE];
public :
	CLwyDeque(void) { m_front = m_rear = 0; } // 공백 큐 만들기
	~CLwyDeque(void) { 	}

	bool IsEmpty() { return m_front == m_rear; } // 큐이 처음과 끝이 같을 경우는 공백
	bool IsFull() { return m_front == (m_rear + 1) % MAXSIZEDEQUE; }

	void AddRear(int ); // 덱 뒤쪽 삽입함수
	void AddFront(int ); // 덱 앞쪽 삽입함수
	int DelFront(); // 덱 앞쪽 삭제함수
	int DelRear(); // 덱 뒷쪽 삭제함수
	int GetFront();	 // 덱 앞쪽 보여주는 함수
	int GetRear(); // 덱 뒷쪽 보여주는 함수
	void Display(); // 출력함수
};
void CLwyDeque::AddRear(int i)
{
	if(IsFull()) { // 덱이 풀일떄 연산 불가
		printf("덱이 가득 차 있습니다.\n"); 
		return;
	}
	m_rear++; //덱의 rear을 하나 증가시켜 줍니다.
	m_rear = m_rear % MAXSIZEDEQUE; // 덱의 저장공간 범위를 넘어가지 않도록 설정함
	// 만일 m_rear가 덱의 최대치를 넘어설 경우 다시 덱의 첫 공간부터 할당합니다. - 모듈라연산
	m_data[m_rear] = i; // 덱에 인자를 넣습니다.
}
void CLwyDeque::AddFront(int i)
{
	if (IsFull()) { // 덱이 풀일떄 연산 불가
		printf("덱이 가득 차 있습니다.\n"); 
		return;
	}
	m_data[m_front] = i;	
	m_front--;
	if ( m_front < 0 ) m_front = MAXSIZEDEQUE - 1; // m_front = (m_front-1+MAXQUEUESIZE) %MAXQUEUESIZE;
} // m_front가 0보다 작아지면 최대크기에 1을 뺴준 배열의 가장 뒷쪽을 채움
int CLwyDeque::DelFront()
{
	if(IsEmpty()){ // 덱이 비어 있을 경우 연산 불가
		printf("덱이 비어 있습니다.\n");
		return -1;
	}
	m_front++; // 덱의 front를 하나 증가시켜 줍니다.
	m_front = m_front % MAXSIZEDEQUE;
	return m_data[m_front]; // 덱의 선두값을 반환해 줍니다.
}
int CLwyDeque::DelRear()
{
	if(IsEmpty()){ // 덱이 비어 있을 경우 연산 불가
		printf("덱이 비어 있습니다.\n");
		return -1;
	}
	int temp = m_data[m_rear];
	m_rear = (m_rear - 1 + MAXSIZEDEQUE) % MAXSIZEDEQUE;
	return temp;
}
int CLwyDeque::GetFront()
{
	if(IsEmpty()){ // 공백검사
		printf("덱이 비어 있습니다.\n");
		return -1;
	}
	return m_data[(m_rear) % MAXSIZEDEQUE];
}
int CLwyDeque::GetRear()
{	
	if(IsEmpty()){ // 공백검사
		printf("덱이 비어 있습니다.\n");
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
