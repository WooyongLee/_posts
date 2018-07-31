#pragma once
#include "LwyElement.h"
#define MAX_LIST_SIZE 100
class CLwyArrayList
{
	CLwyElement m_data[MAX_LIST_SIZE];
	int m_len;
public:
	CLwyArrayList(void) { m_len = 0; }
	~CLwyArrayList(void) { }

	bool IsEmpty( ) { return m_len == 0; } // 공백 리스트일 경우 리스트의 길이는 0
	bool IsFull( ) { return m_len == MAX_LIST_SIZE; } // 리스트가 최대 크기일 경우
	CLwyElement GetEntry(int pos) { return m_data[pos]; } 
	int GetLength() { return m_len; } // 길이에 대한 getter
	void Clear( ) { m_len = 0; } 
	void Replace(int pos, int e) { m_data[pos].SetElement(e); } // 원소를 수정합니다.
	void Display(char *); // 출력
	void Add(int , int ); // 삽입
	void AddTail(int e)  { Add(m_len , e); } // 리스트의 맨 뒤 원소 추가
	void AddHead(int e) { Add(0, e); } // 리스트의 맨 앞에 원소 추가
	int Remove(int pos); // 삭제
	int RemoveTail() { return Remove(m_len - 1); } // 리스트의 크기에 - 1 해준 배열 공간이 리스트의 가장 끝
	int RemoveHead() { return Remove(0); } // 리스트의 처음위치는 0
};
void CLwyArrayList::Display(char *c) 
{
	printf("%s", c);
	printf("[전체 항목의 수 : %2d] : ", m_len);
	for ( int i = 0 ; i < m_len ; i++ )
		printf("%5d ", m_data[i]);
	printf("\n");
}
void CLwyArrayList::Add(int pos, int e)
{
	if ( (!IsFull()) && (pos >= 0) ) {
		for ( int i = m_len ; i > pos ; i-- )
			m_data[i] = m_data[i-1]; // data를 뒤쪽으로 하나씩 밀어줍니다.
		m_data[pos].SetElement(e);
		m_len += 1;
	}
}
int CLwyArrayList::Remove(int pos)
{
	if ( (0 <= pos) && (pos < m_len) ) { // 리스트의 처음 위치 0부터 리스트의 크기 
		int elem = m_data[pos].GetElement(); // - 1(리스트의 마지막 위치) 에서 연산수행
		for( int i = pos + 1 ; i < m_len ; i++ )
			m_data[i-1] = m_data[i]; // data를 앞쪽으로 하나씩 옮겨줍니다.
		m_len--;
		return elem;
	}
	else 
		printf("Error\n");
}
