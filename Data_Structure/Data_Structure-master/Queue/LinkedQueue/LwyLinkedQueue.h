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

	void EnQueue(CLwyNode* ); // 큐의 삽입함수
	CLwyNode* DeQueue(); // 큐의 삭제함수
	CLwyNode* Peek() { return m_front; } // 큐의 위에꺼 보는 함수, front 반환해주었음
};
void CLwyLinkedQueue::DisPlay()
{
	CLwyNode *temp = m_front; // m_front를 받을 임시 변수 선언
	printf(" [전체 항목의 수 %d개] : ", m_nNodes);
	while ( temp != m_rear ) { // front를 임시로 받은 temp가 rear과 같은곳을 가리킬때 까지 반복하여
		printf("%2d", temp->getElement()); // 원소를 출력합니다.
		temp = temp->Next(); // 링크를 따라 한칸 건넙니다.
	}
	printf("%2d\n\n", m_rear->getElement()); //temp와 rear이 같은곳을 가리킬 떄 출력을 안했으므로 rear을 한번더 출력해 주었습니다.
}
void CLwyLinkedQueue::EnQueue(CLwyNode *e)
{	
	if (IsEmpty()) { // 비어있으면
		e->setLink(NULL); // 노드의 링크를 NULL로 세팅해둔 뒤
		m_front = m_rear = e; // front와 rear을 새로 받아온 노드로 지정해줍니다.
	}
	else {
		m_rear->addNext(e); // rear가 가리키는 곳에 하나씩 넣습니다.
		m_rear = e;
	}
	m_nNodes++;
}
CLwyNode* CLwyLinkedQueue::DeQueue()
{
	if (IsEmpty()) return NULL; // 공백일때 연산 불가
	CLwyNode *n = m_front; // front를 임시 포인터로 지정해 두고
	if( m_front->Next() == NULL ) m_front = m_rear = NULL;
	else m_front = m_front->Next();
	m_nNodes--;
	return n;
}