#pragma once
#include "lwyitem.h"
class CLwyDNode :
	public CLwyItem // ������� item�� �������� ����
{
	CLwyDNode* m_prev; // ������带 ����Ű�� ������
	CLwyDNode* m_next; // ������带 ����Ű�� ������
public:
	CLwyDNode( char* name ="", int price = 0, int order = 0, char* memo = "")
		: CLwyItem(name, price, order, memo), m_prev(NULL), m_next(NULL) { } // ��ӹ����� �θ����� �ʱ�ȭ����Ʈ�� ȣ��
	~CLwyDNode(void) {	}

	//getter, setter
	CLwyDNode* GetPrev() { return m_prev; }
	CLwyDNode* GetNext() { return m_next; }
	void SetPrev(CLwyDNode *n) { m_prev = n; }
	void SetNext(CLwyDNode *n) { m_next = n; }
	// Add/Remove �Լ�
	void AddNext (CLwyDNode *n) {
		if( n != NULL ) { // n�� NULL�����ƴ��� ����ó�Ӥ�
			n->m_prev = this; // ���� �ּҷ�, n->SetPrev(this);
			n->m_next = m_next; // ���� ������ �����̴�n->SetNext(m_next);
			if ( m_next != NULL )
				m_next->m_prev = n; // m_next=>SetPrev(n);
			m_next = n; // SetNext(n);
		}
	}
	void Remove () {
		if ( m_prev != NULL ) // m_prev->SetNext(m_next);
			m_prev->m_next = m_next;
		if ( m_next != NULL )
			m_next->m_prev = m_prev;
	}
	void DisplayRevRecur( ) {
		if ( GetNext() != NULL ) // ���� ��尡 NULL�� �ƴ϶��
			GetNext()->DisplayRevRecur(); // ������忡�� �� �Լ��� ȣ��
		Display(); // ��Ͱ� ��� ������ ����� �ϵ��� ��
	}
};