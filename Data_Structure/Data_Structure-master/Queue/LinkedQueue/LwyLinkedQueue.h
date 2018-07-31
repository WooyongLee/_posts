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

	void EnQueue(CLwyNode* ); // ť�� �����Լ�
	CLwyNode* DeQueue(); // ť�� �����Լ�
	CLwyNode* Peek() { return m_front; } // ť�� ������ ���� �Լ�, front ��ȯ���־���
};
void CLwyLinkedQueue::DisPlay()
{
	CLwyNode *temp = m_front; // m_front�� ���� �ӽ� ���� ����
	printf(" [��ü �׸��� �� %d��] : ", m_nNodes);
	while ( temp != m_rear ) { // front�� �ӽ÷� ���� temp�� rear�� �������� ����ų�� ���� �ݺ��Ͽ�
		printf("%2d", temp->getElement()); // ���Ҹ� ����մϴ�.
		temp = temp->Next(); // ��ũ�� ���� ��ĭ �ǳҴϴ�.
	}
	printf("%2d\n\n", m_rear->getElement()); //temp�� rear�� �������� ����ų �� ����� �������Ƿ� rear�� �ѹ��� ����� �־����ϴ�.
}
void CLwyLinkedQueue::EnQueue(CLwyNode *e)
{	
	if (IsEmpty()) { // ���������
		e->setLink(NULL); // ����� ��ũ�� NULL�� �����ص� ��
		m_front = m_rear = e; // front�� rear�� ���� �޾ƿ� ���� �������ݴϴ�.
	}
	else {
		m_rear->addNext(e); // rear�� ����Ű�� ���� �ϳ��� �ֽ��ϴ�.
		m_rear = e;
	}
	m_nNodes++;
}
CLwyNode* CLwyLinkedQueue::DeQueue()
{
	if (IsEmpty()) return NULL; // �����϶� ���� �Ұ�
	CLwyNode *n = m_front; // front�� �ӽ� �����ͷ� ������ �ΰ�
	if( m_front->Next() == NULL ) m_front = m_rear = NULL;
	else m_front = m_front->Next();
	m_nNodes--;
	return n;
}