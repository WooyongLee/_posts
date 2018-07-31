//�߰� ������ ���� ����
#pragma once
#include <string.h>
#include "LwyNode.h"
class CLwyLinkedQueue : public CLwyNode
{
	CLwyNode* m_front; // ��� ������
	CLwyNode* m_rear;
	int m_nNodes;
public:
	CLwyLinkedQueue() : m_nNodes(0) { m_front = m_rear = NULL; } // ����Ʈ ������
	~CLwyLinkedQueue(void) {  } // ���ÿ� �ƹ��͵� ������ ������ ��ȯ

	bool IsEmpty()  {return m_front == NULL;}// { return GetHead() == NULL; }    // ť�� ����ִ��� Ȯ��, ��带 Ȯ���Ͽ� NULL���� �ƴ���

	void DisPlay(); // ����Լ�

	void EnQueue(CLwyNode* );
	CLwyNode* DeQueue();
	CLwyNode* Peek();
};
void CLwyLinkedQueue::DisPlay()
{
	CLwyNode *temp = m_front; // m_front�� ���� �ӽ� ���� ����
	printf(" [��ü �׸��� �� %d��] : ", m_nNodes);
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