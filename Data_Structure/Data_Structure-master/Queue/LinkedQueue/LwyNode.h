#pragma once
#include <stdlib.h>
#include "LwyElement.h"
class CLwyNode : public CLwyElement
{
protected :
	CLwyNode* m_link; // ���� ��带 ����Ű�� ���� ������ ����
public:
	CLwyNode(int num = 0) : CLwyElement(num) { m_link = NULL; } // ����Ʈ������
	~CLwyNode() { }
	CLwyNode* Next() { return m_link;} // m_link�� getter
	void setLink( CLwyNode *p) { m_link = p; } // setter
	void addNext( CLwyNode *p); // ���� ��带 ����
	CLwyNode* RemoveNext();		// ��带 �����ϴ� ����
	int GetInt(void) { return getElement(); }// 
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