#pragma once
#include <stdlib.h>
#include "LwyElement.h"
class CLwyNode : public CLwyElement
{
protected :
	CLwyNode* m_link; // 다음 노드를 가리키기 위한 포인터 변수
public:
	CLwyNode(int num = 0) : CLwyElement(num) { m_link = NULL; } // 디폴트생성자
	~CLwyNode() { }
	CLwyNode* Next() { return m_link;} // m_link의 getter
	void setLink( CLwyNode *p) { m_link = p; } // setter
	void addNext( CLwyNode *p); // 다음 노드를 생성
	CLwyNode* RemoveNext();		// 노드를 제거하는 연산
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