#pragma once
#include "LwyElement.h"
#include <stdio.h>
#include <stdlib.h>

class CLwyNode : public CLwyElement
{
	CLwyNode* m_link; // 다음 노드를 가리키기 위한 포인터 변수
public:
	CLwyNode() { 
		CLwyElement();  
		m_link = NULL; 
	}
	CLwyNode(CPoint2D cp) : CLwyElement(this->cp.m_x = cp.m_x, this->cp.m_y = cp.m_y) { m_link = NULL; } // 디폴트생성자
	~CLwyNode(void) { }
	CLwyNode* Next() { return m_link;} // m_link의 getter
	void setLink( CLwyNode *p) { m_link = p; } // setter
	void addNext( CLwyNode *p); // 다음 노드를 생성
	CLwyNode* RemoveNext();		// 노드를 제거하는 연산
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