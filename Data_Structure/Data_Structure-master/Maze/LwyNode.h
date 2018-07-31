#pragma once
#include "LwyElement.h"
#include <stdio.h>
#include <stdlib.h>

class CLwyNode : public CLwyElement
{
	CLwyNode* m_link; // ���� ��带 ����Ű�� ���� ������ ����
public:
	CLwyNode() { 
		CLwyElement();  
		m_link = NULL; 
	}
	CLwyNode(CPoint2D cp) : CLwyElement(this->cp.m_x = cp.m_x, this->cp.m_y = cp.m_y) { m_link = NULL; } // ����Ʈ������
	~CLwyNode(void) { }
	CLwyNode* Next() { return m_link;} // m_link�� getter
	void setLink( CLwyNode *p) { m_link = p; } // setter
	void addNext( CLwyNode *p); // ���� ��带 ����
	CLwyNode* RemoveNext();		// ��带 �����ϴ� ����
};
void CLwyNode::addNext(CLwyNode *p) 
{
	if ( p!= NULL ) {
		p->m_link = m_link;
		m_link = p;
	}
}
CLwyNode* CLwyNode::RemoveNext()
{
	CLwyNode *p = m_link;
	if ( p != NULL ) m_link = p->m_link;
	return p;
}