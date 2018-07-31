#pragma once
#include "LwyItem.h"
#include <stdio.h>
#include <stdlib.h>
class CLwyNode : public CLwyItem
{
	CLwyNode* m_link; // ���� ��带 ����Ű�� ���� ������ ����
public:
	//CLwyNode( ) { m_link = NULL; }// ����Ʈ������
	CLwyNode( char* name = " ", int price = 0, int order = 0, char* memo = " ") :  CLwyItem(name, price, order, memo) {
		m_link = NULL;
	}
	~CLwyNode(void) { }
	CLwyNode* Next() { return m_link;} // m_link�� getter
	void setLink( CLwyNode *p) { m_link = p; } // setter
	void addNext( CLwyNode *p); // ���� ��带 ����
	CLwyNode* DeleteNext();		// ��带 �����ϴ� ����
};
void CLwyNode::addNext(CLwyNode *p) 
{
	if ( p!= NULL ) {
		p->m_link = m_link;
		m_link = p;
	}
}
CLwyNode* CLwyNode::DeleteNext()
{
	CLwyNode *p = m_link;
	if ( p != NULL ) m_link = p->m_link;
	return p;
}