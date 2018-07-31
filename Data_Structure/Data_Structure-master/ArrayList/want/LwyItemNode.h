#pragma once
#include "LwyItem.h"
#include <stdio.h>
#include <stdlib.h>
class CLwyNode : public CLwyItem
{
	CLwyNode* m_link; // 다음 노드를 가리키기 위한 포인터 변수
public:
	//CLwyNode( ) { m_link = NULL; }// 디폴트생성자
	CLwyNode( char* name = " ", int price = 0, int order = 0, char* memo = " ") :  CLwyItem(name, price, order, memo) {
		m_link = NULL;
	}
	~CLwyNode(void) { }
	CLwyNode* Next() { return m_link;} // m_link의 getter
	void setLink( CLwyNode *p) { m_link = p; } // setter
	void addNext( CLwyNode *p); // 다음 노드를 생성
	CLwyNode* DeleteNext();		// 노드를 제거하는 연산
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