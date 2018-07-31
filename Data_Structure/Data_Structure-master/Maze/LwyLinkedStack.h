#pragma once
#include "LwyNode.h"
#include <string.h>

class CLwyLinkedStack
{
	CLwyNode m_org; // 헤드노드
public:
	CLwyLinkedStack(void) { } // 디폴트 생성자
	~CLwyLinkedStack(void) {  } // 스택에 아무것도 없으면 데이터 반환

	CLwyNode *GetHead() { return m_org.Next(); }
	bool IsEmpty() { return GetHead() == NULL; }   // 스택이 비어있는지 확인, 헤드를 확인하여 NULL인지 아닌지
	void AddHead(CLwyNode *n) { m_org.addNext(n); } // Push
	CLwyNode* RemovedHead() { return m_org.RemoveNext(); }

	void Reset();
	void Clear();	
	
	int GetLength(); 
	void DisPlay();

	void Push(CPoint2D ); //  AddHead
	CPoint2D Pop();			//	RemovedHead();
	CPoint2D Peek();      //   GetHead
};
void CLwyLinkedStack::Clear()
{ // 안에서 RemovedHead(); 호출
	while(!IsEmpty()) 
		delete RemovedHead();
}
void CLwyLinkedStack::Reset()
{ 
	Clear();
	m_org.setLink(NULL);
}  // reset 안에 clear 호출
int CLwyLinkedStack::GetLength()
{
	int count = 0;
	//for ( int i = 0 ; i < max ; i++ )
	for ( CLwyNode* p = GetHead() ; p!= NULL ; p=p->Next() ) 
		count++;
	return count;
}// 리스트 항목갯수 반환
void CLwyLinkedStack::DisPlay()
{
	printf("[%d] 문자", GetLength());  // 리스트 항목갯수 출력
	for ( CLwyNode* p = GetHead() ; p != NULL ; p = p->Next() ) 
		p->Display();
	printf("\n");
}
void CLwyLinkedStack::Push( CPoint2D cp )
{
	AddHead(new CLwyNode(cp)); // new생성자를 이용하여 Node의 데이터필드에 매개변수로 받은 문자 할당 
}

CPoint2D CLwyLinkedStack::Pop() // 반환형 ch로
{
	CLwyNode *p = RemovedHead();
	if (p == NULL) return m_org.ResetElement(); // IsEmpty일 경우
	CPoint2D cp = p->getElement();
	delete p;
	return cp;
}
CPoint2D CLwyLinkedStack::Peek()
{
	CLwyNode *p = GetHead(); // GetHead를 이용하여 Peek함수 구현
	if ( IsEmpty()) return m_org.ResetElement();
	return p->getElement();
}