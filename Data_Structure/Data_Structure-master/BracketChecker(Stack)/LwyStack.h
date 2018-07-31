#pragma once
#include <stdio.h>
#include <stdlib.h>
const int MAX_STACK_SIZE = 100; // 스택의 최대 Size는 100으로 
class CLwyStack
{
	char m_data[MAX_STACK_SIZE]; // 요소의 배열
	int m_top;
public:
	CLwyStack(void) : m_top(0) {  } // 기본 생성자
	~CLwyStack(void)  {  Reset(); }// 스택에 아무것도 없다는 것, 초기화
	bool IsEmpty() { return m_top == 0; } // 스택이 0
	bool IsFull() { return m_top == MAX_STACK_SIZE; } // 스택이 full일 경우 
	void Push( char ); // 스택에 값을 push함
	char Pop(); // 스택에 값을 pop함
	char Peek(); // 스택의 맨 위에 있는 값을 반환함
	void Display(); // 현재 스택의 상황을 출력
	void Reset(); // 스택을 초기화
};

void CLwyStack::Push(char e)
{
	if (IsFull()) {// 스택이 full인지 아닌지를 일단 검사
		printf("Error : 스택이 FULL \n"); // full일 경우 값을 더 넣을수가 없음
		return;
	}
	m_top += 1; // 스택의 top의 위치가 바뀜,+1 해줍니다.
	m_data[m_top] = e; // 스택의 데이터 새롭게 할당한 배열요소에 하나 더 받습니다.
}

char CLwyStack::Pop()
{
	if ( IsEmpty() ) { // 스택이 비엇는지 아닌지 일단 검사
		printf("Error : 스택공백\n"); // 공백일 경우 값을 뺄 수가 없어요
		return 0;
	}
	// 스택의 top의 위치가 바뀜, -1 해줍시다.
	return m_data[m_top--]; // 기존 스택에 있던 데이터를 반환합니다
}

char CLwyStack::Peek()
{
	if (IsEmpty() ) { //스택의 꼭대기를 판별하려면 스택이 비어있으면 안되죠
		printf("Error :스택공백\n"); 
		return 0;
	}
	return m_data[m_top - 1]; // 스택의 맨 위에 자료만 반환하고 아무 연산하지 않습니다.
}

void CLwyStack::Display() 
{
	for ( int i = 0 ; i < m_top ; i++ ) // 스택의 각 인자들을 밑에서부터 반복하면서 차례대로 쭉 출력해봅니다.
		printf("< %c > ", m_data[m_top]);
}
void CLwyStack::Reset()
{
	m_top = 0; // top을 0으로 주어 스택을 비웁니다.
}