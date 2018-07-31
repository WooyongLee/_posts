//추가 구현은 따로 구현
#pragma once
#include <string.h>
#include "LwyNode.h"
class CLwyLinkedQueue : public CLwyNode
{
	CLwyNode* m_front; // 헤드 포인터
	CLwyNode* m_rear;
	int m_nNodes;
public:
	CLwyLinkedQueue() : m_nNodes(0) { m_front = m_rear = NULL; } // 디폴트 생성자
	~CLwyLinkedQueue(void) {  } // 스택에 아무것도 없으면 데이터 반환

	bool IsEmpty()  {return m_front == NULL;}// { return GetHead() == NULL; }    // 큐가 비어있는지 확인, 헤드를 확인하여 NULL인지 아닌지

	void DisPlay(); // 출력함수

	void EnQueue(CLwyNode* );
	CLwyNode* DeQueue();
	CLwyNode* Peek();
};
void CLwyLinkedQueue::DisPlay()
{
	CLwyNode *temp = m_front; // m_front를 받을 임시 변수 선언
	printf(" [전체 항목의 수 %d개] : ", m_nNodes);
	while ( temp != m_rear ) {
		printf("%2c", temp->getElement());
		temp = temp->Next();
	}
	printf("%2c\n\n", m_rear->getElement());
}
void CLwyLinkedQueue::EnQueue(CLwyNode *e)
{	
	if (IsEmpty()) {
		e->setLink(NULL);
		m_front = m_rear = e;
	}
	else {
		m_rear->addNext(e);
		m_rear = e;
	}
	m_nNodes++;
}

CLwyNode* CLwyLinkedQueue::DeQueue()
{
	if (IsEmpty()) return NULL;
	CLwyNode *n = m_front;
	if( m_front->Next() == NULL ) m_front = m_rear = NULL;
	else m_front = m_front->Next();
	m_nNodes--;
	return n;
}
CLwyNode* CLwyLinkedQueue::Peek()
{
	return m_front;
}